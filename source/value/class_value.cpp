#include "value/class_value.hpp"
#include "context/context.hpp"
#include <stdexcept>

FClassValue::FClassValue(ClassDefinitionPtr definition)
    : m_definition(definition)
{}

bool FClassValue::IsClass() const
{
    return true;
}

const std::string FClassValue::ToString() const
{
    std::string str("Class(");
    str += m_definition->GetName();
    str += ")";
    return str;
}

ValuePtr FClassValue::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    return context.GetSymbol(m_definition->GetName());
}

const std::string& FClassValue::GetName() const
{
    return m_definition->GetName();
}

void FClassValue::SetParent(const std::string& parent)
{
    m_definition->SetParent(parent);
}

const std::string& FClassValue::GetParent() const
{
    return m_definition->GetParent();
}

void FClassValue::AddInterface(const std::string& interface)
{
    m_definition->AddInterface(interface);
}

const InterfaceVector& FClassValue::GetInterfaces() const
{
    return m_definition->GetInterfaces();
}

void FClassValue::AddMember(const std::string& name, ValuePtr value)
{
    m_definition->AddMember(name, value);
}

ValuePtr FClassValue::GetMember(const std::string& name) const
{
    return m_definition->GetMember(name);
}

bool FClassValue::HasMember(const std::string& name) const
{
    return m_definition->HasMember(name);
}
