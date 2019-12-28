#include "texture.h"

#include "../../util/image_reader.h"
#include "../../util/handmade_util.h"

namespace
{
std::string fileType(const std::string& fileName)
{
    const auto dotIndex = fileName.find_last_of(".");
    return fileName.substr(dotIndex + 1);
}
}

namespace core::graphics
{

Texture::MapType Texture::fileEnums_ = {{"bmp", GL_RGBA}, {"jpeg", GL_RGB}};

Texture::Texture(const std::string& filePath, int texNumber)
	: id_(0)
	, textureNumber_(texNumber)
{
    ImageReader reader(filePath);
    const auto data = reader.data();
    const auto& width = reader.width();
    const auto& height = reader.height();
    const auto& numChannels = reader.channelCount();

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const auto fileT = fileType(filePath);

    if(!fileEnums_.contains(fileT))
    {
        throw std::invalid_argument("Unsupported file type: " + fileT);
    }

    const auto alphaSetting = fileEnums_[fileT];

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, alphaSetting, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + textureNumber_);
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind() const
{
	glActiveTexture(GL_TEXTURE0 + textureNumber_);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

