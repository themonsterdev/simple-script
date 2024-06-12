#pragma once

#include "parser/statement/interface/statement_rule.hpp"
#include "ast/statement/try_catch_finally/try_catch_finally_statement.hpp"

class FTryCatchFinallyStatementRule : public IStatementRule
{
public:

    bool Match(FLexer& lexer) const override;
    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
