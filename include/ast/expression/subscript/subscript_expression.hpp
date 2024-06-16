/**
 * @file subscript_expression.hpp
 * @brief Declaration of the subscript expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FSubscriptExpression final : public IExpression
{
    ExpressionPtr m_array;
    ExpressionPtr m_index;

public:

    FSubscriptExpression(ExpressionPtr array, ExpressionPtr index);
    ValuePtr Evaluate(const FContext& context) const override;
};
