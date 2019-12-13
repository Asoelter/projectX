#include "image_reader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb/stb_image.h"


ImageReader::ImageReader(const std::string& filePath)
    : data_(nullptr)
    , width_(0)
    , height_(0)
    , channelCount_(0)
{
	stbi_set_flip_vertically_on_load(true);
    data_ = stbi_load(filePath.c_str(), &width_, &height_, &channelCount_, 0);

    if(!data_)
    {
        throw std::invalid_argument("Unable to read file " + filePath);
    }
}

ImageReader::~ImageReader()
{
	stbi_image_free(data_);
}

[[nodiscard]]
uint8_t* ImageReader::data() const
{
    return data_;
}

[[nodiscard]]
int ImageReader::width() const noexcept
{
    return width_;
}

[[nodiscard]]
int ImageReader::height() const noexcept
{
    return height_;
}

[[nodiscard]]
int ImageReader::channelCount() const noexcept
{
    return channelCount_;
}
