#include "type/enum/enum_definition.hpp"
#include "context/context.hpp"
#include <stdexcept>

FEnumDefinition::FEnumDefinition(
    const std::string& name,
    EnumValues values)
    : m_name(name)
    , m_values(values)
{}

const std::string& FEnumDefinition::GetName() const
{
    return m_name;
}

void FEnumDefinition::AddValue(const std::string& value, TypePtr type)
{
    m_values[value] = type;
}

TypePtr FEnumDefinition::GetValue(const std::string& name) const
{
    auto it = m_values.find(name);
    if (it != m_values.end())
    {
        return it->second;
    }

    throw std::runtime_error("Value '" + name + "' not found in enum definition.");
}

const EnumValues& FEnumDefinition::GetValues() const
{
    return m_values;
}
