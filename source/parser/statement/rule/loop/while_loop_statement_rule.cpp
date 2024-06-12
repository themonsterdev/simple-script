#include "parser/statement/rule/loop/while_loop_statement_rule.hpp"
#include "ast/statement/loop/while_loop_statement.hpp"

#include "ast/statement/block/block_statement.hpp"
#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"
#include "lexer/lexer.hpp"

static StatementPtr ParseWhileBlockStatement(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
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

bool FWhileLoopStatementRule::Match(FLexer& lexer) const
{
	return lexer.TryConsumeToken(eTokenType::Keyword, "while");
}

StatementPtr FWhileLoopStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
	// Parse the condition expression
	auto condition = expressionParser.ParseExpression();

    // Consume the 'then' keyword
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "while"))
    {
        // throw error
    }

	// Parse the body of the while loop
	auto body = ParseWhileBlockStatement(lexer, statementParser, expressionParser);

    // Consume the 'end' keyword
    if (lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        // throw error
    }

	// Create and return the while loop statement
	return std::make_unique<FWhileLoopStatement>(std::move(condition), std::move(body));
}
