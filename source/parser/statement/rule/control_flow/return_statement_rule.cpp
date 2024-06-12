/**
 * @file return_statement.cpp
 * @brief Implementation of the return statement class.
 */

#include "parser/statement/rule/control_flow/return_statement_rule.hpp"
#include "ast/statement/control_flow/return_statement.hpp"
#include "parser/expression/expression_parser.hpp"
#include "lexer/lexer.hpp"

bool FReturnStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "return");
}

StatementPtr FReturnStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Parse the expression after 'return'
    ExpressionPtr returnExpression = expressionParser.ParseExpression();

    // Create and return the ReturnStatement object
    return std::make_unique<FReturnStatement>(std::move(returnExpression));
}
