/**
 * @file unary_not_expression.cpp
 * @brief Implementation of the unary not expression class.
 */

// Include the header file for the FUnaryNotExpression class
#include "expression/operator/unary/unary_not_expression.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

#include "boolean_value.hpp"

FUnaryNotExpression::FUnaryNotExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FUnaryNotExpression::Evaluate(const FContext& context) const
{
    // Evaluate the inner expression
    ValuePtr innerValue = m_expression->Evaluate(context);

    // Check if the value is a boolean
    if (!innerValue->IsBoolean()) {
        throw std::runtime_error("Operand of unary negate must be boolean");
    }

    // Negate the boolean value
    const auto& value = std::dynamic_pointer_cast<FBooleanValue>(innerValue);

    return std::make_shared<FBooleanValue>(!value->GetValue());
}
