#include "file_reader.h"

#include <fstream>
#include <stack>

#include "handmade_util.h"

FileReader::FileReader(const std::string& filePath)
{
    std::fstream fin(filePath);

    if(!verify(fin))
    {
        handmade_assert(false);
    }
}

bool FileReader::verify(std::fstream& file)
{
    std::stack<int> headerContents;
    std::string reader;

    headerContents.push(0x0a);
    headerContents.push(0x01a);
    headerContents.push(0x0a);
    headerContents.push(0x0d);
    headerContents.push(0x47);
    headerContents.push(0x4e);
    headerContents.push(0x50);
    headerContents.push(0xFFFFFF89);

    while(file >> reader)
    {
        for(const auto& byte : reader)
        {
            std::cout << std::hex << static_cast<int>(byte) << ", ";
        }

        std::cout << '\n';
    }

    /*while(!headerContents.empty())
    {
        file >> reader;

        for(const auto& byte : reader)
        {
            const auto next = headerContents.top();
            headerContents.pop();

            if(next == static_cast<int>(byte))
            {
                std::cout << "WE HAVE A MATCH" << std::endl;
            }
            else
            {
                std::cout << "MISMATCH: " << std::hex << next << " : " << static_cast<int>(byte) << std::endl;
            }
        }
    }*/

    return true;
}
