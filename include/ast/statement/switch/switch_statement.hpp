/**
 * @file switch_statement.hpp
 * @brief Declaration of the switch statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

// Include the header files for case and default statements
#include "ast/statement/switch/case_statement.hpp"
#include "ast/statement/switch/default_statement.hpp"

/**
 * @brief Represents a switch statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * evaluates an expression and executes a block of statements based on the result.
 */
class FSwitchStatement : public IStatement
{
    // The expression to be evaluated for the switch condition
    ExpressionPtr m_condition;

    // The list of case statements associated with this switch statement
    CaseStatementVector m_cases;

    // The default case statement associated with this switch statement
    DefaultStatementPtr m_defaultCase;

public:

    /**
     * @brief Constructs a switch statement with the given condition, cases, and default case.
     * @param condition The expression to be evaluated for the switch condition.
     * @param cases The list of case statements associated with this switch statement.
     * @param defaultCase The default case statement associated with this switch statement.
     */
    FSwitchStatement(ExpressionPtr condition, CaseStatementVector cases, DefaultStatementPtr defaultCase);

    /**
     * @brief Executes this switch statement within the given context.
     *
     * This method is currently empty because the implementation of switch statement execution
     * will depend on the specifics of your language and interpreter.
     * You should fill in this method with the logic to evaluate the switch condition and execute the appropriate case or default case body within the context.
     * @param context The context in which to execute the switch statement.
     */
    void Execute(const FContext& context) const override;

    /**
     * @brief Gets the expression to be evaluated for the switch condition.
     * @return The expression to be evaluated for the switch condition.
     */
    const ExpressionPtr& GetCondition() const;

    /**
     * @brief Gets the list of case statements associated with this switch statement.
     * @return The list of case statements associated with this switch statement.
     */
    const CaseStatementVector& GetCases() const;

    /**
     * @brief Gets the default case statement associated with this switch statement.
     * @return The default case statement associated with this switch statement.
     */
    const DefaultStatementPtr& GetDefaultCase() const;
};
