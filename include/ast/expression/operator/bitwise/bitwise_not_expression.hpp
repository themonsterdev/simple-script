/**
 * @file bitwise_not_expression.hpp
 * @brief Declaration of the FBitwiseNotExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Class for bitwise NOT expressions.
 * This class represents bitwise NOT expressions.
 */
class FBitwiseNotExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    FBitwiseNotExpression(ExpressionPtr expression);
    ValuePtr Evaluate(const FContext& context) const override;
};
