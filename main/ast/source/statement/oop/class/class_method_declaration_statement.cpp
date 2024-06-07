#include "statement/oop/class/class_method_declaration_statement.hpp"

#include "context.hpp"
#include "function_value.hpp"

FClassMethodDeclarationStatement::FClassMethodDeclarationStatement(
    const std::string methodVisibility,
    const std::string methodName,
    FunctionParameters methodParameters,
    StatementPtr methodBody)
    : m_methodVisibility(methodVisibility)
    , m_methodName(methodName)
    , m_methodParameters(methodParameters)
    , m_methodBody(std::move(methodBody))
{}

void FClassMethodDeclarationStatement::Execute(const FContext& context) const
{
    const auto& functionValue = std::make_shared<CFunctionValue>(m_methodName);

    functionValue->SetParameters(m_methodParameters);
    functionValue->SetBody(m_methodBody.get());

    AccessSpecifier accessMethod = AccessSpecifier::Private;
    if (m_methodVisibility == "protected")
    {
        accessMethod = AccessSpecifier::Protected;
    }
    else if (m_methodVisibility == "public")
    {
        accessMethod = AccessSpecifier::Public;
    }
    context.GetCurrentClass()->AddMethod(m_methodName, accessMethod, functionValue);
}

const std::string& FClassMethodDeclarationStatement::GetMethodVisibility() const
{
    return m_methodVisibility;
}

const std::string& FClassMethodDeclarationStatement::GetMethodName() const
{
    return m_methodName;
}

FunctionParameters FClassMethodDeclarationStatement::GetMethodParameters() const
{
    return m_methodParameters;
}

const StatementPtr& FClassMethodDeclarationStatement::GetMethodBody() const
{
    return m_methodBody;
}
