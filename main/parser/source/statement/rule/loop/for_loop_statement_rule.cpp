#include "statement/rule/loop/for_loop_statement_rule.hpp"
#include "lexer.hpp"

bool FForLoopStatementRule::Match(FLexer& lexer) const
{
	const auto& token = lexer.PeekNextToken();

	if (token.type == eTokenType::Keyword)
	{
		if (token.lexeme == "for")
		{
			return true;
		}
	}

	return false;
}

StatementPtr FForLoopStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
	return nullptr;
}
