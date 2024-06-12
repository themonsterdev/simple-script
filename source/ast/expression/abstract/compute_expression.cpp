/**
 * @file compute_expression.cpp
 * @brief Implementation of the AComputeExpression class.
 */

// Include base class header
#include "ast/expression/abstract/compute_expression.hpp"

AComputeExpression::AComputeExpression(ExpressionPtr left, ExpressionPtr right)
	// Assign the left operand to the member variable m_left
	: m_left(std::move(left))
	// Assign the right operand to the member variable m_right
	, m_right(std::move(right))
{}

const ExpressionPtr& AComputeExpression::GetLeft() const
{
	// Return a reference to the left operand
	return m_left;
}

const ExpressionPtr& AComputeExpression::GetRight() const
{
	// Return a reference to the right operand
	return m_right;
}
