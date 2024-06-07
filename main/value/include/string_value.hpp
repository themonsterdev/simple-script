#pragma once

#include "abstract/value.hpp"

class FStringValue final : public AValue
{
    std::string m_value;

public:

    FStringValue(const std::string& value);

    bool IsString() const override;
    const std::string ToString() const override;

    const std::string& GetValue() const;
};
