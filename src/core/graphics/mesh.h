#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <numeric>
#include <type_traits>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../util/handmade_util.h"

typedef unsigned GLuint;

namespace core::graphics
{

//TODO(asoelter): change valuesPerIndex to a vector
//because the number of values per index can change
//based on the index

struct MeshDescriptor
{
    MeshDescriptor()
        : valuesPerIndex()
        , offsets()
        , elementBuffer()
    {}

    std::vector<int>      valuesPerIndex;
    std::vector<unsigned> offsets;
    std::vector<unsigned> elementBuffer;
};

template<typename T>
using EnableIfFloat = std::enable_if_t<std::is_floating_point_v<T>>;

template
    <
    typename T, 
    typename = EnableIfFloat<T>
    >
class Mesh
{
public:
    Mesh(std::vector<T> const & data, const MeshDescriptor& descriptor)
        : elementSize(descriptor.elementBuffer.size())
    {
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, descriptor.elementBuffer.size() * sizeof(unsigned), descriptor.elementBuffer.data(), GL_STATIC_DRAW);

        auto type = GL_FLOAT;

        if constexpr(!std::is_same_v<T, float>)
        {
            type = GL_DOUBLE;
        }

        const auto& valsPerIndex = descriptor.valuesPerIndex;
        const auto totalValuesPerIndex = std::accumulate(valsPerIndex.begin(), valsPerIndex.end(), 0);
        const auto stride = totalValuesPerIndex * sizeof(float); 

        for(int i = 0; i < descriptor.offsets.size(); ++i)
        {
            glVertexAttribPointer(i, descriptor.valuesPerIndex[i], type, GL_FALSE, stride, (void*)( descriptor.offsets[i] * sizeof(T) ));
            glEnableVertexAttribArray(i);
        }
    }

    Mesh(std::vector<T>         data, 
         std::vector<unsigned>  elementBuffer,
         std::vector<unsigned>  offsets = {})
        : elementSize(elementBuffer.size())
    {
        HANDMADE_UNUSED(offsets);
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.size() * sizeof(unsigned), elementBuffer.data(), GL_STATIC_DRAW);

        if constexpr(std::is_same_v<T, float>)
        {
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }
        else
        {
            glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, 0);
        }
    }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &ebo_);
    }

    void draw() const
    {
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glDrawElements(GL_TRIANGLES, elementSize, GL_UNSIGNED_INT, 0);
    }

    static std::vector<float> merge(const std::vector<T>& index1,
                                    const std::vector<T>& index2,
                                    unsigned valueCount1,
                                    unsigned valueCount2)
    {
        auto result        = std::vector<float>();
        auto pos1          = 0;
        auto pos2          = 0;
        auto pushingIndex1 = true;

        for(auto i = 0u; i < index1.size() + index2.size(); ++i)
        {
            if(pushingIndex1)
            {
                handmade_assert(pos1 < index1.size());

                result.push_back(index1[pos1++]);

                if(pos1 % valueCount1 == 0) 
                {
                    pushingIndex1 = false;
                }
            }
            else
            {
                handmade_assert(pos2 < index2.size());
                
                result.push_back(index2[pos2++]);

                if(pos2 % valueCount2 == 0) 
                {
                    pushingIndex1 = true;
                }
            }
        }

        return result;
    }


private:
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint ebo_ = 0;
    size_t elementSize = 0;
};
}

#include "mesh.hpp"

#endif //MESH_H
