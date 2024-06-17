#pragma once

#include "abstract/value.hpp"
#include <vector>

using ArrayElementVector = std::vector<ValuePtr>;

class FArrayValue final : public AValue
{
    ArrayElementVector m_elements;

public:

    FArrayValue(ArrayElementVector elements);

    bool IsArray() const override;
    const std::string ToString() const override;

    const ArrayElementVector& GetElements() const;
    const ValuePtr& GetElement(uint32_t index) const;
};
