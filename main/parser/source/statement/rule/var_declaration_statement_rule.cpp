#include "statement/rule/var_declaration_statement_rule.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"

#include "exception/syntax_exception.hpp"
#include "statement/var_declaration_statement.hpp"
#include "statement/var_declaration_list_statement.hpp"

bool FVarDeclarationStatementRule::Match(FLexer& lexer, FExpressionParser& expressionParser) const
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Keyword && token.lexeme == "var";
}

StatementPtr FVarDeclarationStatementRule::Parse(FLexer& lexer, FExpressionParser& expressionParser) const
{
    // Get the next token, which should be 'var'
    SToken varToken = lexer.GetNextToken();

    // Check if the token is 'var'
    if (varToken.type != eTokenType::Keyword || varToken.lexeme != "var")
    {
        // Throw an error if the token is not 'var'
        throw FSyntaxException("Expected 'var'");
    }

    StatementVector declarations;

    // Get the first token, which should be an identifier
    SToken idToken = lexer.GetNextToken();

    // Check if the token is an identifier
    if (idToken.type != eTokenType::Identifier)
    {
        // Throw an error if the token is not an identifier
        throw FSyntaxException("Expected identifier after 'var'");
    }

    // Store the identifier
    std::string identifier = idToken.lexeme;

    // Initial declaration with the first identifier
    ExpressionPtr expression = nullptr;

    // Check if the next token is '='
    if (lexer.HasNextToken())
    {
        SToken nextToken = lexer.PeekNextToken();

        if (nextToken.lexeme == "=")
        {
            lexer.GetNextToken(); // consume token '='

            // Parse the expression on the right side of the assignment
            expression = expressionParser.ParseExpression();
        }
    }

    // Add the first declaration
    declarations.push_back(std::make_unique<FVarDeclarationStatement>(identifier, std::move(expression)));

    // Parse any additional declarations
    while (lexer.HasNextToken())
    {
        // Peek the next token to see if it is a comma
        SToken nextToken = lexer.PeekNextToken();

        if (nextToken.lexeme == ",")
        {
            lexer.GetNextToken(); // consume token ','

            // Get the next token, which should be an identifier
            SToken idToken = lexer.GetNextToken();

            // Check if the token is an identifier
            if (idToken.type != eTokenType::Identifier)
            {
                // Throw an error if the token is not an identifier
                throw FSyntaxException("Expected identifier after ',', received " + idToken.lexeme);
            }

            // Store the identifier
            std::string identifier = idToken.lexeme;

            // Reset expression for the new declaration
            expression = nullptr;

            // Check if the next token is '='
            if (lexer.HasNextToken())
            {
                nextToken = lexer.PeekNextToken();

                if (nextToken.lexeme == "=")
                {
                    lexer.GetNextToken(); // consume token '='

                    // Parse the expression on the right side of the assignment
                    expression = expressionParser.ParseExpression();
                }
            }

            // Add the declaration
            declarations.push_back(std::make_unique<FVarDeclarationStatement>(identifier, std::move(expression)));
        }
        else
        {
            // If no comma is found, end parsing
            break;
        }
    }

    // Return a unique pointer to the FVarDeclarationListStatement with the list of declarations
    return std::make_unique<FVarDeclarationListStatement>(std::move(declarations));
}
