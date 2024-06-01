/**
 * @file conditional_statement.hpp
 * @brief Declaration of the conditional statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a conditional statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * evaluates a condition and executes different statements based on the result.
 */
class FConditionalStatement final : public IStatement
{
    ExpressionPtr m_condition;             // The condition to be evaluated
    StatementPtr m_ifStatement;            // Statement to execute if condition is true
    StatementList m_elseIfStatements;     // List of else-if statements
    StatementPtr m_elseStatement;         // Statement to execute if no condition is true

public:

    /**
     * @brief Constructs an FConditionalStatement with the given condition and if statement.
     * @param condition The condition to be evaluated.
     * @param ifStatement The statement to execute if the condition is true.
     */
    FConditionalStatement(ExpressionPtr condition, StatementPtr ifStatement);

    /**
     * @brief Executes this conditional statement within the given context.
     * @param context The context in which to execute the node.
     */
    virtual void Execute(const FContext& context) const override;

    /**
     * @brief Evaluates the condition associated with this conditional statement.
     * @param context The context in which to evaluate the condition.
     * @return true if the condition evaluates to true, false otherwise.
     */
    bool EvaluateCondition(const FContext& context) const;

    /**
     * @brief Adds an else-if statement to this conditional statement.
     * @param elseIfStatement The else-if statement to add.
     */
    void AddElseIfStatement(StatementPtr elseIfStatement);

    /**
     * @brief Sets the else statement for this conditional statement.
     * @param elseStatement The else statement to set.
     */
    void SetElseStatement(StatementPtr elseStatement);

    /**
     * @brief Gets the condition associated with this conditional statement.
     * @return A constant reference to the condition expression.
     */
    const ExpressionPtr& GetCondition() const;

    /**
     * @brief Gets the if statement associated with this conditional statement.
     * @return A constant reference to the if statement.
     */
    const StatementPtr& GetIfStatement() const;

    /**
     * @brief Gets the list of else-if statements associated with this conditional statement.
     * @return A constant reference to the list of else-if statements.
     */
    const StatementList& GetElseIfStatements() const;

    /**
     * @brief Gets the else statement associated with this conditional statement.
     * @return A constant reference to the else statement.
     */
    const StatementPtr& GetElseStatement() const;
};
