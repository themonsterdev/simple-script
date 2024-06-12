/**
 * @file addition_expression.cpp
 * @brief Implementation of the FAdditionExpression class.
 */

 // Include header file for the FAdditionExpression class
#include "ast/expression/operator/additive/addition_expression.hpp"

// Include necessary standard library headers
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"
#include "value/string_value.hpp"

FAdditionExpression::FAdditionExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FAdditionExpression::Evaluate(const FContext& context) const
{
    // Check if left and right operands exist
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Addition operator must have exactly two operands");
    }

    // Evaluate the left and right operands
    ValuePtr leftValue  = m_left->Evaluate(context);
    ValuePtr rightValue = m_right->Evaluate(context);

    // Check if both operands are integers
    if (leftValue->IsNumber() && rightValue->IsNumber())
    {
        const auto& leftInt = std::dynamic_pointer_cast<FNumberValue>(leftValue);
        const auto& rightInt = std::dynamic_pointer_cast<FNumberValue>(rightValue);
        const int value = leftInt->GetValue() + rightInt->GetValue();
        return std::make_shared<FNumberValue>(value);
    }
    else if (leftValue->IsString() && rightValue->IsString())
    {
        const auto& leftString = std::dynamic_pointer_cast<FStringValue>(leftValue);
        const auto& rightString = std::dynamic_pointer_cast<FStringValue>(rightValue);
        const std::string value = leftString->GetValue() + rightString->GetValue();
        return std::make_shared<FStringValue>(value);
    }

    // Throw exception for invalid operand types
    throw std::runtime_error("Invalid operand types for addition operation");
}
