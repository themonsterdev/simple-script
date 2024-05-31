#pragma once

#include "statement/interface/statement.hpp"
#include <memory>

class FLexer;
class FStatementParser;
class FExpressionParser;

class IStatementRule
{
public:

    virtual ~IStatementRule() = default;

    virtual bool Match(FLexer& lexer) const = 0;

    virtual StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const = 0;
};

using StatementRulePtr    = std::unique_ptr<IStatementRule>;
using StatementRuleVector = std::vector<StatementRulePtr>;
