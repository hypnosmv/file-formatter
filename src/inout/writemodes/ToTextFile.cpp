#include "writemodes/ToTextFile.hpp"
#include <fstream>


bool ToTextFile::write(const std::string& path, const std::string& contents) const
{
    std::ofstream outputFile(path);
    if (not outputFile.is_open()) return false;

    outputFile << contents;
    outputFile.close();

    return true;
}
