#pragma once

#include "abstract/value.hpp"

class FNumberValue final : public AValue
{
    int m_value;

public:

    FNumberValue(int value);

    bool IsNumber() const override;
    const std::string ToString() const override;
    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;

    void SetValue(int value);
    int GetValue() const;
};

using NumberValuePtr = std::shared_ptr<FNumberValue>;
