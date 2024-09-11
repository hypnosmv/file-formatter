#include "Program.hpp"
#include "ExitCode.hpp"
#include "readmodes/FromTextFile.hpp"
#include "writemodes/ToTextFile.hpp"


int main(int argc, char* argv[])
{
    Program program(argc, argv);

    program.setTargetReader(Reader(std::make_unique<FromTextFile>()));
    program.setConfigReader(Reader(std::make_unique<FromTextFile>()));
    program.setDestinationWriter(Writer(std::make_unique<ToTextFile>()));

    program.run();

    return ExitCode::SUCCESS;
}
