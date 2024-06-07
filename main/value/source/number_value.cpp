#include "number_value.hpp"

FNumberValue::FNumberValue(int value)
    : m_value(value)
{}

bool FNumberValue::IsNumber() const
{
    return true;
}

const std::string FNumberValue::ToString() const
{
    return std::to_string(m_value);
}

int FNumberValue::GetValue() const
{
    return m_value;
}
