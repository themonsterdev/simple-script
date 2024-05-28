/**
 * @file string_operator_expression.cpp
 * @brief Implementation of the string operator expression class.
 */

// Include the declaration of the string operator expression class
#include "expression/string_operator_expression.hpp"

// For runtime_error
#include <stdexcept>

FStringOperatorExpression::FStringOperatorExpression(const std::string& op, ExpressionPtr left, ExpressionPtr right)
    // Initialize the string operator and its operands
    : m_operator(op)
    , m_left(left.release())
    , m_right(right.release())
{
    // Check if both left and right child expressions exist
    if (!m_left || !m_right)
    {
        throw std::runtime_error("String operator expression must have exactly two child expressions");
    }
}

Value FStringOperatorExpression::Evaluate(const FContext& context) const
{
    // Evaluate the operands expressions
    Value leftValue = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract string values from the variants
    std::string leftString;
    std::string rightString;

    // Check if the right operand is a string
    if (std::holds_alternative<std::string>(rightValue))
    {
        rightString = std::get<std::string>(rightValue);
    }
    else // Throw an exception if the right operand is not a string
    {
        throw std::runtime_error("Invalid operand type for string operation");
    }

    // Perform the binary operation based on the operator
    if (m_operator == "+")
    {
        // Concatenate the strings
        if (std::holds_alternative<std::string>(leftValue))
        {
            leftString = std::get<std::string>(leftValue);
            return leftString + rightString;
        }
        else // Throw an exception if the left operand is not a string
        {
            throw std::runtime_error("Invalid operand types for string concatenation");
        }
    }
    else if (m_operator == "*")
    {
        // Perform string repetition
        if (std::holds_alternative<int>(leftValue))
        {
            int repeatCount = std::get<int>(leftValue);
            std::string repeatedString;

            // Repeat the right string 'repeatCount' times
            for (int i = 0; i < repeatCount; ++i)
            {
                repeatedString += rightString;
            }
            return repeatedString;
        }
        else // Throw an exception if the left operand is not an integer
        {
            throw std::runtime_error("Invalid operand types for string repetition");
        }
    }
    // Add other string operations here

    // Throw an exception if the operator is not supported
    throw std::runtime_error("Unsupported string operator: " + m_operator);
}

std::string FStringOperatorExpression::GetOperator() const
{
    // Return the string operator
    return m_operator;
}

const ExpressionPtr& FStringOperatorExpression::GetLeft() const
{
    // Returns a constant reference to the left operand.
    return m_left;
}

const ExpressionPtr& FStringOperatorExpression::GetRight() const
{
    // Returns a constant reference to the right operand.
    return m_right;
}
