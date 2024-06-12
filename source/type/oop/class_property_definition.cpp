/**
 * @file property_definition.cpp
 * @brief Implementation of the PropertyDefinition struct.
 */

#include "type/oop/class_property_definition.hpp"

FClassPropertyDefinition::FClassPropertyDefinition(const std::string& name, TypePtr type)
    : m_name(name)
    , m_type(std::move(type))
{}

const std::string& FClassPropertyDefinition::GetName() const
{
    return m_name;
}

TypePtr FClassPropertyDefinition::GetType() const
{
    return m_type;
}
