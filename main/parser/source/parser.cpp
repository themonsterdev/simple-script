#include "parser.hpp"
#include "tokenizer.hpp"

// Statement
#include "ast/statement/arithmetic_operator_node.hpp"
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/binary_operator_node.hpp"
#include "ast/statement/print_statement_node.hpp"
#include "ast/statement/string_operator_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

#include <stdexcept>

FParser::FParser(FTokenizer& tokenizer)
	: m_tokenizer(tokenizer)
{}

std::unique_ptr<FSyntaxTree> FParser::Parse()
{
    ASyntaxNodePtr root = std::make_unique<ASyntaxNode>();

    while (m_tokenizer.HasNextToken())
    {
        const SToken& token = m_tokenizer.PeekNextToken();

        if (token.type == eTokenType::END)
        {
            break;
        }

        auto statement = ParseStatement();
        if (statement)
        {
            root->AddChild(statement.release());
        }
    }

    return std::make_unique<FSyntaxTree>(std::move(root));
}

ASyntaxNodePtr FParser::ParseStatement()
{
    SToken token = m_tokenizer.PeekNextToken();
    if (token.type == eTokenType::KEYWORD)
    {
        if (token.lexeme == "var")
        {
            return ParseVarDeclarationStatement();
        }
        else if (token.lexeme == "print")
        {
            return ParsePrintStatement();
        }
    }
    else if (token.type == eTokenType::IDENTIFIER)
    {
        return ParseAssignmentStatement();
    }

    throw std::runtime_error("Unexpected token: " + token.lexeme);
}

ASyntaxNodePtr FParser::ParseExpression()
{
    ASyntaxNodePtr left = ParseTerm();

    if (left->GetType() == eSyntaxNodeType::Number)
    {
        return ParseArithmeticOperatorExpression(std::move(left));
    }
    else if (left->GetType() == eSyntaxNodeType::String)
    {
        return ParseStringOperatorExpression(std::move(left));
    }
    else if (left->GetType() == eSyntaxNodeType::Identifier)
    {
        // return ParseIdentifierOperatorExpression(std::move(left));
    }

    return left;
}

ASyntaxNodePtr FParser::ParseAssignmentStatement()
{
    SToken idToken = m_tokenizer.GetNextToken();
    if (idToken.type != eTokenType::IDENTIFIER)
    {
        throw std::runtime_error("Expected identifier in assignment statement");
    }

    std::string identifier = idToken.lexeme;

    SToken equalToken = m_tokenizer.GetNextToken();
    if (equalToken.lexeme != "=")
    {
        throw std::runtime_error("Expected '=' in assignment statement");
    }

    auto value = ParseExpression();
    return std::make_unique<FAssignmentNode>(identifier, value.release());
}

ASyntaxNodePtr FParser::ParseVarDeclarationStatement()
{
    SToken varToken = m_tokenizer.GetNextToken();
    if (varToken.type != eTokenType::KEYWORD)
    {
        throw std::runtime_error("Expected 'var'");
    }

    SToken idToken = m_tokenizer.GetNextToken();
    if (idToken.type != eTokenType::IDENTIFIER)
    {
        throw std::runtime_error("Expected identifier after 'var'");
    }

    std::string identifier = idToken.lexeme;

    SToken equalToken = m_tokenizer.GetNextToken();
    if (equalToken.lexeme != "=")
    {
        throw std::runtime_error("Expected '=' after identifier in var declaration");
    }

    auto value = ParseExpression();
    return std::make_unique<FVarDeclarationNode>(identifier, value.release());
}

ASyntaxNodePtr FParser::ParsePrintStatement()
{
    SToken idToken = m_tokenizer.GetNextToken();
    if (idToken.type != eTokenType::KEYWORD)
    {
        throw std::runtime_error("Expected 'print'");
    }

    auto expression = ParseExpression();
    return std::make_unique<FPrintStatementNode>(expression.release());
}

ASyntaxNodePtr FParser::ParseArithmeticOperatorExpression(ASyntaxNodePtr left)
{
    while (m_tokenizer.HasNextToken())
    {
        const SToken& token = m_tokenizer.PeekNextToken();

        if (token.type == eTokenType::OPERATOR && (token.lexeme == "+" || token.lexeme == "-"))
        {
            m_tokenizer.GetNextToken();

            ASyntaxNodePtr right = ParseTerm();

            if (token.lexeme == "+")
            {
                left = std::make_unique<FArithmeticOperatorNode>("+", left.release(), right.release());
            }
            else if (token.lexeme == "-")
            {
                left = std::make_unique<FArithmeticOperatorNode>("-", left.release(), right.release());
            }
        }
        else
        {
            break;
        }
    }

    return left;
}

ASyntaxNodePtr FParser::ParseStringOperatorExpression(ASyntaxNodePtr left)
{
    while (m_tokenizer.HasNextToken())
    {
        const SToken& token = m_tokenizer.PeekNextToken();

        if (token.type == eTokenType::OPERATOR && (token.lexeme == "+" || token.lexeme == "-"))
        {
            m_tokenizer.GetNextToken();

            ASyntaxNodePtr right = ParseTerm();

            if (token.lexeme == "+")
            {
                left = std::make_unique<FStringOperatorNode>("+", left.release(), right.release());
            }
        }
        else
        {
            break;
        }
    }

    return left;
}

ASyntaxNodePtr FParser::ParseComparisonOperatorExpression(ASyntaxNodePtr left)
{
    SToken opToken = m_tokenizer.GetNextToken();
    if (opToken.type != eTokenType::COMPARISON)
    {
        throw std::runtime_error("Expected comparison operator");
    }

    auto right = ParseTerm();

    return std::make_unique<ABinaryOperatorNode>(opToken.lexeme, left.release(), right.release());
}

ASyntaxNodePtr FParser::ParseIdentifier()
{
    SToken token = m_tokenizer.GetNextToken();
    if (token.type != eTokenType::IDENTIFIER)
    {
        throw std::runtime_error("Expected 'identifier'");
    }

    return std::make_unique<FIdentifierNode>(token.lexeme);
}

ASyntaxNodePtr FParser::ParseNumber()
{
    SToken token = m_tokenizer.GetNextToken();
    if (token.type != eTokenType::NUMBER)
    {
        throw std::runtime_error("Expected 'number'");
    }

    int value = std::stoi(token.lexeme);
    return std::make_unique<FNumberNode>(value);
}

ASyntaxNodePtr FParser::ParseString()
{
    SToken token = m_tokenizer.GetNextToken();
    if (token.type != eTokenType::STRING)
    {
        throw std::runtime_error("Expected 'string'");
    }

    return std::make_unique<FStringNode>(token.lexeme);
}

ASyntaxNodePtr FParser::ParseTerm()
{
    ASyntaxNodePtr left = ParseFactor();

    while (m_tokenizer.HasNextToken() && left->GetType() == eSyntaxNodeType::Number)
    {
        const SToken& token = m_tokenizer.PeekNextToken();

        if (token.type == eTokenType::OPERATOR && (token.lexeme == "*" || token.lexeme == "/" || token.lexeme == "%"))
        {
            m_tokenizer.GetNextToken();

            ASyntaxNodePtr right = ParseFactor();

            if (token.lexeme == "*")
            {
                left = std::make_unique<FArithmeticOperatorNode>("*", left.release(), right.release());
            }
            else if (token.lexeme == "/")
            {
                left = std::make_unique<FArithmeticOperatorNode>("/", left.release(), right.release());
            }
            else if (token.lexeme == "%")
            {
                left = std::make_unique<FArithmeticOperatorNode>("%", left.release(), right.release());
            }
        }
        else
        {
            break;
        }
    }

    return left;
}

ASyntaxNodePtr FParser::ParseFactor()
{
    const SToken& token = m_tokenizer.PeekNextToken();

    if (token.type == eTokenType::NUMBER)
    {
        return ParseNumber();
    }
    else if (token.type == eTokenType::STRING)
    {
        return ParseString();
    }
    else if (token.type == eTokenType::IDENTIFIER)
    {
        return ParseIdentifier();
    }

    throw std::runtime_error("Unexpected token in factor: " + token.lexeme);
}
