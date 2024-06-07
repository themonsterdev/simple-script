#include "statement/rule/function/function_statement_rule.hpp"
#include "statement/function/function_statement.hpp"

#include "statement/block/block_statement.hpp"

#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"

#include "exception/syntax_exception.hpp"
#include "lexer.hpp"

bool FFunctionStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Keyword && token.lexeme == "function";
}

StatementPtr FFunctionStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume token 'function'
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "function"))
    {
        throw FSyntaxException("Expected 'function' keyword for function declaration");
    }

    // Parse function name
    const auto& functionNameToken = lexer.GetNextToken();
    if (functionNameToken.type != eTokenType::Identifier)
    {
        throw FSyntaxException("Expected function name after 'function' keyword");
    }
    std::string functionName = functionNameToken.lexeme;

    if (!lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    {
        throw FSyntaxException("Expected '(' after function name");
    }

    // Parse function parameters (if any)
    FunctionParameters parameters;
    while (lexer.HasNextToken())
    {
        const auto& nextToken = lexer.PeekNextToken();

        if (nextToken.type == eTokenType::Keyword || nextToken.type == eTokenType::Identifier)
        {
            lexer.GetNextToken();

            parameters.push_back({ nextToken.lexeme, "void" });
        }
        else if (nextToken.lexeme == ",")
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

    StatementPtr body = std::make_unique<FBlockStatement>(std::move(statements));

    // Create and return a FunctionDeclaration statement
    return std::make_unique<FFunctionStatement>(functionName, parameters, std::move(body));
}
