/**
 * @file type.hpp
 * @brief Declaration of the FType class.
 */

#pragma once

#include <string>
#include <memory>

#include "value/interface/value.hpp"

class FType final
{
    std::string m_name;
    ValuePtr m_defaultValue;

public:

    FType(const std::string& name);

    const std::string& GetName() const;

    void SetDefaultValue(ValuePtr defaultValue);
    const ValuePtr GetDefaultValue() const;
};

using TypePtr = std::shared_ptr<FType>;
