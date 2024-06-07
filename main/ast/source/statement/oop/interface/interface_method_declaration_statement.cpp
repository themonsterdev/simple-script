#include "statement/oop/interface/interface_method_declaration_statement.hpp"
#include "context.hpp"

FInterfaceMethodDeclarationStatement::FInterfaceMethodDeclarationStatement(
    const std::string& visibility,
    const std::string& name,
    const std::string& returnValue,
    FunctionParameters parameters)
    : m_visibility(visibility)
    , m_name(name)
    , m_returnValue(returnValue)
    , m_parameters(parameters)
{}

void FInterfaceMethodDeclarationStatement::Execute(const FContext& context) const
{
    // context.RegisterInterfaceMethod(m_visibility, m_name, m_returnValue, m_parameters);
}

const std::string& FInterfaceMethodDeclarationStatement::GetVisibility() const
{
    return m_visibility;
}

const std::string& FInterfaceMethodDeclarationStatement::GetMethodName() const
{
    return m_name;
}

FunctionParameters FInterfaceMethodDeclarationStatement::GetParameters() const
{
    return m_parameters;
}
