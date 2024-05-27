/**
 * @file arithmetic_operator_node.cpp
 * @brief Implementation of the arithmetic operator node class.
 */

// Include the declaration of the arithmetic operator node
#include "ast/expression/arithmetic_operator_node.hpp"

// For std::runtime_error
#include <stdexcept>

FArithmeticOperatorNode::FArithmeticOperatorNode(const std::string& op, ExpressionPtr left, ExpressionPtr right)
    // Initialize the operator
    : m_operator(op)
    , m_left(std::move(left))
    , m_right(std::move(right))
{}

Value FArithmeticOperatorNode::Evaluate(const FContext& context) const
{
    // Check if both left and right child nodes exist
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Arithmetic operator node must have exactly two children");
    }

    // Evaluate the child nodes
    Value leftValue = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract int values from the variants
    int leftInt, rightInt;

    // Check if both operands are integers
    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        leftInt = std::get<int>(leftValue);
        rightInt = std::get<int>(rightValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for arithmetic operation");
    }

    // Validate operands before performing operations
    if (m_operator == "/" && rightInt == 0)
    {
        throw std::runtime_error("Division by zero error");
    }
    else if (m_operator == "%" && rightInt == 0)
    {
        throw std::runtime_error("Modulo by zero error");
    }

    // Perform operations based on their precedence
    if (m_operator == "*")
    {
        // Perform multiplication
        return leftInt * rightInt;
    }
    else if (m_operator == "/")
    {
        // Perform division
        return leftInt / rightInt;
    }
    else if (m_operator == "%")
    {
        // Perform modulo operation
        return leftInt % rightInt;
    }
    else if (m_operator == "+")
    {
        // Perform addition
        return leftInt + rightInt;
    }
    else if (m_operator == "-")
    {
        // Perform subtraction
        return leftInt - rightInt;
    }
    // @TODO Add other operations here

    // Throw an exception if the operator is not supported
    throw std::runtime_error("Unsupported arithmetic operator: " + m_operator);
}

std::string FArithmeticOperatorNode::GetOperator() const
{
    // Return the binary operator
    return m_operator;
}

const ExpressionPtr& FArithmeticOperatorNode::GetLeft() const
{
    // Returns a constant reference to the left expression.
    return m_left;
}

const ExpressionPtr& FArithmeticOperatorNode::GetRight() const
{
    // Returns a constant reference to the right expression.
    return m_right;
}
