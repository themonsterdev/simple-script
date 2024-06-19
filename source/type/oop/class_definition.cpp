/**
 * @file class_definition.cpp
 * @brief Implementation of the FClassDefinition class.
 */

#include "type/oop/class_definition.hpp"

FClassDefinition::FClassDefinition(const std::string& name)
	: m_name(name)
	, m_interfaces({})
	, m_members({})
	, m_visibility({})
{}

const std::string& FClassDefinition::GetName() const
{
	return m_name;
}

void FClassDefinition::SetParent(const std::string& parent)
{
	m_parent = parent;
}

const std::string& FClassDefinition::GetParent() const
{
	return m_parent;
}

void FClassDefinition::AddInterface(const std::string& interface)
{
	m_interfaces.push_back(interface);
}

const InterfaceVector& FClassDefinition::GetInterfaces() const
{
	return m_interfaces;
}

void FClassDefinition::AddMember(const std::string& name, ValuePtr value)
{
	m_members[name] = value;
}

ValuePtr FClassDefinition::GetMember(const std::string& name) const
{
	auto it = m_members.find(name);
    if (it != m_members.end())
	{
        return it->second;
    }

	if (!m_parent.empty())
    {
        
    }

	throw std::runtime_error("Member '" + name + "' not found in class '" + m_name + "'");
}

bool FClassDefinition::HasMember(const std::string& name) const
{
	return m_members.find(name) != m_members.end();
}
