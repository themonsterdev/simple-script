#include "statement/rule/loop/continue_statement_rule.hpp"
#include "statement/loop/continue_statement.hpp"

#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"
#include "exception/syntax_exception.hpp"
#include "lexer.hpp"

bool FContinueStatementRule::Match(FLexer& lexer) const
{
	const auto& token = lexer.PeekNextToken();

	if (token.type == eTokenType::Keyword)
	{
		if (token.lexeme == "continue")
		{
			return true;
		}
	}

	return false;
}

StatementPtr FContinueStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume the 'continue' keyword
    lexer.GetNextToken();

    // Create and return the continue statement
    return std::make_unique<FContinueStatement>();
}
