#ifndef SHADER_H
#define SHADER_H

#include <string>
typedef unsigned int GLenum;

namespace core::graphics
{
class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    unsigned id() const;
    void bind() const;
    void unbind() const;
private:
    bool isError();
    std::string errorLog();
    unsigned compileShader(GLenum type, std::string source);

    const unsigned programID_;
};
}

#endif //SHADER_H
