/**
 * @file bitwise_xor_expression.cpp
 * @brief Implementation of the FBitwiseXorExpression class.
 */

// Include header file for the FBitwiseXorExpression class
#include "expression/operator/bitwise/bitwise_xor_expression.hpp"
#include <stdexcept>

FBitwiseXorExpression::FBitwiseXorExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FBitwiseXorExpression::Evaluate(const FContext& context) const
{
    // Check if both left and right operands are not null
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Both operands must be provided for bitwise XOR expression");
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
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Both operands of bitwise XOR expression must be integers");
    }

    // Perform the bitwise XOR operation and return the result
    return leftInt ^ rightInt;
}