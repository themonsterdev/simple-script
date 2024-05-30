#pragma once

#include "statement/interface/statement_rule.hpp"

class FAssignmentStatementRule final : public IStatementRule
{
public:

    bool Match(FLexer& lexer, FExpressionParser& expressionParser) const override;

    StatementPtr Parse(FLexer& lexer, FExpressionParser& expressionParser) const override;
};
