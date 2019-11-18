#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>

class FileReader
{
public:
    FileReader(const std::string& filePath);
private:
    bool verify(std::fstream& file);
    std::vector<unsigned char> data_;
};

#endif //FILE_READER_H
