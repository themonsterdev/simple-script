#include "parser/statement/rule/variable/variable_declaration_statement_rule.hpp"
#include "parser/expression/expression_parser.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include "parser/exception/syntax_exception.hpp"
#include "ast/statement/variable/variable_declaration_statement.hpp"

bool FVariableDeclarationStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "var");
}

StatementPtr FVariableDeclarationStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    const auto& token = lexer.GetNextToken();

    if (!token.IsSameType(eTokenType::Identifier))
    {
        throw FSyntaxException("Expected identifier after 'var' keyword.");
    }

    const auto& identifier = token.GetLexeme();

    std::string type;
    if (lexer.TryConsumeToken(eTokenType::Delimiter, ":"))
    {
        const auto& typeToken = lexer.GetNextToken();
        if (!typeToken.IsSameType(eTokenType::Identifier))
        {
            throw FSyntaxException("Expected type identifier after ':' in variable declaration.");
        }
        type = typeToken.GetLexeme();
    }

    ExpressionPtr initializer = nullptr;
    if (lexer.TryConsumeToken(eTokenType::Operator, "="))
    {
        initializer = expressionParser.ParseExpression();
    }

    return std::make_unique<FVariableDeclarationStatement>(
        identifier,
        type,
        std::move(initializer)
    );
}
