#ifndef FILE_READER_H
#define FILE_READER_H

#include <array>
#include <cstdint>
#include <string>

class FileReader
{
public:
    FileReader(const std::string& filePath);

    static constexpr auto carriageReturn = 0x0d;
    static constexpr auto newLine = 0x0a;

private:
    enum class ChunkType
    {
        IHDR,
        PLTE,
        IDAT,
        IEND,
        UNKNOWN
    };

    void readFile(const std::string& filePath);

    //TODO(asoelter): get rid of peak methods??
    [[nodiscard]] char      readChar();
    [[nodiscard]] char      peakChar();
    [[nodiscard]] uint8_t   readByte();
    [[nodiscard]] uint8_t   peakByte();
    [[nodiscard]] uint16_t  readHalfWord();
    [[nodiscard]] uint16_t  peakHalfWord();
    [[nodiscard]] uint32_t  readWord();

    void addToChunkLookout(char c);
    [[nodiscard]] bool verify();
    void readIHDR();

    std::string         data_;
    size_t              readCursor_;
    std::array<char, 4> chunkLookout_;
};

#endif //FILE_READER_H
