#include "statement/rule/block_statement_rule.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "exception/syntax_exception.hpp"
#include "statement/block_statement.hpp"

bool FBlockStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();

    if (token.type == eTokenType::Keyword)
    {
        if (token.lexeme == "then")
        {
            return true;
        }
    }

    return false;
}

StatementPtr FBlockStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume token 'then' | 'else'
    lexer.GetNextToken();

    StatementList statements;

    while (lexer.HasNextToken())
    {
        const auto& token = lexer.PeekNextToken();

        if (token.type == eTokenType::End)
        {
            break;
        }

        if (token.type == eTokenType::Keyword)
        {
            if (token.lexeme == "end")
            {
                break;
            }
            else if (token.lexeme == "else")
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
