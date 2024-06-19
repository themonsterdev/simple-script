/**
 * @file class_definition.hpp
 * @brief Declaration of the FClassDefinition class.
 */

#pragma once

#include <vector>
#include <unordered_map>

#include "value/interface/value.hpp"

enum class Visibility
{
    Private,
    Protected,
    Public
};

using InterfaceVector = std::vector<std::string>;
using ClassMemberMap  = std::unordered_map<std::string, ValuePtr>;
using VisibilityUnorderedMap = std::unordered_map<std::string, Visibility>;

class FClassDefinition final
{
    std::string            m_name;
    std::string            m_parent;
    InterfaceVector        m_interfaces;
    ClassMemberMap         m_members;
    VisibilityUnorderedMap m_visibility;

public:

    FClassDefinition(const std::string& name);

    const std::string& GetName() const;

    void SetParent(const std::string& parent);
    const std::string& GetParent() const;

    void AddInterface(const std::string& interface);
    const InterfaceVector& GetInterfaces() const;

    void AddMember(const std::string& name, ValuePtr value);
    ValuePtr GetMember(const std::string& name) const;
    bool HasMember(const std::string& name) const;
};

using ClassDefinitionPtr = std::shared_ptr<FClassDefinition>;
