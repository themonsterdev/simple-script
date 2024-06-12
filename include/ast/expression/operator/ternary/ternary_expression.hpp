/**
 * @file ternary_expression.hpp
 * @brief Declaration of the FTernaryExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a ternary expression.
 *
 * This class represents a ternary expression of the form "condition ? trueExpr : falseExpr".
 */
class FTernaryExpression final : public IExpression
{
public:

    /**
     * @brief Constructs a ternary expression with the given condition and expressions.
     * @param condition The condition expression.
     * @param trueExpr The expression to be evaluated if the condition is true.
     * @param falseExpr The expression to be evaluated if the condition is false.
     */
    FTernaryExpression(ExpressionPtr condition, ExpressionPtr trueExpr, ExpressionPtr falseExpr);

    /**
     * @brief Evaluates the ternary expression based on the provided context.
     * @param context The context used for evaluation.
     * @return The result of the ternary expression evaluation.
     */
    ValuePtr Evaluate(const FContext& context) const override;

    /**
     * @brief Gets the condition expression.
     * @return The condition expression.
     */
    const ExpressionPtr& GetCondition() const;

    /**
     * @brief Gets the true expression.
     * @return The true expression.
     */
    const ExpressionPtr& GetTrue() const;

    /**
     * @brief Gets the false expression.
     * @return The false expression.
     */
    const ExpressionPtr& GetFalse() const;

private:

    // The condition expression.
    ExpressionPtr m_condition;

    // The expression to be evaluated if the condition is true.
    ExpressionPtr m_trueExpr;

    // The expression to be evaluated if the condition is false.
    ExpressionPtr m_falseExpr;
};
