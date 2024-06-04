#include "statement/rule/try_catch_finally/try_catch_finally_statement_rule.hpp"

#include "exception/syntax_exception.hpp"
#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"

static StatementPtr ParseTryCatchFinnalyStatements(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (lexer.HasNextToken())
    {
        const auto& token = lexer.PeekNextToken();

        if (token.type == eTokenType::Keyword && token.lexeme == "catch")
        {
            // If another 'catch' is encountered, stop parsing case statements
            break;
        }

        if (token.type == eTokenType::Keyword && token.lexeme == "finally")
        {
            // If another 'finally' is encountered, stop parsing case statements
            break;
        }

        if (token.type == eTokenType::Keyword && token.lexeme == "end")
        {
            // If another 'end' is encountered, stop parsing case statements
            break;
        }

        // Parse the next statement in the case
        auto statement = statementParser.ParseStatement();

        if (statement)
        {
            statements.push_back(std::move(statement));
        }
        else
        {
            // If parsing fails, throw an error or handle it accordingly
            break;
        }
    }

    return std::make_unique<FBlockStatement>(std::move(statements));
}

bool FTryCatchFinallyStatementRule::Match(FLexer& lexer) const 
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Keyword && token.lexeme == "try";
}

StatementPtr FTryCatchFinallyStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume the 'try' token
    lexer.GetNextToken();

    // Parse the try block
    auto tryBlock = ParseTryCatchFinnalyStatements(lexer, statementParser, expressionParser);

    // Parse the catch block
    StatementPtr catchBlock = nullptr;
    std::string errorVariable;
    if (lexer.TryConsumeToken(eTokenType::Keyword, "catch"))
    {
        // Get the error variable
        const auto& nextToken = lexer.GetNextToken();
        if (nextToken.type == eTokenType::Identifier)
        {
            errorVariable = nextToken.lexeme;
        }
        else
        {
            throw FSyntaxException("Expected identifier for error variable in catch block");
        }

        // Parse the catch block
        catchBlock = ParseTryCatchFinnalyStatements(lexer, statementParser, expressionParser);
    }

    // Parse the finally block
    StatementPtr finallyBlock = nullptr;
    if (lexer.TryConsumeToken(eTokenType::Keyword, "finally"))
    {
        // Parse the finally block
        finallyBlock = ParseTryCatchFinnalyStatements(lexer, statementParser, expressionParser);
    }

    // Consume the 'end' token
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        throw FSyntaxException("Expected 'end' after try-catch-finally statement");
    }

    // Create and return the try-catch-finally statement
    return std::make_unique<FTryCatchFinallyStatement>(
        std::move(tryBlock),
        std::move(errorVariable),
        std::move(catchBlock),
        std::move(finallyBlock)
    );
}
