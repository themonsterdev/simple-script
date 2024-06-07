/**
 * @file block_statement.cpp
 * @brief Implementation of the block statement class.
 */

// Include the declaration of the block statement class
#include "statement/block/block_statement.hpp"

// For runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

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
    context.EnterScope();
    context.ResetReturnValue();
    context.SetContinueFlag(false);
    context.SetThrowFlag(false);

    // Execute each statement in the block sequentially
    for (const auto& statement : m_statements)
    {
        statement->Execute(context);

        // Check if a 'return' value has been set
        if (context.HasReturnValue())
        {
            // Exit the loop if a 'return' statement was executed
            break;
        }

        // Check if a 'continue' statement has been encountered
        if (context.GetContinueFlag())
        {
            // Exit the loop if a 'continue' statement was executed
            break;
        }

        // Check if a 'throw' statement has been encountered
        if (context.GetThrowFlag())
        {
            // Exit the loop if a 'throw' statement was executed
            break;
        }
    }

    context.LeaveScope();
}
