/**
 * @file boolean_expression.hpp
 * @brief Declaration of the boolean expression class.
 */

// Ensure this file is included only once
#pragma once

 // Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a boolean expression in the abstract syntax tree (AST).
 *
 * This class inherits from the IExpression interface and represents a expression
 * that holds an boolean value in the AST.
 */
class FBooleanExpression final : public IExpression
{
	// The boolean value held by the expression
	bool m_value;

public:

	/**
	 * @brief Constructs a boolean expression with the specified boolean value.
	 * @param value The boolean value to be held by the expression.
	 */
	FBooleanExpression(bool value);

	/**
	 * @brief Returns the boolean value held by the expression.
	 * @return The boolean value.
	 */
	bool GetValue() const;

	/**
	 * @brief Sets the boolean value held by the expression.
	 * @param value The new boolean value.
	 */
	void SetValue(bool value);

	/**
	 * @brief Evaluates the boolean expression.
	 * @param context The context in which the evaluation occurs (unused in this case).
	 * @return The boolean value held by the expression.
	 */
	virtual ValuePtr Evaluate(const FContext& context) const override;
};
