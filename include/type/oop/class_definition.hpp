/**
 * @file class_definition.hpp
 * @brief Declaration of the FClassDefinition class.
 */

#pragma once

#include <unordered_map>
#include <vector>

#include "type/oop/class_property_definition.hpp"
#include "type/oop/class_method_definition.hpp"

class FContext;

enum class Visibility
{
    Private,
    Protected,
    Public
};

using InterfaceVector        = std::vector<std::string>;
using PropertyUnorderedMap   = std::unordered_map<std::string, ClassPropertyDefinitionPtr>;
using MethodUnorderedMap     = std::unordered_map<std::string, ClassMethodDefinitionPtr>;
using VisibilityUnorderedMap = std::unordered_map<std::string, Visibility>;

class FClassDefinition final
{
    std::string            m_name;
    std::string            m_parent;
    InterfaceVector        m_interfaces;
    PropertyUnorderedMap   m_properties;
    MethodUnorderedMap     m_methods;
    VisibilityUnorderedMap m_visibility;

public:

    FClassDefinition(const std::string& name);

    const std::string& GetName() const;

    void SetParent(const std::string& parent);
    const std::string& GetParent() const;

    void AddInterface(const std::string& interface);
    const InterfaceVector& GetInterfaces() const;

    void AddProperty(Visibility visibility, ClassPropertyDefinitionPtr property);
    bool HasProperty(const std::string& name) const;
    ClassPropertyDefinitionPtr GetProperty(const std::string& name) const;
    PropertyUnorderedMap GetProperties() const;

    void AddMethod(Visibility visibility, ClassMethodDefinitionPtr method);
    bool HasMethod(const std::string& name) const;
    ClassMethodDefinitionPtr GetMethod(const std::string& name) const;
    MethodUnorderedMap GetMethods() const;

    ValuePtr NewInstance(const FContext& context, const std::vector<ValuePtr>& arguments) const;
};

using ClassDefinitionPtr = std::shared_ptr<FClassDefinition>;
