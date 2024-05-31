/**
 * @file block_statement.cpp
 * @brief Implementation of the block statement class.
 */

 // Include the declaration of the block statement class
#include "statement/block_statement.hpp"

// For runtime_error
#include <stdexcept>

FBlockStatement::FBlockStatement(StatementList statements)
    // Initialize m_identifier with the given identifier
    : m_statements(std::move(statements))
{}

const StatementList& FBlockStatement::GetStatements() const
{
    // Return a constant reference to the expression associated with this assignment
	return m_statements;
}

void FBlockStatement::Execute(const FContext& context) const
{
    for (const auto& statement : m_statements)
    {
        statement->Execute(context);
    }
}
