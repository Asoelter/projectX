#include "file_reader.h"

#include <algorithm>
#include <fstream>
#include <stack>

#include "handmade_util.h"

namespace 
{

constexpr auto toByte(char c)
{
    return static_cast<uint8_t>(c);
}

constexpr auto isBlank(char c)
{
    const auto byte = toByte(c);

    return byte == 0 
        || byte == FileReader::carriageReturn 
        || byte == FileReader::newLine;
}

}

FileReader::FileReader(const std::string& filePath)
    : data_()
    , readCursor_(0)
    , chunkLookout_{0, 0, 0, 0}
{
    readFile(filePath);

    if(!verify())
    {
        throw std::invalid_argument("Not a png file");
    }

    readIHDR();
}

void FileReader::readFile(const std::string& filePath)
{
    std::fstream fin(filePath);
    data_.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
}

[[nodiscard]]
char FileReader::readChar()
{
    auto nextChar = data_[readCursor_++];

    while(isBlank(nextChar)) //ignore white space
    {
        nextChar = data_[readCursor_++];
    }

    addToChunkLookout(nextChar);

    return nextChar;
}

[[nodiscard]] 
char FileReader::peakChar()
{
    auto nextChar = data_[readCursor_];
    int distancetoNextChar = 1;

    while(isBlank(nextChar)) //ignore white space
    {
        nextChar = data_[readCursor_ + distancetoNextChar++];
    }

    return nextChar;
}

[[nodiscard]]
uint8_t FileReader::readByte() 
{
    const auto nextChar = data_[readCursor_++];

    addToChunkLookout(nextChar);

    const auto nextByte = static_cast<uint8_t>(nextChar);

    return toByte(nextByte);
}

[[nodiscard]] 
uint8_t FileReader::peakByte()
{
    const auto nextChar = data_[readCursor_];
    const auto nextByte = static_cast<uint8_t>(nextChar);

    return toByte(nextByte);
}

[[nodiscard]] 
uint16_t FileReader::readHalfWord()
{
    const auto firstByte  = readByte();
    const auto secondByte = readByte();

    const auto halfWord = firstByte << 8 | secondByte << 0; 

    return halfWord;
}

[[nodiscard]] 
uint16_t FileReader::peakHalfWord()
{
    const auto firstByte  = data_[readCursor_];
    const auto secondByte = data_[readCursor_ + 1];
    const auto word = firstByte << 8 | secondByte << 0;
    return word;
}

[[nodiscard]] 
uint32_t FileReader::readWord()
{
    const auto firstByte  = readByte();
    const auto secondByte = readByte();
    const auto thirdByte  = readByte();
    const auto fourthByte = readByte();

    const auto word = firstByte  << 24
                    | secondByte << 16
                    | thirdByte  << 8
                    | fourthByte << 0;

    return word;
}

void FileReader::addToChunkLookout(char c)
{
    chunkLookout_[0] = chunkLookout_[1];
    chunkLookout_[1] = chunkLookout_[2];
    chunkLookout_[2] = chunkLookout_[3];
    chunkLookout_[3] = c;
}

[[nodiscard]]
bool FileReader::verify()
{
    std::stack<uint8_t> headerContents;
    std::string reader;

    headerContents.push(0x1a);
    headerContents.push(0x47);
    headerContents.push(0x4e);
    headerContents.push(0x50);
    headerContents.push(0x89); //do we need to set the high bits?

    while(!headerContents.empty())
    {
        const auto& fileByte       = toByte(readChar());
        const auto& nextHeaderByte = headerContents.top();

        if(nextHeaderByte != fileByte)
        {
            return false;
        }

        headerContents.pop();
    }

    return true;
}

void FileReader::readIHDR()
{
    const auto i = readChar();
    const auto h = readChar();
    const auto d = readChar();
    const auto r = readChar();

    if(i != 'I' && h != 'H' && d != 'D' && r != 'R')
    {
        throw std::invalid_argument("Not a png file");
    }

    // TODO(asoelter): how much of this is usefule 
    // info that needs to be saved?
    const auto width             = readWord(); //< Should these be reading a word? the spec says 
    const auto height            = readWord(); //< four bytes but the data looks like its in 8
    const auto bitDepth          = readByte(); 
    const auto colorType         = readByte();
    const auto compressionMethod = readByte();
    const auto filterMethod      = readByte();
    const auto interlaceMethod   = readByte();

    std::cout << "file width: " << width << std::endl;
    std::cout << "file height: " << height << std::endl;
    std::cout << "color type " << colorType << std::endl;
}
