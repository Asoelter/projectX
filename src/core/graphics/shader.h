#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "../math/mat4.h"
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

    [[nodiscard]] 
    unsigned id() const;
    void bind();
    void unbind();

    void setUniform1i(const char* name, float value);
    void setUniform1f(const char* name, float value);
    void setUniformVec2f(const char* name, const math::vec2<float>& value);
    void setUniformVec4f(const char* name, const math::vec4<float>& value);
    void setUniformMat4f(const char* name, const math::mat4<float>& value);

    [[nodiscard]]
    static Shader* activeShader();

private:
    bool isError();
    std::string errorLog();
    unsigned compileShader(GLenum type, std::string source);

    const unsigned programID_;

private:
    static Shader* activeShader_;
};
}

#endif //SHADER_H
