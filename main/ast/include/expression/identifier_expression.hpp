/**
 * @file identifier_expression.hpp
 * @brief Declaration of the identifier expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents an identifier expression in the abstract syntax tree (AST).
 *
 * This class inherits from the IExpression interface and represents an expression
 * that holds an identifier (variable name) in the AST.
 */
class FIdentifierExpression final : public IExpression
{
public:

    /**
     * @brief Constructs an identifier expression with the specified name.
     * @param name The name of the identifier.
     */
    FIdentifierExpression(const std::string& name);

    /**
     * @brief Returns the name of the identifier.
     * @return The name of the identifier.
     */
    const std::string& GetName() const;

    /**
     * @brief Sets the name of the identifier.
     * @param name The new name of the identifier.
     */
    void SetName(const std::string& name);

    /**
     * @brief Evaluates the identifier expression within the given context.
     *
     * This method retrieves the value associated with the identifier from the context.
     *
     * @param context The context in which to evaluate the identifier.
     * @return The value associated with the identifier.
     */
    virtual Value Evaluate(const FContext& context) const override;

private:

    // The name of the identifier.
    std::string m_name;
};
