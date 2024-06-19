#include "value/string_value.hpp"
#include "value/number_value.hpp"

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

ValuePtr FStringValue::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    if (methodName == "substr")
    {
        return Substr(args);
    }
    else if (methodName == "length")
    {
        return Length();
    }

    return nullptr;
}

ValuePtr FStringValue::Substr(std::vector<ValuePtr> args) const
{
    if (args.size() < 2)
    {
        throw std::runtime_error("Expected two arguments for substr method.");
    }

    auto startObj = std::dynamic_pointer_cast<FNumberValue>(args[0]);
    auto lengthObj = std::dynamic_pointer_cast<FNumberValue>(args[1]);

    if (!startObj || !lengthObj)
    {
        throw std::runtime_error("Arguments for substr method must be numbers.");
    }

    size_t start  = startObj->GetValue();
    size_t length = lengthObj->GetValue();

    if (start >= m_value.size())
    {
        return std::make_shared<FStringValue>("");
    }

    return std::make_shared<FStringValue>(m_value.substr(start, length));
}

ValuePtr FStringValue::Length() const
{
    return std::make_shared<FNumberValue>(m_value.length());
}
