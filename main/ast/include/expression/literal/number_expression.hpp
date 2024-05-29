/**
 * @file number_expression.hpp
 * @brief Declaration of the number expression class.
 */

// Ensure this file is included only once
#pragma once

 // Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a number expression in the abstract syntax tree (AST).
 *
 * This class inherits from the IExpression interface and represents a expression
 * that holds an integer value in the AST.
 */
class FNumberExpression final : public IExpression
{
	// The integer value held by the expression
	int m_value;

public:

	/**
	 * @brief Constructs a number expression with the specified integer value.
	 * @param value The integer value to be held by the expression.
	 */
	FNumberExpression(int value);

	/**
	 * @brief Returns the integer value held by the expression.
	 * @return The integer value.
	 */
	int GetValue() const;

	/**
	 * @brief Sets the integer value held by the expression.
	 * @param value The new integer value.
	 */
	void SetValue(int value);

	/**
	 * @brief Evaluates the number expression.
	 * @param context The context in which the evaluation occurs (unused in this case).
	 * @return The integer value held by the expression.
	 */
	virtual Value Evaluate(const FContext& context) const override;
};
