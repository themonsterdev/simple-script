#include "statement/oop/property_declaration_statement.hpp"
#include "context.hpp"

FPropertyDeclarationStatement::FPropertyDeclarationStatement(
    std::string visibility,
    std::string name,
    ExpressionPtr expression
)
    : m_visibility(visibility)
    , m_name(name)
    , m_expression(std::move(expression))
{}

const std::string& FPropertyDeclarationStatement::GetVisibility() const
{
    return m_visibility;
}

const std::string& FPropertyDeclarationStatement::GetName() const
{
    return m_name;
}

const ExpressionPtr& FPropertyDeclarationStatement::GetExpression() const
{
    return m_expression;
}

void FPropertyDeclarationStatement::Execute(const FContext& context) const
{
    AccessSpecifier accessMethod = AccessSpecifier::Private;
    if (m_visibility == "protected")
    {
        accessMethod = AccessSpecifier::Protected;
    }
    else if (m_visibility == "public")
    {
        accessMethod = AccessSpecifier::Public;
    }

    const auto& value = m_expression->Evaluate(context);
    context.GetCurrentClass()->AddProperty(m_name, accessMethod, value);
}
