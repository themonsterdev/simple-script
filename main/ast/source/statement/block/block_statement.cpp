/**
 * @file block_statement.cpp
 * @brief Implementation of the block statement class.
 */

// Include the declaration of the block statement class
#include "statement/block/block_statement.hpp"

// For runtime_error
#include <stdexcept>

FBlockStatement::FBlockStatement(StatementList statements)
    // Initialize m_statements with the given list of statements
    : m_statements(std::move(statements))
{}

const StatementList& FBlockStatement::GetStatements() const
{
    // Return a constant reference to the list of statements in this block
    return m_statements;
}

void FBlockStatement::Execute(const FContext& context) const
{
    // Execute each statement in the block sequentially
    for (const auto& statement : m_statements)
    {
        statement->Execute(context);
    }
}
