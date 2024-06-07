/**
 * @file return_statement.cpp
 * @brief Implementation of the return statement class.
 */

#include "statement/rule/control_flow/return_statement_rule.hpp"
#include "statement/control_flow/return_statement.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"

bool FReturnStatementRule::Match(FLexer& lexer) const
{
	const auto& token = lexer.PeekNextToken();
	return token.type == eTokenType::Keyword && token.lexeme == "return";
}

StatementPtr FReturnStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume the 'return' keyword
    lexer.GetNextToken();

    // Parse the expression after 'return'
    ExpressionPtr returnExpression = expressionParser.ParseExpression();

    // Create and return the ReturnStatement object
    return std::make_unique<FReturnStatement>(std::move(returnExpression));
}
