#include "parser/statement/rule/loop/do_while_loop_statement_rule.hpp"
#include "ast/statement/loop/do_while_loop_statement.hpp"
#include "ast/statement/block/block_statement.hpp"
#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"
#include "lexer/lexer.hpp"

static StatementPtr ParseDoBlockStatement(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (!lexer.MatchToken(eTokenType::Keyword, "while"))
    {
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

bool FDoWhileLoopStatementRule::Match(FLexer& lexer) const
{
	return lexer.TryConsumeToken(eTokenType::Keyword, "do");
}

StatementPtr FDoWhileLoopStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Parse the body of the do-while loop
    auto body = ParseDoBlockStatement(lexer, statementParser, expressionParser);

    // Check for the 'while' keyword
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "while"))
    {
        throw FSyntaxException("Expected 'while' keyword after 'do'");
    }

    // Parse the condition expression
    auto condition = expressionParser.ParseExpression();

    // Create and return the do-while loop statement
    return std::make_unique<FDoWhileLoopStatement>(std::move(body), std::move(condition));
}
