#include "parser.hpp"
#include "tokenizer.hpp"

// Statement
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/binary_operator_node.hpp"
#include "ast/statement/print_statement_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"

#include <stdexcept>

FParser::FParser(FTokenizer& tokenizer)
	: m_tokenizer(tokenizer)
{}

std::unique_ptr<FSyntaxTree> FParser::Parse()
{
    std::unique_ptr<ASyntaxNode> root = std::make_unique<ASyntaxNode>();

    while (m_tokenizer.HasNextToken())
    {
        auto statement = ParseStatement();
        if (statement)
        {
            root->AddChild(statement.release());
        }
    }

    return std::make_unique<FSyntaxTree>(std::move(root));
}

std::unique_ptr<ASyntaxNode> FParser::ParseStatement()
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

std::unique_ptr<ASyntaxNode> FParser::ParseExpression()
{
    std::unique_ptr<ASyntaxNode> left = ParseTerm();

    while (m_tokenizer.HasNextToken())
    {
        const SToken& token = m_tokenizer.PeekNextToken();

        if (token.type == eTokenType::OPERATOR && (token.lexeme == "+" || token.lexeme == "-"))
        {
            m_tokenizer.GetNextToken();

            std::unique_ptr<ASyntaxNode> right = ParseTerm();

            if (token.lexeme == "+")
            {
                left = std::make_unique<BinaryOperatorNode>("+", left.release(), right.release());
            }
            else if (token.lexeme == "-")
            {
                left = std::make_unique<BinaryOperatorNode>("-", left.release(), right.release());
            }
        }
        else
        {
            break;
        }
    }

    return left;
}

std::unique_ptr<ASyntaxNode> FParser::ParseAssignmentStatement()
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
    return std::make_unique<AssignmentNode>(identifier, value.release());
}

std::unique_ptr<ASyntaxNode> FParser::ParseVarDeclarationStatement()
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
    return std::make_unique<VarDeclarationNode>(identifier, value.release());
}

std::unique_ptr<ASyntaxNode> FParser::ParsePrintStatement()
{
    SToken idToken = m_tokenizer.GetNextToken();
    if (idToken.type != eTokenType::KEYWORD)
    {
        throw std::runtime_error("Expected 'print'");
    }

    auto expression = ParseExpression();
    return std::make_unique<PrintStatementNode>(expression.release());
}

std::unique_ptr<ASyntaxNode> FParser::ParseArithmeticOperatorExpression(ASyntaxNode* left)
{
    SToken opToken = m_tokenizer.GetNextToken();
    if (opToken.type != eTokenType::OPERATOR)
    {
        throw std::runtime_error("Expected arithmetic operator");
    }

    auto right = ParseTerm();

    return std::make_unique<BinaryOperatorNode>(opToken.lexeme, left, right.release());
}

std::unique_ptr<ASyntaxNode> FParser::ParseComparisonOperatorExpression(ASyntaxNode* left)
{
    SToken opToken = m_tokenizer.GetNextToken();
    if (opToken.type != eTokenType::COMPARISON)
    {
        throw std::runtime_error("Expected comparison operator");
    }

    auto right = ParseTerm();

    return std::make_unique<BinaryOperatorNode>(opToken.lexeme, left, right.release());
}

std::unique_ptr<ASyntaxNode> FParser::ParseIdentifier()
{
    SToken token = m_tokenizer.GetNextToken();
    if (token.type != eTokenType::IDENTIFIER)
    {
        throw std::runtime_error("Expected 'identifier'");
    }

    return std::make_unique<IdentifierNode>(token.lexeme);
}

std::unique_ptr<ASyntaxNode> FParser::ParseNumber()
{
    SToken token = m_tokenizer.GetNextToken();
    if (token.type != eTokenType::NUMBER)
    {
        throw std::runtime_error("Expected 'number'");
    }

    int value = std::stoi(token.lexeme);
    return std::make_unique<NumberNode>(value);
}

std::unique_ptr<ASyntaxNode> FParser::ParseTerm()
{
    std::unique_ptr<ASyntaxNode> left = ParseFactor();

    while (m_tokenizer.HasNextToken())
    {
        const SToken& token = m_tokenizer.PeekNextToken();

        if (token.type == eTokenType::OPERATOR && (token.lexeme == "*" || token.lexeme == "/" || token.lexeme == "%"))
        {
            m_tokenizer.GetNextToken();

            std::unique_ptr<ASyntaxNode> right = ParseFactor();

            if (token.lexeme == "*")
            {
                left = std::make_unique<BinaryOperatorNode>("*", left.release(), right.release());
            }
            else if (token.lexeme == "/")
            {
                left = std::make_unique<BinaryOperatorNode>("/", left.release(), right.release());
            }
            else if (token.lexeme == "%")
            {
                left = std::make_unique<BinaryOperatorNode>("%", left.release(), right.release());
            }
        }
        else
        {
            break;
        }
    }

    return left;
}

std::unique_ptr<ASyntaxNode> FParser::ParseFactor()
{
    const SToken& token = m_tokenizer.PeekNextToken();

    if (token.type == eTokenType::NUMBER)
    {
        return ParseNumber();
    }
    else if (token.type == eTokenType::IDENTIFIER)
    {
        return ParseIdentifier();
    }

    throw std::runtime_error("Unexpected token in factor: " + token.lexeme);
}
