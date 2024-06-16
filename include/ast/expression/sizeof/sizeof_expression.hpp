/**
 * @file sizeof_expression.hpp
 * @brief Declaration of the sizeof expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FSizeofExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    FSizeofExpression(ExpressionPtr expression);
    ValuePtr Evaluate(const FContext& context) const override;
};
