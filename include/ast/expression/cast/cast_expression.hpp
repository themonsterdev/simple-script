/**
 * @file cast_expression.hpp
 * @brief Declaration of the cast expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"
#include "type/type.hpp"

class FCastExpression final : public IExpression
{
    TypePtr m_targetType;
    ExpressionPtr m_expression;

public:

    FCastExpression(TypePtr targetType, ExpressionPtr expression);
    ValuePtr Evaluate(const FContext& context) const override;
};
