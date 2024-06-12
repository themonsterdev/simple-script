#pragma once

#include "parser/statement/interface/statement_rule.hpp"

class FContinueStatementRule final : public IStatementRule
{
public:

    bool Match(FLexer& lexer) const override;

    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
