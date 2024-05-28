/**
 * @file var_declaration_list_statement.cpp
 * @brief Implementation of the variable declaration list class.
 */

// Include the declaration of the variable declaration list statement class
#include "statement/var_declaration_list_statement.hpp"

// For std::invalid_argument
#include <stdexcept>

FVarDeclarationListStatement::FVarDeclarationListStatement(StatementVector declarations)
	: m_declarations(std::move(declarations))
{}

void FVarDeclarationListStatement::Execute(const FContext& context) const
{
    for (const auto& declarations : m_declarations)
    {
        declarations->Execute(context);
    }
}

const StatementVector& FVarDeclarationListStatement::GetDeclarations() const
{
    return m_declarations;
}
