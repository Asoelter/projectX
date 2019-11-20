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
uint8_t FileReader::readByte() 
{
    const auto nextSymbol = readChar();

    addToChunkLookout(static_cast<char>(nextSymbol));

    return toByte(nextSymbol);
}

[[nodiscard]] 
unsigned FileReader::readHalfWord()
{
    const auto firstByte  = readByte();
    const auto secondByte = readByte();

    const auto word = firstByte << 8 | secondByte << 0; 

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
        const auto& fileByte       = readByte();
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

    //TODO(asoelter): switch this to an exception? 
    if(i != 'I' && h != 'H' && d != 'D' && r != 'R')
    {
        throw std::invalid_argument("Not a png file");
    }

    const auto width  = readHalfWord();
    const auto height = readHalfWord();
}
