/**
 * @file case_statement.hpp
 * @brief Declaration of the case statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a case statement in a switch statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * specifies a case condition and the associated block of statements to execute.
 */
class FCaseStatement final : public IStatement
{
    // The expression representing the case condition
    ExpressionPtr m_condition;

    // The body of statements associated with this case
    StatementPtr m_body;

public:

    /**
     * @brief Constructs a case statement with the given condition and body.
     * @param condition The expression representing the case condition.
     * @param body The body of statements associated with this case.
     */
    FCaseStatement(ExpressionPtr condition, StatementPtr body);

    /**
     * @brief Executes this case statement within the given context.
     *
     * This method is currently empty because the implementation of case execution
     * will depend on the specifics of your language and interpreter.
     * You should fill in this method with the logic to execute the case body within the context.
     * @param context The context in which to execute the case statement.
     */
    void Execute(const FContext& context) const override;

    /**
     * @brief Gets the condition expression of this case statement.
     * @return The condition expression of this case statement.
     */
    const ExpressionPtr& GetCondition() const;

    /**
     * @brief Gets the body of statements associated with this case statement.
     * @return The body of statements associated with this case statement.
     */
    const StatementPtr& GetBody() const;
};

// Define a smart pointer type for FCaseStatement
using CaseStatementPtr = std::unique_ptr<FCaseStatement>;

using CaseStatementVector = std::vector<CaseStatementPtr>;
