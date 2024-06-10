#include "statement/oop/property_declaration_statement.hpp"
#include "context.hpp"
#include <stdexcept>

FPropertyDeclarationStatement::FPropertyDeclarationStatement(
    Visibility visibility,
    ClassPropertyDefinitionPtr propertyDefinition,
    ExpressionPtr expression)
    : m_visibility(visibility)
    , m_propertyDefinition(propertyDefinition)
    , m_expression(std::move(expression))
{}

void FPropertyDeclarationStatement::Execute(const FContext& context) const
{
    const auto& value = m_expression->Evaluate(context);
    if (!value)
    {
        throw std::runtime_error("Failed to get value for the property statement");
    }

    const auto& type  = m_propertyDefinition->GetType();
    if (!type)
    {
        throw std::runtime_error("Failed to get type for the property statement");
    }

    type->SetDefaultValue(value);

    context.DeclareClassProperty(m_visibility, m_propertyDefinition);
}

Visibility FPropertyDeclarationStatement::GetVisibility() const
{
    return m_visibility;
}

ClassPropertyDefinitionPtr FPropertyDeclarationStatement::GetPropertyDefinition() const
{
    return m_propertyDefinition;
}

const ExpressionPtr& FPropertyDeclarationStatement::GetExpression() const
{
    return m_expression;
}
