#pragma once

#include "statement/interface/statement_rule.hpp"

class FVarDeclarationListStatementRule final : public IStatementRule
{
public:

    StatementPtr Parse(FLexer& lexer, FExpressionParser& expressionParser) const override;
};
