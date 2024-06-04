#include "statement/rule/invokable/call_statement_rule.hpp"
#include "statement/invokable/call_statement.hpp"

#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"

#include "exception/syntax_exception.hpp"
#include "lexer.hpp"

bool FCallStatementRule::Match(FLexer& lexer) const
{
    lexer.BeginNextToken();

    // Check if the next token is an identifier
    const auto& token = lexer.PeekNextToken();

    if (token.type == eTokenType::Identifier || token.type == eTokenType::Keyword)
    {
        lexer.GetNextToken();

        // Check if the identifier is followed by a left parenthesis
        const auto& nextToken = lexer.PeekNextToken();

        if (nextToken.type == eTokenType::Delimiter && nextToken.lexeme == "(")
        {
            lexer.EndNextToken();
            return true;
        }
    }

    lexer.EndNextToken();
    return false;
}

StatementPtr FCallStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Parse the function call expression
    ExpressionPtr functionCall = expressionParser.ParseExpression();

    // Return the call statement with the parsed function call
    return std::make_unique<FCallStatement>(std::move(functionCall));
}
