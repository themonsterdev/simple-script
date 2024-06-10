#include "statement/oop/class/class_method_declaration_statement.hpp"

#include "context.hpp"

FClassMethodDeclarationStatement::FClassMethodDeclarationStatement(
    Visibility visibility,
    ClassMethodDefinitionPtr methodDefinition,
    StatementPtr body)
    : m_visibility(visibility)
    , m_methodDefinition(methodDefinition)
    , m_body(std::move(body))
{}

void FClassMethodDeclarationStatement::Execute(const FContext& context) const
{
    context.DeclareClassMethod(m_visibility, m_methodDefinition);

    if (m_body)
    {
        m_body->Execute(context);
    }
}

const Visibility& FClassMethodDeclarationStatement::GetVisibility() const
{
    return m_visibility;
}

const StatementPtr& FClassMethodDeclarationStatement::GetBody() const
{
    return m_body;
}
