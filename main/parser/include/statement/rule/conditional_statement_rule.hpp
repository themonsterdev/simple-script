#pragma once

#include "statement/interface/statement_rule.hpp"

class FConditionalStatementRule final : public IStatementRule
{
public:

    bool Match(FLexer& lexer) const override;

    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
