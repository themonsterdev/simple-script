#pragma once

#include "parser/statement/interface/statement_rule.hpp"

class FReturnStatementRule : public IStatementRule
{
    bool Match(FLexer& lexer) const override;

    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
