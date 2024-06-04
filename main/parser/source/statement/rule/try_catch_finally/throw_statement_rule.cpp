#include "statement/rule/try_catch_finally/throw_statement_rule.hpp"
#include "statement/try_catch_finally/throw_statement.hpp"

#include "exception/syntax_exception.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"

bool FThrowStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Keyword && token.lexeme == "throw";
}

StatementPtr FThrowStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Consume the 'throw' token
    lexer.GetNextToken();

    // Parse the expression following the 'throw' keyword
    auto expression = expressionParser.ParseExpression();

    // Create and return the throw statement
    return std::make_unique<FThrowStatement>(std::move(expression));
}
