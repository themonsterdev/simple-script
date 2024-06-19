#include "parser/statement/rule/oop/class_declaration_rule.hpp"

#include "ast/statement/oop/class/class_declaration_statement.hpp"
#include "ast/statement/oop/member_declaration_statement.hpp"

#include "type/oop/class_definition.hpp"

#include "ast/statement/block/block_statement.hpp"

#include "parser/statement/statement_parser.hpp"
#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"

#include "lexer/lexer.hpp"

static BlockStatementPtr ParseClassBody(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (!lexer.MatchToken(eTokenType::Keyword, "end"))
    {
        // Default visibility
        Visibility visibility = Visibility::Private;

        if (lexer.TryConsumeToken(eTokenType::Keyword, "private"))
        {
            // default private !
            // visibility = Visibility::Private;
        }
        else if (lexer.TryConsumeToken(eTokenType::Keyword, "protected"))
        {
            visibility = Visibility::Protected;
        }
        else if (lexer.TryConsumeToken(eTokenType::Keyword, "public"))
        {
            visibility = Visibility::Public;
        }

        auto statement = statementParser.ParseStatement();

        if (statement)
        {
            auto member = std::make_unique<FMemberDeclarationStatement>(
                visibility,
                std::move(statement)
            );

            statements.push_back(std::move(member));
        }
        else
        {
            break;
        }
    }

    return std::make_unique<FBlockStatement>(std::move(statements));
}

static StatementPtr ParseClassDeclaration(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    // Expect the class name
    const auto& classNameToken = lexer.GetNextToken();
    if (!classNameToken.IsSameType(eTokenType::Identifier))
    {
        throw FSyntaxException("Expected class name after 'class' keyword.");
    }

    const auto& className = classNameToken.GetLexeme();

    const auto& classDefinition = std::make_shared<FClassDefinition>(className);

    // Consume the 'extends' keyword
    if (lexer.TryConsumeToken(eTokenType::Keyword, "extends"))
    {
        const auto& parentClasFToken = lexer.GetNextToken();
        if (!parentClasFToken.IsSameType(eTokenType::Identifier))
        {
            throw FSyntaxException("Expected class name after 'extends' keyword.");
        }

        classDefinition->SetParent(parentClasFToken.GetLexeme());
    }

    // Consume the 'implements' keyword
    if (lexer.TryConsumeToken(eTokenType::Keyword, "implements"))
    {
        const auto& interfaceToken = lexer.GetNextToken();
        if (!interfaceToken.IsSameType(eTokenType::Identifier))
        {
            throw FSyntaxException("Expected interface name after 'implements' keyword.");
        }

        classDefinition->AddInterface(interfaceToken.GetLexeme());

        while (lexer.TryConsumeToken(eTokenType::Delimiter, ","))
        {
            const auto& interfaceToken = lexer.GetNextToken();
            if (!interfaceToken.IsSameType(eTokenType::Identifier))
            {
                throw FSyntaxException("Expected interface name after ',' keyword.");
            }

            classDefinition->AddInterface(interfaceToken.GetLexeme());
        }
    }

    auto classBody = ParseClassBody(lexer, statementParser, expressionParser);

    return std::make_unique<FClassDeclarationStatement>(
        classDefinition,
        std::move(classBody)
    );
}

static StatementPtr ParseTraitDeclaration(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    // Expect the trait name
    const auto& traitNameToken = lexer.GetNextToken();
    if (!traitNameToken.IsSameType(eTokenType::Identifier))
    {
        throw FSyntaxException("Expected trait name after 'trait' keyword.");
    }

    const auto& traitName = traitNameToken.GetLexeme();

    // ExpectToken("then");
    // ParseTraitBody();
    // ExpectToken("end");
    // 
    // RegisterTrait(traitName);

    return nullptr;
}

bool FClassDeclarationRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();

    if (token.IsSameType(eTokenType::Keyword))
    {
        if (token.IsSameLexeme("class"))
        {
            return true;
        }
        else if (token.IsSameLexeme("abstract"))
        {
            return true;
        }
        else if (token.IsSameLexeme("trait"))
        {
            return true;
        }
    }

    return false;
}

StatementPtr FClassDeclarationRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    StatementPtr statement = nullptr;
    const auto& token = lexer.PeekNextToken();

    if (lexer.TryConsumeToken(eTokenType::Keyword, "class"))
    {
        statement = ParseClassDeclaration(lexer, statementParser, expressionParser);
    }
    else if (lexer.TryConsumeToken(eTokenType::Keyword, "abstract"))
    {
        if (!lexer.TryConsumeToken(eTokenType::Keyword, "class"))
        {
            throw FSyntaxException("Expected keyword 'class' after 'abstract' keyword.");
        }

        statement = ParseClassDeclaration(lexer, statementParser, expressionParser);
    }
    else if (lexer.TryConsumeToken(eTokenType::Keyword, "trait"))
    {
        statement = ParseClassDeclaration(lexer, statementParser, expressionParser);
    }
    else
    {
        throw FSyntaxException("Unexpected token in class parser.");
    }

    if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        throw FSyntaxException("Expected keyword 'end' after " + token.GetLexeme());
    }

    return statement;
}
