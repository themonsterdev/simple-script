#include "parser/statement/rule/loop/continue_statement_rule.hpp"
#include "ast/statement/loop/continue_statement.hpp"

#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"
#include "lexer/lexer.hpp"

bool FContinueStatementRule::Match(FLexer& lexer) const
{
	return lexer.TryConsumeToken(eTokenType::Keyword, "continue");
}

StatementPtr FContinueStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Create and return the continue statement
    return std::make_unique<FContinueStatement>();
}
