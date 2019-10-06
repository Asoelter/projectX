#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "../math/vec4.h"
#include "../math/vec2.h"

typedef unsigned int GLenum;

namespace core::graphics
{
class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    unsigned id() const;
    void bind() const;
    void unbind() const;

    void setUniformVec4f(const char* name, 
                         const math::vec4<float>& value);

    void setUniformVec2f(const char* name, 
                         const math::vec2<float>& value);
private:
    bool isError();
    std::string errorLog();
    unsigned compileShader(GLenum type, std::string source);

    const unsigned programID_;
};
}

#endif //SHADER_H
