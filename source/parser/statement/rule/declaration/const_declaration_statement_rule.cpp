#include "parser/statement/rule/declaration/const_declaration_statement_rule.hpp"
#include "parser/expression/expression_parser.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include "parser/exception/syntax_exception.hpp"
#include "ast/statement/declaration/const_declaration_statement.hpp"
#include "ast/statement/declaration/var_declaration_list_statement.hpp"

bool FConstDeclarationStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "const");
}

StatementPtr FConstDeclarationStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    StatementVector declarations;

    // Get the first token, which should be an identifier
    const auto& idToken = lexer.GetNextToken();

    // Check if the token is an identifier
    if (!idToken.IsSameType(eTokenType::Identifier))
    {
        // Throw an error if the token is not an identifier
        throw FSyntaxException("Expected identifier after 'const'");
    }

    // Store the identifier
    const auto& identifier = idToken.GetLexeme();

    // Initial declaration with the first identifier
    ExpressionPtr expression = nullptr;

    // Check if the next token is '='
    if (lexer.TryConsumeToken(eTokenType::Operator, "="))
    {
        // Parse the expression on the right side of the assignment
        expression = expressionParser.ParseExpression();
    }

    // Add the first declaration
    declarations.push_back(std::make_unique<FConstDeclarationStatement>(identifier, std::move(expression)));

    // Parse any additional declarations
    while (lexer.TryConsumeToken(eTokenType::Delimiter, ","))
    {
        // Get the next token, which should be an identifier
        const auto& idToken = lexer.GetNextToken();

        // Check if the token is an identifier
        if (!idToken.IsSameType(eTokenType::Identifier))
        {
            // Throw an error if the token is not an identifier
            throw FSyntaxException("Expected identifier after ',' delimiter");
        }

        // Store the identifier
        const auto& identifier = idToken.GetLexeme();

        // Reset expression for the new declaration
        expression = nullptr;

        // Check if the next token is '='
        if (lexer.TryConsumeToken(eTokenType::Operator, "="))
        {
            // Parse the expression on the right side of the assignment
            expression = expressionParser.ParseExpression();
        }

        // Add the declaration
        declarations.push_back(
            std::make_unique<FConstDeclarationStatement>(
                identifier,
                std::move(expression)
            )
        );
    }

    if (declarations.size() == 1)
    {
        return std::move(declarations.front());
    }

    // Return a unique pointer to the FVarDeclarationListStatement with the list of declarations
    return std::make_unique<FVarDeclarationListStatement>(std::move(declarations));
}
