#pragma once

#include "statement/interface/statement_rule.hpp"

class FBlockStatementRule final : public IStatementRule
{
public:

    bool Match(FLexer& parser) const override;

    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
