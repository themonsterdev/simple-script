#include "statement/rule/assignment_statement_rule.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "exception/syntax_exception.hpp"
#include "statement/assignment_statement.hpp"

bool FAssignmentStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Identifier;
}

StatementPtr FAssignmentStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Get the next token, which should be an identifier
    SToken idToken = lexer.GetNextToken();

    // Check if the token is an identifier
    if (idToken.type != eTokenType::Identifier)
    {
        // Throw an error if the token is not an identifier
        throw FSyntaxException("Expected identifier in assignment statement");
    }

    // Store the identifier
    std::string identifier = idToken.lexeme;

    // Get the next token, which should be '='
    SToken equalToken = lexer.GetNextToken();

    // Check if the token is '='
    if (equalToken.lexeme != "=")
    {
        // Throw an error if the token is not '='
        throw FSyntaxException("Expected '=' in assignment statement");
    }

    // Parse the expression on the right side of the assignment
    auto value = expressionParser.ParseExpression();

    // Return a unique pointer to the FAssignmentStatement with the identifier and expression
    return std::make_unique<FAssignmentStatement>(identifier, std::move(value));
}
