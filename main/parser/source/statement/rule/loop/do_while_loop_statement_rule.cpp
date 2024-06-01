#include "statement/rule/loop/do_while_loop_statement_rule.hpp"
#include "statement/loop/do_while_loop_statement.hpp"
#include "statement/block/block_statement.hpp"
#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"
#include "exception/syntax_exception.hpp"
#include "lexer.hpp"

static StatementPtr ParseDoWhileBlockStatement(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
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
            else if (token.lexeme == "while")
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

bool FDoWhileLoopStatementRule::Match(FLexer& lexer) const
{
	const auto& token = lexer.PeekNextToken();

	if (token.type == eTokenType::Keyword)
	{
		if (token.lexeme == "do")
		{
			return true;
		}
	}

	return false;
}

StatementPtr FDoWhileLoopStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume the 'do' keyword
    lexer.GetNextToken();

    // Parse the body of the do-while loop
    auto body = ParseDoWhileBlockStatement(lexer, statementParser, expressionParser);

    // Check for the 'while' keyword
    const auto& whileToken = lexer.GetNextToken();
    if (whileToken.type != eTokenType::Keyword || whileToken.lexeme != "while")
    {
        throw FSyntaxException("Expected 'while' keyword after 'do'");
    }

    // Parse the condition expression
    auto condition = expressionParser.ParseExpression();

    // Create and return the do-while loop statement
    return std::make_unique<FDoWhileLoopStatement>(std::move(body), std::move(condition));
}
