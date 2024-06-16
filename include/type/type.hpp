/**
 * @file type.hpp
 * @brief Declaration of the FType class.
 */

#pragma once

#include <string>
#include <memory>

#include "value/interface/value.hpp"

enum class eTypeKind
{
    ANY,
    VOID,
    NUMBER,
    STRING,
    BOOLEAN,
    FUNCTION,
    CLASS,
};

class FType final
{
    eTypeKind m_kind;
    ValuePtr m_defaultValue;

public:

    FType(eTypeKind name);

    const eTypeKind& GetKind() const;

    void SetDefaultValue(ValuePtr defaultValue);
    const ValuePtr GetDefaultValue() const;
};

using TypePtr = std::shared_ptr<FType>;
