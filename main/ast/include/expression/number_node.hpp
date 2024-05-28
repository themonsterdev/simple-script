/**
 * @file number_node.hpp
 * @brief Declaration of the number node class.
 */

#pragma once

 // Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a number node in the abstract syntax tree (AST).
 *
 * This class inherits from the IExpression interface and represents a node
 * that holds an integer value in the AST.
 */
class FNumberNode final : public IExpression
{
	// The integer value held by the node
	int m_value;

public:

	/**
	 * @brief Constructs a number node with the specified integer value.
	 * @param value The integer value to be held by the node.
	 */
	FNumberNode(int value);

	/**
	 * @brief Returns the integer value held by the node.
	 * @return The integer value.
	 */
	int GetValue() const;

	/**
	 * @brief Sets the integer value held by the node.
	 * @param value The new integer value.
	 */
	void SetValue(int value);

	/**
	 * @brief Evaluates the number node.
	 * @param context The context in which the evaluation occurs (unused in this case).
	 * @return The integer value held by the node.
	 */
	virtual Value Evaluate(const FContext& context) const override;
};
