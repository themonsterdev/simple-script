/**
 * @file compute_expression.hpp
 * @brief Declaration of the AComputeExpression class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "expression/interface/expression.hpp"

/**
 * @brief Abstract class for arithmetic computation expressions.
 * This class represents arithmetic computation expressions such as addition, subtraction, etc.
 */
class AComputeExpression : public IExpression
{
protected:

	ExpressionPtr m_left;   // The left operand.
	ExpressionPtr m_right;  // The right operand.

public:

    /**
    * @brief Constructs an AComputeExpression object with given left and right operands.
    * @param left The left operand.
    * @param right The right operand.
    */
	AComputeExpression(ExpressionPtr left, ExpressionPtr right);

    /**
     * @brief Gets the left operand.
     * @return The left operand.
     */
    const ExpressionPtr& GetLeft() const;

    /**
     * @brief Gets the right operand.
     * @return The right operand.
     */
    const ExpressionPtr& GetRight() const;
};
