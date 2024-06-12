#pragma once

#include "type/type.hpp"
#include <unordered_map>

class FContext;

using EnumValues = std::unordered_map<std::string, TypePtr>;

class FEnumDefinition final
{
    std::string m_name;
    EnumValues  m_values;

public:

    FEnumDefinition(
        const std::string& name,
        EnumValues values
    );

    const std::string& GetName() const;

    void AddValue(const std::string& value, TypePtr type);
    TypePtr GetValue(const std::string& name) const;
    const EnumValues& GetValues() const;
};

using EnumDefinitionPtr = std::shared_ptr<FEnumDefinition>;
