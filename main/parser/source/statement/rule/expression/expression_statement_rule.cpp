#include "statement/rule/expression/expression_statement_rule.hpp"
#include "statement/expression/expression_statement.hpp"

#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"

#include "exception/syntax_exception.hpp"
#include "lexer.hpp"

bool FExpressionStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Identifier
        || token.type == eTokenType::Keyword;
}

StatementPtr FExpressionStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    auto expression = expressionParser.ParseExpression();

    return std::make_unique<FExpressionStatement>(std::move(expression));
}
