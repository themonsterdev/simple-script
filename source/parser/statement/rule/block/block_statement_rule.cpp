#include "parser/statement/rule/block/block_statement_rule.hpp"
#include "parser/expression/expression_parser.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include "parser/exception/syntax_exception.hpp"
#include "ast/statement/block/block_statement.hpp"

bool FBlockStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "then");
}

StatementPtr FBlockStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    StatementList statements;

    while (!lexer.MatchToken(eTokenType::Keyword, "end"))
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
