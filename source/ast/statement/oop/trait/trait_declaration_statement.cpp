/**
 * @file trait_declaration_statement.cpp
 * @brief Implementation of the trait declaration statement class.
 */

// Include the header file for the trait declaration statement trait
#include "ast/statement/oop/trait/trait_declaration_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

// Constructor definition
FTraitDeclarationStatement::FTraitDeclarationStatement(
    const std::string& traitName,
    StatementPtr traitBody)
    : m_traitName(traitName)
    , m_traitBody(std::move(traitBody))
{}

// Execute method definition
void FTraitDeclarationStatement::Execute(const FContext& context) const
{

}

// GetTraitName method definition
const std::string& FTraitDeclarationStatement::GetTraitName() const
{
    // Return the name of the trait
    return m_traitName;
}

// GetTraitBody method definition
const StatementPtr& FTraitDeclarationStatement::GetTraitBody() const
{
    // Return the block containing trait attributes and methods
    return m_traitBody;
}
