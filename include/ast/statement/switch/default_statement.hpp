/**
 * @file default_statement.hpp
 * @brief Declaration of the default statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a default statement in a switch statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * specifies the default case and the associated block of statements to execute.
 */
class FDefaultStatement final : public IStatement
{
    // The body of statements associated with this default case
    StatementPtr m_body;

public:

    /**
     * @brief Constructs a default statement with the given body.
     * @param body The body of statements associated with this default case.
     */
    FDefaultStatement(StatementPtr body);

    /**
     * @brief Executes this default statement within the given context.
     *
     * This method is currently empty because the implementation of default case execution
     * will depend on the specifics of your language and interpreter.
     * You should fill in this method with the logic to execute the default case body within the context.
     * @param context The context in which to execute the default statement.
     */
    void Execute(const FContext& context) const override;

    /**
     * @brief Gets the body of statements associated with this default statement.
     * @return The body of statements associated with this default statement.
     */
    const StatementPtr& GetBody() const;
};

// Define a smart pointer type for FDefaultStatement
using DefaultStatementPtr = std::unique_ptr<FDefaultStatement>;
