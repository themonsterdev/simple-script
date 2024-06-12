/**
 * @file string_expression.hpp
 * @brief Declaration of the string expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a string constant node in the abstract syntax tree.
 *
 * This class inherits from the IExpression interface and represents a node
 * that holds a string constant value in the AST.
 */
class FStringExpression final : public IExpression
{
	// The string value stored in this node
	std::string m_value;

public:

	/**
	 * @brief Constructs a string node with the specified string value.
	 * @param value The string value.
	 */
	FStringExpression(const std::string& value);

	/**
	 * @brief Gets the string value stored in this node.
	 * @return The string value.
	 */
	std::string GetValue() const;

	/**
	 * @brief Sets the string value stored in this node.
	 * @param value The new string value.
	 */
	void SetValue(const std::string& value);

	/**
	 * @brief Evaluates the string constant represented by this node.
	 * @param context The context in which the evaluation occurs.
	 * @return The string value.
	 */
	ValuePtr Evaluate(const FContext& context) const override;
};
