#pragma once

#include "abstract/value.hpp"

class FStringValue final : public AValue
{
    std::string m_value;

public:

    FStringValue(const std::string& value);

    bool IsString() const override;
    const std::string ToString() const override;

    void SetValue(const std::string value);
    const std::string& GetValue() const;
};

using StringValuePtr = std::shared_ptr<FStringValue>;
