#pragma once

#include "parser/statement/interface/statement_rule.hpp"

class FVarDeclarationListStatementRule final : public IStatementRule
{
public:

    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
