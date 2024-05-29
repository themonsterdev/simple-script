/**
 * @file var_declaration_list_statement.cpp
 * @brief Implementation of the variable declaration list class.
 */

// Include the declaration of the variable declaration list statement class
#include "statement/var_declaration_list_statement.hpp"

// For std::invalid_argument
#include <stdexcept>

FVarDeclarationListStatement::FVarDeclarationListStatement(StatementVector declarations)
    // Initialize member variable with provided declarations
    : m_declarations(std::move(declarations))
{}

void FVarDeclarationListStatement::Execute(const FContext& context) const
{
    // Iterate over each declaration in the list
    for (const auto& declarations : m_declarations)
    {
        // Execute each declaration
        declarations->Execute(context);
    }
}

const StatementVector& FVarDeclarationListStatement::GetDeclarations() const
{
    // Return the vector of declarations
    return m_declarations;
}
