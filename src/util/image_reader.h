#ifndef FILE_READER_H
#define FILE_READER_H

#include <array>
#include <cstdint>
#include <string>

class ImageReader
{
public:
    ImageReader(const std::string& filePath);
    ~ImageReader();

    [[nodiscard]]
    uint8_t* data() const;

    [[nodiscard]]
    int width() const noexcept;

    [[nodiscard]]
    int height() const noexcept;

    [[nodiscard]]
    int channelCount() const noexcept;
private:
    uint8_t* data_;
    int      width_;
    int      height_;
    int      channelCount_;
};

#endif //FILE_READER_H
