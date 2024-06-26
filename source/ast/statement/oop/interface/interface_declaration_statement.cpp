/**
 * @file interface_declaration_statement.cpp
 * @brief Implementation of the interface statement class.
 */

#include "ast/statement/oop/interface/interface_declaration_statement.hpp"
#include "context/context.hpp"

FInterfaceDeclarationStatement::FInterfaceDeclarationStatement(
    const std::string& interfaceName,
    StatementList interfaceMethods)
    : m_interfaceName(interfaceName)
    , m_interfaceMethods(std::move(interfaceMethods))
{}

void FInterfaceDeclarationStatement::Execute(const FContext& context) const
{
    
}

std::string FInterfaceDeclarationStatement::GetInterfaceName() const
{
    return m_interfaceName;
}

const StatementList& FInterfaceDeclarationStatement::GetInterfaceMethods() const
{
    return m_interfaceMethods;
}
