/**
 * @file assert_statement.hpp
 * @brief Declaration of the assert statement class.
 */

 // Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents an assert statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * asserts the truthiness of an expression.
 */
class FAssertStatement final : public IStatement
{
    // The expression to be asserted.
    ExpressionPtr m_expression;

    // The optional message for the assertion failure.
    std::string m_message;

public:

    /**
     * @brief Constructs an FAssertStatement with the given expression and an optional message.
     * @param expression The expression to be asserted.
     * @param message The optional message to display if the assertion fails.
     */
    explicit FAssertStatement(ExpressionPtr expression, std::string message = "");

    /**
     * @brief Executes the assert statement within the given context.
     * @param context The context in which to execute the statement.
     */
    virtual void Execute(const FContext& context) const override;
};
