#include "statement/rule/oop/class_declaration_rule.hpp"

#include "statement/oop/class/class_declaration_statement.hpp"
#include "statement/oop/class/class_method_declaration_statement.hpp"
#include "statement/oop/property_declaration_statement.hpp"

#include "oop/class_definition.hpp"
#include "oop/class_property_definition.hpp"
#include "oop/class_method_definition.hpp"

#include "statement/block/block_statement.hpp"

#include "statement/statement_parser.hpp"
#include "expression/expression_parser.hpp"
#include "exception/syntax_exception.hpp"

#include "lexer.hpp"

static StatementPtr ParseProperty(Visibility visibility, FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    lexer.GetNextToken(); // Consume 'var' or 'const' keyword

    const auto& propertyNameToken = lexer.GetNextToken();
    if (propertyNameToken.type != eTokenType::Identifier)
    {
        throw FSyntaxException("Expected property name after 'var' keyword.");
    }

    std::string propertyName = propertyNameToken.lexeme;
    ExpressionPtr expression = nullptr;

    if (lexer.TryConsumeToken(eTokenType::Operator, "="))
    {
        expression = expressionParser.ParseExpression();
    }

    const auto& propertyType       = std::make_shared<FType>("any");
    const auto& propertyDefinition = std::make_shared<FClassPropertyDefinition>(
        propertyName,
        propertyType
    );

    return std::make_unique<FPropertyDeclarationStatement>(
        visibility,
        propertyDefinition,
        std::move(expression)
    );
}

static StatementPtr ParseMethod(Visibility visibility, FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    // Consume 'function' keyword
    lexer.GetNextToken();

    // Consume 'identifier'
    const auto& methodNameToken = lexer.GetNextToken();
    if (methodNameToken.type != eTokenType::Identifier)
    {
        throw FSyntaxException("Expected method name after 'function' keyword.");
    }

    // Consume '(' delimiter
    if (!lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    {
        throw FSyntaxException("Expected '(' after method name.");
    }

    // Consume 'identifiers'
    FunctionParameters parameters;
    while (lexer.HasNextToken())
    {
        const auto& token = lexer.PeekNextToken();

        if (token.type == eTokenType::Identifier)
        {
            parameters.push_back({ token.lexeme, "void" });
            lexer.GetNextToken();
            continue;
        }
        else if (token.lexeme == ",")
        {
            lexer.GetNextToken();
            continue;
        }
        else if (token.lexeme == ")")
        {
            break;
        }
        else
        {
            throw FSyntaxException("Invalid token in method parameters.");
        }
    }

    // Consume ')' delimiter
    if (!lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
    {
        throw FSyntaxException("Expected ')' keyword after method name parameters.");
    }

    // Consume 'then' keyword
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "then"))
    {
        throw FSyntaxException("Expected 'then' keyword after method parameters.");
    }

    // Consume 'statements'
    StatementList statements;
    while (lexer.HasNextToken() && !lexer.MatchToken(eTokenType::Keyword, "end"))
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

    if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        throw FSyntaxException("Expected keyword 'end' after method.");
    }

    const auto& returnType       = std::make_shared<FType>("any");
    const auto& methodDefinition = std::make_shared<FClassMethodDefinition>(
        methodNameToken.lexeme,
        returnType,
        parameters
    );

    auto methodBody = std::make_unique<FBlockStatement>(std::move(statements));
    
    auto statement = std::make_unique<FClassMethodDeclarationStatement>(
        visibility,
        methodDefinition,
        std::move(methodBody)
    );

    return statement;
}

static BlockStatementPtr ParseClassBody(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (lexer.HasNextToken())
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

        const auto& token = lexer.PeekNextToken();

        if (token.type == eTokenType::Keyword)
        {
            if (token.lexeme == "var" || token.lexeme == "const")
            {
                auto propertyStatement = ParseProperty(
                    visibility,
                    lexer,
                    statementParser,
                    expressionParser
                );
                if (propertyStatement)
                {
                    statements.push_back(std::move(propertyStatement));
                    continue;
                }
            }
            else if (token.lexeme == "function")
            {
                auto methodStatement = ParseMethod(
                    visibility,
                    lexer,
                    statementParser,
                    expressionParser
                );
                if (methodStatement)
                {
                    statements.push_back(std::move(methodStatement));
                    continue;
                }
            }
            else if (token.lexeme == "class")
            {
                auto classStatement = statementParser.ParseStatement();
                if (classStatement)
                {
                    statements.push_back(std::move(classStatement));
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
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
    if (classNameToken.type != eTokenType::Identifier)
    {
        throw FSyntaxException("Expected class name after 'class' keyword.");
    }

    const auto& className = classNameToken.lexeme;

    const auto& classDefinition = std::make_shared<FClassDefinition>(className);

    // Consume the 'extends' keyword
    if (lexer.TryConsumeToken(eTokenType::Keyword, "extends"))
    {
        const auto& parentClassToken = lexer.GetNextToken();
        if (parentClassToken.type != eTokenType::Identifier)
        {
            throw FSyntaxException("Expected class name after 'extends' keyword.");
        }

        classDefinition->SetParent(parentClassToken.lexeme);
    }

    // Consume the 'implements' keyword
    if (lexer.TryConsumeToken(eTokenType::Keyword, "implements"))
    {
        const auto& interfaceToken = lexer.GetNextToken();
        if (interfaceToken.type != eTokenType::Identifier)
        {
            throw FSyntaxException("Expected interface name after 'implements' keyword.");
        }

        classDefinition->AddInterface(interfaceToken.lexeme);

        while (lexer.TryConsumeToken(eTokenType::Delimiter, ","))
        {
            const auto& interfaceToken = lexer.GetNextToken();
            if (interfaceToken.type != eTokenType::Identifier)
            {
                throw FSyntaxException("Expected interface name after ',' keyword.");
            }

            classDefinition->AddInterface(interfaceToken.lexeme);
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
    if (traitNameToken.type != eTokenType::Identifier)
    {
        throw FSyntaxException("Expected trait name after 'trait' keyword.");
    }

    std::string traitName = traitNameToken.lexeme;

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

    if (token.type == eTokenType::Keyword)
    {
        if (token.lexeme == "class")
        {
            return true;
        }
        else if (token.lexeme == "abstract")
        {
            return true;
        }
        else if (token.lexeme == "trait")
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
        throw FSyntaxException("Expected keyword 'end' after " + token.lexeme);
    }

    return statement;
}
