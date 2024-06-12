#include "parser/statement/rule/loop/for_loop_statement_rule.hpp"
#include "lexer/lexer.hpp"

bool FForLoopStatementRule::Match(FLexer& lexer) const
{
	return lexer.TryConsumeToken(eTokenType::Keyword, "for");
}

StatementPtr FForLoopStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
	return nullptr;
}
