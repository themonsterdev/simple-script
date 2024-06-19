#include "parser/statement/rule/function/function_statement_rule.hpp"
#include "ast/statement/function/function_declaration_statement.hpp"
#include "type/function/function_definition.hpp"

#include "ast/statement/block/block_statement.hpp"

#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"

#include "parser/exception/syntax_exception.hpp"
#include "lexer/lexer.hpp"

bool FFunctionStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "function");
}

StatementPtr FFunctionStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Parse function name
    const auto& functionNameToken = lexer.GetNextToken();
    if (!functionNameToken.IsSameType(eTokenType::Identifier))
    {
        throw FSyntaxException("Expected function name after 'function' keyword");
    }
    const auto& functionName = functionNameToken.GetLexeme();

    if (!lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    {
        throw FSyntaxException("Expected '(' after function name");
    }

    // Parse function parameters (if any)
    std::vector<std::string> parameters;
    while (lexer.HasNextToken())
    {
        const auto& nextToken = lexer.PeekNextToken();

        if (nextToken.IsSameType(eTokenType::Keyword) || nextToken.IsSameType(eTokenType::Identifier))
        {
            lexer.GetNextToken();

            parameters.push_back(nextToken.GetLexeme());
        }
        else if (nextToken.IsSameLexeme(","))
        {
            lexer.GetNextToken();

            // If there's no comma, break the loop
            continue;
        }
        else
        {
            // If there's no unknow, break the loop
            break;
        }
    }

    // Consume ')'
    if (!lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
    {
        throw FSyntaxException("Expected ')' after function parameters");
    }

    // Parse function body (statements inside the function)
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "then"))
    {
        throw FSyntaxException("Expected 'then' keyword before function body");
    }

    StatementList statements;
    while (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        auto statement = statementParser.ParseStatement();

        if (statement)
        {
            statements.push_back(std::move(statement));
        }
        else
        {
            break;
        }
    }

    std::string returnType = "void";

    auto body = std::make_unique<FBlockStatement>(std::move(statements));

    const auto& functionDefinition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        std::move(body)
    );

    // Create and return a FunctionDeclaration statement
    return std::make_unique<FFunctionDeclarationStatement>(functionDefinition);
}
