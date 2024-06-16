/**
 * @file dereference_expression.hpp
 * @brief Declaration of the dereference expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FDereferenceExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    FDereferenceExpression(ExpressionPtr expression);
    ValuePtr Evaluate(const FContext& context) const override;
};
