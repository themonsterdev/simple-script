#include "parser/statement/rule/conditional/conditional_statement_rule.hpp"
#include "ast/statement/block/block_statement.hpp"
#include "ast/statement/conditional/conditional_statement.hpp"

#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

static StatementPtr ParseIfBlockStatement(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (lexer.HasNextToken())
    {
        const auto& token = lexer.PeekNextToken();

        if (token.IsSameType(eTokenType::End))
        {
            break;
        }
        else if (token.IsSameType(eTokenType::Keyword))
        {
            if (token.IsSameLexeme("end"))
            {
                break;
            }
            else if (token.IsSameLexeme("else if"))
            {
                break;
            }
            else if (token.IsSameLexeme("else"))
            {
                break;
            }
        }

        StatementPtr statement = statementParser.ParseStatement();

        if (statement)
        {
            statements.push_back(std::move(statement));
        }
        else
        {
            break;
        }
    }

    return std::make_unique<FBlockStatement>(std::move(statements));
}

bool FConditionalStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "if");
}

StatementPtr FConditionalStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Parse the conditional expression
    auto conditionExpression = expressionParser.ParseExpression();

    // Ensure 'then' follows the condition
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "then"))
    {
        throw FSyntaxException("Expected 'then' keyword after the condition");
    }

    // Parse the main statement (then)
    auto thenStatement = ParseIfBlockStatement(lexer, statementParser, expressionParser);

    // Create the conditional statement
    auto conditionalStatement = std::make_unique<FConditionalStatement>(
        std::move(conditionExpression),
        std::move(thenStatement)
    );

    // Parse 'else if' blocks
    while (lexer.TryConsumeToken(eTokenType::Keyword, "else if"))
    {
        auto elseIfCondition = expressionParser.ParseExpression();

        // Ensure 'then' follows the else if condition
        if (!lexer.TryConsumeToken(eTokenType::Keyword, "then"))
        {
            throw FSyntaxException("Expected 'then' keyword after the 'else if' condition");
        }

        auto elseIfStatement = ParseIfBlockStatement(lexer, statementParser, expressionParser);

        conditionalStatement->AddElseIfStatement(
            std::make_unique<FConditionalStatement>(
                std::move(elseIfCondition),
                std::move(elseIfStatement)
            )
        );
    }

    // Parse 'else' block
    if (lexer.TryConsumeToken(eTokenType::Keyword, "else"))
    {
        auto elseStatement = ParseIfBlockStatement(lexer, statementParser, expressionParser);
        conditionalStatement->SetElseStatement(std::move(elseStatement));

        // Ensure 'end' terminates the conditional
        if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
        {
            throw FSyntaxException("Expected 'end' after 'else' statement block");
        }
    }
    // Ensure 'end' terminates the conditional
    else if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        throw FSyntaxException("Expected 'end' after 'if' statement block");
    }

    return conditionalStatement;
}
