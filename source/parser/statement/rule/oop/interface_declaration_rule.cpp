#include "parser/statement/rule/oop/interface_declaration_rule.hpp"

#include "ast/statement/oop/interface/interface_declaration_statement.hpp"
#include "ast/statement/oop/interface/interface_method_declaration_statement.hpp"

#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"

#include "lexer/lexer.hpp"

bool FInterfaceDeclarationRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "interface");
}

StatementPtr FInterfaceDeclarationRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Expect the interface name
    const auto& interfaceNameToken = lexer.GetNextToken();
    if (!interfaceNameToken.IsSameType(eTokenType::Identifier))
    {
        throw FSyntaxException("Expected interface name after 'interface' keyword.");
    }

    const auto& interfaceName = interfaceNameToken.GetLexeme();

    // interface methods
    StatementList methods;
    while (lexer.TryConsumeToken(eTokenType::Keyword, "function"))
    {
        const auto& methodNameToken = lexer.GetNextToken();

        if (!methodNameToken.IsSameType(eTokenType::Identifier))
        {
            throw FSyntaxException("Expected method name after 'function' keyword.");
        }

        std::string methodName = methodNameToken.GetLexeme();

        FunctionParameters parameters;
        if (!lexer.TryConsumeToken(eTokenType::Delimiter, "("))
        {
            throw FSyntaxException("Expected delimiter '(' after method identifier.");
        }

        while (lexer.HasNextToken())
        {
            const auto& token = lexer.PeekNextToken();

            if (token.IsSameType(eTokenType::Identifier))
            {
                const auto& parameterName = token.GetLexeme();
                FFunctionParameter parameter(parameterName, "any");
                parameters.push_back(parameter);
            }
            else if (token.IsSameLexeme(","))
            {
                lexer.GetNextToken();
            }
            else
            {
                break;
            }
        }

        if (!lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
        {
            throw FSyntaxException("Expected delimiter ')' after method parameters.");
        }

        auto methodStatement = std::make_unique<FInterfaceMethodDeclarationStatement>(
            "public",
            "void",
            methodName,
            parameters
        );
        methods.push_back(std::move(methodStatement));
    }

    if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        throw FSyntaxException("Expected keyword 'end' after interface.");
    }

    return std::make_unique<FInterfaceDeclarationStatement>(
        interfaceName,
        std::move(methods)
    );
}
