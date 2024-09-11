#pragma once
#include <string>

#include "Reader.hpp"
#include "Writer.hpp"


class Program
{
public:
    Program(int argc, char* argv[]);

    void run() const;
    void setTargetReader(Reader&& targetReader);
    void setConfigReader(Reader&& configReader);
    void setDestinationWriter(Writer&& destinationWriter);

private:
    std::string targetPath_;
    std::string configPath_;
    std::string destinationDirectory_;

    Reader targetReader_;
    Reader configReader_;
    Writer destinationWriter_;
};
