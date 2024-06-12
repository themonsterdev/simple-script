#pragma once

#include "abstract/value.hpp"

class FBooleanValue final : public AValue
{
    bool m_value;

public:

    FBooleanValue(bool value);

    bool IsBoolean() const override;
    const std::string ToString() const override;

    bool GetValue() const;
};
