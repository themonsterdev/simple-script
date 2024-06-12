/**
 * @file class_property_definition.hpp
 * @brief Declaration of the FClassPropertyDefinition struct.
 */

#pragma once

#include "type/type.hpp"

class FClassPropertyDefinition final
{
    std::string m_name;
    TypePtr m_type;

public:

    FClassPropertyDefinition(const std::string& name, TypePtr type);

    const std::string& GetName() const;
    TypePtr GetType() const;
};

using ClassPropertyDefinitionPtr = std::shared_ptr<FClassPropertyDefinition>;
