#include "value/boolean_value.hpp"

FBooleanValue::FBooleanValue(bool value)
    : m_value(value)
{}

bool FBooleanValue::IsBoolean() const
{
    return true;
}

const std::string FBooleanValue::ToString() const
{
    return m_value ? "true" : "false";
}

bool FBooleanValue::GetValue() const
{
    return m_value;
}
