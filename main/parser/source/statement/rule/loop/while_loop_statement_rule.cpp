#include "statement/rule/loop/while_loop_statement_rule.hpp"
#include "statement/loop/while_loop_statement.hpp"

#include "statement/block/block_statement.hpp"
#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"
#include "exception/syntax_exception.hpp"
#include "lexer.hpp"

static StatementPtr ParseWhileBlockStatement(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (lexer.HasNextToken())
    {
        const auto& token = lexer.PeekNextToken();

        if (token.type == eTokenType::End)
        {
            break;
        }
        else if (token.type == eTokenType::Keyword)
        {
            if (token.lexeme == "end")
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

bool FWhileLoopStatementRule::Match(FLexer& lexer) const
{
	const auto& token = lexer.PeekNextToken();

	if (token.type == eTokenType::Keyword)
	{
		if (token.lexeme == "while")
		{
			return true;
		}
	}

	return false;
}

StatementPtr FWhileLoopStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
	// Consume the 'while' keyword
	lexer.GetNextToken();

	// Parse the condition expression
	auto condition = expressionParser.ParseExpression();

    // Consume the 'then' keyword
    lexer.GetNextToken();

	// Parse the body of the while loop
	auto body = ParseWhileBlockStatement(lexer, statementParser, expressionParser);

    // Consume the 'end' keyword
    lexer.GetNextToken();

	// Create and return the while loop statement
	return std::make_unique<FWhileLoopStatement>(std::move(condition), std::move(body));
}
