#pragma once

#include "abstract/value.hpp"
#include <vector>

class FStringValue final : public AValue
{
    std::string m_value;

public:

    FStringValue(const std::string& value);

    bool IsString() const override;
    const std::string ToString() const override;
    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;

    void SetValue(const std::string value);
    const std::string& GetValue() const;

    ValuePtr Substr(std::vector<ValuePtr> args) const;
    ValuePtr Length() const;
};

using StringValuePtr = std::shared_ptr<FStringValue>;
