#include "value/string_value.hpp"

FStringValue::FStringValue(const std::string& value)
    : m_value(value)
{}

bool FStringValue::IsString() const
{
    return true;
}

const std::string FStringValue::ToString() const
{
    return m_value;
}

void FStringValue::SetValue(const std::string value)
{
    m_value = value;
}

const std::string& FStringValue::GetValue() const
{
    return m_value;
}
