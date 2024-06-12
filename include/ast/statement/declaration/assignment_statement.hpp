/**
 * @file assignment_statement.hpp
 * @brief Declaration of the assignment statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents an assignment statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * assigns the result of an expression to an identifier.
 */
class FAssignmentStatement final : public IStatement
{
    // The identifier to which the expression value will be assigned.
    std::string m_identifier;

    // The expression to be evaluated and assigned to the identifier.
    ExpressionPtr m_expression;

public:

    /**
     * @brief Constructs an FAssignmentStatement with the given identifier and expression.
     * @param identifier The identifier for the assignment.
     * @param expression The expression to be evaluated and assigned.
     */
    FAssignmentStatement(const std::string& identifier, ExpressionPtr expression);

    /**
     * @brief Gets the identifier of this assignment node.
     * @return The identifier of this assignment node.
     */
    std::string GetIdentifier() const;

    /**
     * @brief Gets the expression of this assignment node.
     * @return The expression of this assignment node.
     */
    const ExpressionPtr& GetExpression() const;

    /**
     * @brief Executes this assignment node within the given context.
     *
     * This method evaluates the expression and assigns its value to the identifier in the context.
     * @param context The context in which to evaluate the node.
     */
    void Execute(const FContext& context) const override;
};
