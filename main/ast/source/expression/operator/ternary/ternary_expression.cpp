/**
 * @file ternary_expression.cpp
 * @brief Implementation of the FTernaryExpression class.
 */

// Include the header file for the ternary expression class
#include "expression/operator/ternary/ternary_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

FTernaryExpression::FTernaryExpression(ExpressionPtr condition, ExpressionPtr trueExpr, ExpressionPtr falseExpr)
    // Initialize condition member with the provided condition expression
    : m_condition(std::move(condition))
    // Initialize trueExpr member with the provided true expression
    , m_trueExpr(std::move(trueExpr))
    // Initialize falseExpr member with the provided false expression
    , m_falseExpr(std::move(falseExpr))
{}

Value FTernaryExpression::Evaluate(const FContext& context) const
{
    // Evaluate the condition
    Value conditionValue = m_condition->Evaluate(context);

    bool conditionResult = false;

    // Check if both operands are integer/boolean
    if (std::holds_alternative<int>(conditionValue))
    {
        // Extract boolean value from the variants
        conditionResult = std::get<int>(conditionValue) > 0;
    }
    else if (std::holds_alternative<bool>(conditionValue))
    {
        // Extract boolean value from the variants
        conditionResult = std::get<bool>(conditionValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid condition type for ternary");
    }

    // If the condition is true, evaluate and return the true expression
    if (conditionResult)
    {
        return m_trueExpr->Evaluate(context);
    }

    // Otherwise, evaluate and return the false expression
    return m_falseExpr->Evaluate(context);
}

const ExpressionPtr& FTernaryExpression::GetCondition() const
{
    // Return the condition expression
    return m_condition;
}

const ExpressionPtr& FTernaryExpression::GetTrue() const
{
    // Return the true expression
    return m_trueExpr;
}

const ExpressionPtr& FTernaryExpression::GetFalse() const
{
    // Return the false expression
    return m_falseExpr;
}
