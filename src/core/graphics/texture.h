#ifndef TEXTURE_H
#define TEXTURE_H

#include <initializer_list>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../containers/little_map.h"

namespace core::graphics
{
class Texture
{
public:
    Texture(const std::string& filePath, int texNumber = 0);
    void bind() const;
    void unbind() const;

private:
    using MapType = core::containers::LittleMap<std::string, GLenum>;

    unsigned int id_;
    unsigned int textureNumber_;
    static MapType fileEnums_;
};

class TextureBlock
{
public:
    TextureBlock(const std::initializer_list<std::string>& fileNames);

    void bind() const;
    void unbind() const;

    [[nodiscard]] 
    bool empty() const;

private:
    std::vector<Texture> textures_;
};

}

#endif //TEXTURE_H
