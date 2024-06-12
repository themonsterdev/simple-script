#include "parser/statement/rule/expression/expression_statement_rule.hpp"
#include "ast/statement/expression/expression_statement.hpp"

#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"

#include "parser/exception/syntax_exception.hpp"
#include "lexer/lexer.hpp"

bool FExpressionStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();
    return token.IsSameType(eTokenType::Identifier)
        || token.IsSameType(eTokenType::Keyword);
}

StatementPtr FExpressionStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    auto expression = expressionParser.ParseExpression();

    return std::make_unique<FExpressionStatement>(std::move(expression));
}
