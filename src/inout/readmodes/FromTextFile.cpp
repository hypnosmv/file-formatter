#include "readmodes/FromTextFile.hpp"
#include <fstream>
#include <iterator>


std::optional<std::string> FromTextFile::read(const std::string& path) const
{
    std::ifstream inputFile(path);
    if (not inputFile.is_open()) return std::nullopt;

    std::string fileContents;
    fileContents.assign(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
    inputFile.close();

    return fileContents;
}
