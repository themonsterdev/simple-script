/**
 * @file class_declaration_statement.cpp
 * @brief Implementation of the class declaration statement class.
 */

// Include the header file for the class declaration statement class
#include "statement/oop/class/class_declaration_statement.hpp"
#include "statement/block/block_statement.hpp"

// Include declarations for context objects
#include "context.hpp"

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
    context.DeclareClass(Visibility::Public, m_classDefinition);

    const auto& classBody = dynamic_cast<FBlockStatement*>(m_classBody.get());

    if (classBody)
    {
        // Execute each statement in the block sequentially
        for (const auto& statement : classBody->GetStatements())
        {
            statement->Execute(context);
        }
    }
}

ClassDefinitionPtr FClassDeclarationStatement::GetClassDefinition() const
{
    return m_classDefinition;
}

const StatementPtr& FClassDeclarationStatement::GetClassBody() const
{
    return m_classBody;
}
