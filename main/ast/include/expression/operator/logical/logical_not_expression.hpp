/**
 * @file logical_not_expression.hpp
 * @brief Declaration of the FLogicalNotExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/interface/expression.hpp"

/**
 * @brief Class for logical NOT expressions.
 * This class represents logical NOT expressions.
 */
class FLogicalNotExpression final : public IExpression
{
    // The expression to be negated.
    ExpressionPtr m_expression;

public:

    /**
     * @brief Constructs an FLogicalNotExpression object with the given expression.
     * @param expression The expression to be negated.
     */
    FLogicalNotExpression(ExpressionPtr expression);

    /**
     * @brief Evaluates the logical NOT expression.
     * @param context The evaluation context.
     * @return The value of the logical NOT expression.
     */
    virtual Value Evaluate(const FContext& context) const override;

    /**
     * @brief Gets the expression to be negated.
     * @return The expression to be negated.
     */
    const ExpressionPtr& GetExpression() const;
};
