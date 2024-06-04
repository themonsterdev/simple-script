#include "statement/rule/assert/assert_statement_rule.hpp"
#include "statement/assert/assert_statement.hpp"

#include "expression/expression_parser.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "exception/syntax_exception.hpp"

bool FAssertStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();

    if (token.type == eTokenType::Keyword)
    {
        if (token.lexeme == "assert")
        {
            return true;
        }
    }

    return false;
}

StatementPtr FAssertStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume the 'assert' token
    lexer.GetNextToken();

    // Check for the opening parenthesis before the expression
    if (!lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    {
        throw FSyntaxException("Expected '(' after 'assert' keyword");
    }

    // Parse the expression after '('
    ExpressionPtr expression = expressionParser.ParseExpression();

    // Check if there is an optional message after the expression
    const auto& token = lexer.PeekNextToken();
    std::string errorMessage;
    if (lexer.TryConsumeToken(eTokenType::Delimiter, ","))
    {
        // Check if the next token is a string literal or string format literal
        const auto& nextToken = lexer.PeekNextToken();
        if (nextToken.type == eTokenType::String || nextToken.type == eTokenType::StringFormatLiteral)
        {
            errorMessage = nextToken.lexeme; // Assign the string literal as the error message

            // Consume the string literal token
            lexer.GetNextToken();
        }
        else
        {
            // Throw syntax error if the token after the comma is not a string literal or format literal
            throw FSyntaxException("Expected string literal or format literal after ',' in assert statement");
        }
    }

    // Check if there is a closing parenthesis
    if (!lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
    {
        // Throw syntax error if there is no closing parenthesis
        throw FSyntaxException("Expected ')' after the error message in assert statement");
    }

    // Return the assert statement with the parsed expression and optional error message
    return std::make_unique<FAssertStatement>(std::move(expression), errorMessage);
}
