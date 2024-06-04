/**
 * @file addition_expression.cpp
 * @brief Implementation of the FAdditionExpression class.
 */

 // Include header file for the FAdditionExpression class
#include "expression/operator/additive/addition_expression.hpp"

// Include necessary standard library headers
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

FAdditionExpression::FAdditionExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FAdditionExpression::Evaluate(const FContext& context) const
{
    // Check if left and right operands exist
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Addition operator must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract integer values from the variants
    int leftInt, rightInt;

    // Check if both operands are integers
    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        leftInt  = std::get<int>(leftValue);
        rightInt = std::get<int>(rightValue);
    }
    else if (std::holds_alternative<std::string>(leftValue) && std::holds_alternative<std::string>(rightValue))
    {
        // Extract integer values from the variants
        return std::get<std::string>(leftValue) + std::get<std::string>(rightValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for addition operation");
    }

    // Return the sum of the left and right integer values
    return leftInt + rightInt;
}
