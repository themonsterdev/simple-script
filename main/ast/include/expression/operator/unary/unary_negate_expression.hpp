/**
 * @file unary_negate_expression.hpp
 * @brief Declaration of the unary negate expression class.
 */

 // Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

class FUnaryNegateExpression final : public IExpression
{
	ExpressionPtr m_expression;

public:

	FUnaryNegateExpression(ExpressionPtr expression);

	virtual Value Evaluate(const FContext& context) const override;
};
