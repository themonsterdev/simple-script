#pragma once

#include "parser/statement/interface/statement_rule.hpp"

class FEnumDeclarationStatementRule final : public IStatementRule
{
public:

    bool Match(FLexer& lexer) const override;

    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
