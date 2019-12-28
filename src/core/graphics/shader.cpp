#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

#include "../../util/handmade_util.h"

#include <fstream>
#include <string>
#include <cstring>

std::string readFile(const std::string& filepath)
{
    std::fstream fin(filepath);
    std::string reader;
    std::string result;

    while(std::getline(fin, reader))
    {
        result += (reader + '\n');
    }

    return result;
}

namespace core::graphics
{

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : programID_(glCreateProgram())
{
    const auto vertexID = compileShader(GL_VERTEX_SHADER, readFile(vertexPath));
    const auto fragmentID = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentPath));

    glAttachShader(programID_, vertexID);
    glAttachShader(programID_, fragmentID);

    glLinkProgram(programID_);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID); 

    Window::setActiveShader(this);
}

Shader::~Shader()
{
    glDeleteProgram(programID_);
}

[[nodiscard]]
unsigned Shader::id() const
{
    return programID_;
}

void Shader::bind() 
{
    glUseProgram(programID_);

	if (Window::activeShader_ != this)
	{
		Window::setActiveShader(this);
	}
}

void Shader::unbind() 
{
    glUseProgram(0);

    if(Window::activeShader_ == this)
    {
        Window::setActiveShader(nullptr);
    }
}

void Shader::setUniform1i(const char* name, float value)
{
    auto location = glGetUniformLocation(programID_, name);

    glUniform1i(location, value);
}

void Shader::setUniform1f(const char* name, float value)
{
    const auto location = glGetUniformLocation(programID_, name);

    glUniform1f(location, value);
}

void Shader::setUniformVec2f(const char* name, const math::vec2<float>& value)
{
    const auto location = glGetUniformLocation(programID_, name);

    glUniform2fv(location, 1, value.data);
}

void Shader::setUniformVec4f(const char* name, const math::vec4<float>& value)
{
    const auto location = glGetUniformLocation(programID_, name);

    glUniform4fv(location, 1, value.data);
}

void Shader::setUniformMat4f(const char* name, const math::mat4<float>& value)
{
    const auto location = glGetUniformLocation(programID_, name);

    glUniformMatrix4fv(location, 1, GL_FALSE, value.data());
}

bool Shader::isError()
{
    int success = 0;
    //TODO(asoelter): find out why this causes errors
    glGetShaderiv(programID_, GL_COMPILE_STATUS, &success);

    //Hack to pop the error that this causes out of the queue
    while(glGetError() != 0);

    return success == GL_FALSE;
}

std::string Shader::errorLog()
{
    int maxLength = 0;
    int actualLength = 0;
    glGetShaderiv(programID_, GL_INFO_LOG_LENGTH, &maxLength);          
    char* log = (char*)alloca(maxLength);
    glGetProgramInfoLog(programID_, maxLength, &actualLength, log);

    std::string result(log);
    return result;
}

unsigned Shader::compileShader(GLenum type, std::string source)
{
    const auto id = glCreateShader(type);

    source.shrink_to_fit();
    const auto cSource = source.c_str();
    const auto size = static_cast<GLint>(source.size());

    glShaderSource(id, 1, &cSource, &size);
    glCompileShader(id);

    return id;
}

}
