#include "value/number_value.hpp"

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

ValuePtr FNumberValue::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    return nullptr;
}

void FNumberValue::SetValue(int value)
{
    m_value = value;
}

int FNumberValue::GetValue() const
{
    return m_value;
}
