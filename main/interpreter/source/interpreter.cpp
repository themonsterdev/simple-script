#include "interpreter.hpp"

// Statement
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/binary_operator_node.hpp"
#include "ast/statement/print_statement_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"

#include <iostream>

void FInterpreter::Interpret(const FSyntaxTree* syntaxTree)
{
    const auto root = syntaxTree->GetRoot();
    if (root)
    {
        for (const auto child : root->GetChildren())
        {
            EvaluateNode(child);
        }
    }
    else
    {
        std::cerr << "Error: AST root is null." << std::endl;
    }
}

void FInterpreter::EvaluateNode(const ASyntaxNode* node)
{
    switch (node->GetType())
    {
    case eSyntaxNodeType::VariableDeclaration:
    {
        const auto varDeclNode = dynamic_cast<const VarDeclarationNode*>(node);
        if (varDeclNode)
        {
            const auto identifier = varDeclNode->GetIdentifier();
            const auto expression = varDeclNode->GetExpression();

            if (expression)
            {
                int value = EvaluateExpression(expression);
                m_variables[identifier] = value;
            }
            else
            {
                std::cerr << "Error: Variable declaration missing expression." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Unable to cast node to VarDeclarationNode." << std::endl;
        }
        break;
    }
    case eSyntaxNodeType::PrintStatement:
    {
        const auto printStmtNode = dynamic_cast<const PrintStatementNode*>(node);
        if (printStmtNode)
        {
            const auto expression = printStmtNode->GetExpression();
            if (expression)
            {
                int value = EvaluateExpression(expression);
                std::cout << value << std::endl;
            }
            else
            {
                std::cerr << "Error: Print statement missing expression." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Unable to cast node to PrintStatementNode." << std::endl;
        }
        break;
    }
    case eSyntaxNodeType::AssignmentStatement:
    {
        const auto assignmentNode = dynamic_cast<const AssignmentNode*>(node);
        if (assignmentNode)
        {
            const auto identifier = assignmentNode->GetIdentifier();
            const auto expression = assignmentNode->GetExpression();

            if (expression)
            {
                int value = EvaluateExpression(expression);
                m_variables[identifier] = value;
            }
            else
            {
                std::cerr << "Error: Assignment statement missing expression." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Unable to cast node to AssignmentNode." << std::endl;
        }
        break;
    }
    default:
        std::cerr << "Error: Unknown node type." << std::endl;
        break;
    }

    for (const auto child : node->GetChildren())
    {
        EvaluateNode(child);
    }
}

int FInterpreter::EvaluateExpression(const ASyntaxNode* expression)
{
    switch (expression->GetType())
    {
    case eSyntaxNodeType::ArithmeticExpression:
    {
        const auto node = dynamic_cast<const BinaryOperatorNode*>(expression);
        if (node)
        {
            int leftValue = EvaluateExpression(node->GetLeft());
            int rightValue = EvaluateExpression(node->GetRight());

            if (node->GetOp() == "+")
            {
                return leftValue + rightValue;
            }
            else if (node->GetOp() == "-")
            {
                return leftValue - rightValue;
            }
            else if (node->GetOp() == "/")
            {
                return leftValue / rightValue;
            }
            else if (node->GetOp() == "%")
            {
                return leftValue % rightValue;
            }
            else if (node->GetOp() == "*")
            {
                return leftValue * rightValue;
            }
        }
        break;
    }
    case eSyntaxNodeType::ComparisonExpression:
    {
        // Ajoutez la logique pour les expressions de comparaison si nécessaire
        std::cout << "ComparisonExpression" << std::endl;
        break;
    }
    case eSyntaxNodeType::Identifier:
    {
        const auto identifierNode = dynamic_cast<const IdentifierNode*>(expression);
        if (identifierNode)
        {
            std::string identifier = identifierNode->GetName();
            const auto it = m_variables.find(identifier);
            if (it != m_variables.end())
            {
                return it->second;
            }
            else
            {
                std::cerr << "Error: Undefined variable '" << identifier << "'." << std::endl;
                return 0;
            }
        }
        else
        {
            std::cerr << "Error: Unable to cast expression to IdentifierNode." << std::endl;
            return 0;
        }
    }
    case eSyntaxNodeType::Number:
    {
        const auto numberNode = dynamic_cast<const NumberNode*>(expression);
        if (numberNode)
        {
            return numberNode->GetValue();
        }
        else
        {
            std::cerr << "Error: Unable to cast expression to NumberNode." << std::endl;
            return 0;
        }
    }
    default:
        std::cerr << "Error: Unknown expression type." << std::endl;
        break;
    }

    return 0;
}
