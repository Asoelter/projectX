#ifndef MESH_H
#define MESH_H

#include <type_traits>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef unsigned GLuint;

namespace core::graphics
{

struct MeshDescriptor
{
    MeshDescriptor()
        : valuesPerIndex(0)
        , offsets()
        , elementBuffer()
    {}

    int                   valuesPerIndex;
    std::vector<unsigned> offsets;
    std::vector<unsigned> elementBuffer;
};

template
    <
    typename T, 
    typename = std::enable_if_t<std::is_floating_point_v<T>>
    >
class Mesh
{
public:
    Mesh(std::vector<T> const & data, const MeshDescriptor& descriptor)
        : elementSize(descriptor.elementBuffer.size())
    {
        //TODO(asoelter): bullet proof this
        if (glGenVertexArrays == NULL) {
            std::cout << "Do not have an glGenVertexArrays pointer\n";
            exit(-1);
        }
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

        for(int i = 0; i < descriptor.offsets.size(); ++i)
        {
            auto stride = 0;
            if(i > 0)
            {
                stride = descriptor.offsets.size() * descriptor.valuesPerIndex * sizeof(T);
            }
            glVertexAttribPointer(i, descriptor.valuesPerIndex, type, GL_FALSE, stride, (void*)( descriptor.offsets[i] * sizeof(T) ));
            glEnableVertexAttribArray(i);
        }
    }

    Mesh(std::vector<T>         data, 
         std::vector<unsigned>  elementBuffer,
         std::vector<unsigned>  offsets = {})
        : elementSize(elementBuffer.size())
    {
        (void)offsets;
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

private:
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint ebo_ = 0;
    int elementSize = 0;
};
}

#include "mesh.hpp"

#endif //MESH_H
