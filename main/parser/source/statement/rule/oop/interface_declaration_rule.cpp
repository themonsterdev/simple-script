#include "statement/rule/oop/interface_declaration_rule.hpp"

#include "statement/oop/interface/interface_declaration_statement.hpp"
#include "statement/oop/interface/interface_method_declaration_statement.hpp"

#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"
#include "exception/syntax_exception.hpp"

#include "lexer.hpp"

bool FInterfaceDeclarationRule::Match(FLexer& lexer) const
{
    return lexer.MatchToken(eTokenType::Keyword, "interface");
}

StatementPtr FInterfaceDeclarationRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    if (!Match(lexer))
    {
        throw FSyntaxException("Unexpected token in 'interface' parser.");
    }
    
    // Consume the 'interface' keyword
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "interface"))
    {
        throw FSyntaxException("Expected keyword 'interface'.");
    }

    // Expect the interface name
    const auto& interfaceNameToken = lexer.GetNextToken();
    if (interfaceNameToken.type != eTokenType::Identifier)
    {
        throw FSyntaxException("Expected interface name after 'interface' keyword.");
    }

    const auto& interfaceName = interfaceNameToken.lexeme;

    // interface methods
    StatementList methods;
    while (lexer.TryConsumeToken(eTokenType::Keyword, "function"))
    {
        const auto& methodNameToken = lexer.GetNextToken();

        if (methodNameToken.type != eTokenType::Identifier)
        {
            throw FSyntaxException("Expected method name after 'function' keyword.");
        }

        std::string methodName = methodNameToken.lexeme;

        FunctionParameters parameters;
        if (!lexer.TryConsumeToken(eTokenType::Delimiter, "("))
        {
            throw FSyntaxException("Expected delimiter '(' after method identifier.");
        }

        while (lexer.HasNextToken())
        {
            const auto& token = lexer.PeekNextToken();

            if (token.type == eTokenType::Identifier)
            {
                const auto& parameterName = token.lexeme;
                FFunctionParameter parameter(parameterName, "any");
                parameters.push_back(parameter);
            }
            else if (token.lexeme == ",")
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
