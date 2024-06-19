/**
 * @file class_declaration_statement.cpp
 * @brief Implementation of the class declaration statement class.
 */

// Include the header file for the class declaration statement class
#include "ast/statement/oop/class/class_declaration_statement.hpp"
#include "ast/statement/block/block_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "value/class_value.hpp"

#include <stdexcept>

// Constructor definition
FClassDeclarationStatement::FClassDeclarationStatement(
    ClassDefinitionPtr classDefinition,
    StatementPtr classBody)
    : m_classDefinition(classDefinition)
    , m_classBody(std::move(classBody))
{}

// Execute method definition
void FClassDeclarationStatement::Execute(const FContext& context) const
{
    const auto& value = std::make_shared<FClassValue>(m_classDefinition);
    context.AddSymbol(value->GetName(), value);

    const auto& currentClass = context.GetCurrentClass();
    context.SetCurrentClass(value);

    if (m_classBody)
    {
        m_classBody->Execute(context);
    }

    context.SetCurrentClass(currentClass);
}

ClassDefinitionPtr FClassDeclarationStatement::GetClassDefinition() const
{
    return m_classDefinition;
}

const StatementPtr& FClassDeclarationStatement::GetClassBody() const
{
    return m_classBody;
}
