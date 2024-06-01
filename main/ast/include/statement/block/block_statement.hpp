/**
 * @file block_statement.hpp
 * @brief Declaration of the block statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a block statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * contains a block of statements to be executed sequentially.
 */
class FBlockStatement final : public IStatement
{
    // The list of statements contained within the block.
    StatementList m_statements;

public:

    /**
     * @brief Constructs an FBlockStatement with the given list of statements.
     * @param statements The list of statements contained within the block.
     */
    FBlockStatement(StatementList statements);

    /**
     * @brief Gets the list of statements in this block.
     * @return The list of statements in this block.
     */
    const StatementList& GetStatements() const;

    /**
     * @brief Executes the statements within this block within the given context.
     * @param context The context in which to execute the statements.
     */
    virtual void Execute(const FContext& context) const override;
};
