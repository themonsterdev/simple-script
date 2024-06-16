#include "parser/statement/rule/declaration/var_declaration_list_statement_rule.hpp"

bool FVarDeclarationListStatementRule::Match(FLexer& lexer) const
{
	return false;
}

StatementPtr FVarDeclarationListStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
	return nullptr;
}
