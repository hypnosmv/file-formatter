#include "factories/FindersFactory.hpp"
#include "ExitCode.hpp"
#include "finders/FindCharScope.hpp"
#include "finders/FindDuplicatedSemicolon.hpp"
#include "finders/FindLastLine.hpp"
#include "finders/FindLooseParenthesis.hpp"
#include "finders/FindMultiLineComment.hpp"
#include "finders/FindSingleLineComment.hpp"
#include "finders/FindSqueezedParenthesis.hpp"
#include "finders/FindStringScope.hpp"
#include "finders/FindTrailingBrace.hpp"
#include "finders/FindTrailingSpace.hpp"


std::shared_ptr<IFinder> FindersFactory::createFinder(const std::string& finderName) const
{
    if (finderName == "FIND_CHAR_SCOPE") return std::make_shared<FindCharScope>();
    else if (finderName == "FIND_DUPLICATED_SEMICOLON") return std::make_shared<FindDuplicatedSemicolon>();
    else if (finderName == "FIND_LAST_LINE") return std::make_shared<FindLastLine>();
    else if (finderName == "FIND_LOOSE_PARENTHESIS") return std::make_shared<FindLooseParenthesis>();
    else if (finderName == "FIND_MULTI_LINE_COMMENT") return std::make_shared<FindMultiLineComment>();
    else if (finderName == "FIND_SINGLE_LINE_COMMENT") return std::make_shared<FindSingleLineComment>();
    else if (finderName == "FIND_SQUEEZED_PARENTHESIS") return std::make_shared<FindSqueezedParenthesis>();
    else if (finderName == "FIND_STRING_SCOPE") return std::make_shared<FindStringScope>();
    else if (finderName == "FIND_TRAILING_BRACE") return std::make_shared<FindTrailingBrace>();
    else if (finderName == "FIND_TRAILING_SPACE") return std::make_shared<FindTrailingSpace>();
    else std::exit(ExitCode::INVALID_FINDER_NAME);
}
