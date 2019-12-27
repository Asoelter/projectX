#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../containers/little_map.h"

namespace core::graphics
{
class Texture
{
public:
    Texture(const std::string& filePath);
    void bind() const;
    void unbind() const;

private:
    using MapType = core::containers::LittleMap<std::string, GLenum>;

    unsigned int id_;
    unsigned int textureNumber_;
    static int textureCount_;
    static MapType fileEnums_;
};
}

#endif //TEXTURE_H
