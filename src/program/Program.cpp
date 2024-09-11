#include "Program.hpp"
#include <cstdlib>

#include "ExitCode.hpp"
#include "models/guarded/GuardedChainFactory.hpp"


Program::Program(int argc, char* argv[])
{
    switch(argc)
    {
        case 3:
            break;
        case 4:
            destinationDirectory_ = argv[3];
            break;
        default:
            std::exit(ExitCode::INVALID_ARGS_NUMBER);
            break;
    }

    targetPath_ = argv[1];
    configPath_ = argv[2];
}

void Program::run() const
{
    std::optional<std::string> targetContents = targetReader_.read(targetPath_);
    if (targetContents == std::nullopt) std::exit(ExitCode::READ_FAIL);

    std::optional<std::string> configContents = configReader_.read(configPath_);
    if (configContents == std::nullopt) std::exit(ExitCode::READ_FAIL);

    std::shared_ptr<IChainFactory> chainFactory = std::make_shared<GuardedChainFactory>();

    std::shared_ptr<IConfigInterpreter> interpreter = chainFactory->createConfigInterpreter();
    std::vector<IConfigInterpreter::Instruction> instructions = interpreter->makeInstructions(*configContents);

    std::shared_ptr<IChainBuilder> builder = chainFactory->createChainBuilder();
    std::shared_ptr<IChainNode> startNode = builder->getStartOfBuiltChain(instructions);

    std::string formattedContents = startNode->handle(std::make_unique<IChainNode::WorkingData>(*targetContents))->text;

    bool writeSuccess = destinationWriter_.write(destinationDirectory_ + "formatted.txt", formattedContents);
    if (not writeSuccess) std::exit(ExitCode::WRITE_FAIL);
}

void Program::setTargetReader(Reader&& targetReader)
{
    targetReader_ = std::move(targetReader);
}

void Program::setConfigReader(Reader&& configReader)
{
    configReader_ = std::move(configReader);
}

void Program::setDestinationWriter(Writer&& destinationWriter)
{
    destinationWriter_ = std::move(destinationWriter);
}
