/**
 * @file class_definition.cpp
 * @brief Implementation of the FClassDefinition class.
 */

#include "type/oop/class_definition.hpp"
#include "value/object_value.hpp"
#include "context/context.hpp"

FClassDefinition::FClassDefinition(const std::string& name)
	: m_name(name)
	, m_interfaces({})
	, m_properties({})
	, m_methods({})
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

void FClassDefinition::AddProperty(Visibility visibility, ClassPropertyDefinitionPtr property)
{
	const auto& name   = property->GetName();
	m_visibility[name] = visibility;
	m_properties[name] = property;
}

bool FClassDefinition::HasProperty(const std::string& name) const
{
	return m_properties.find(name) != m_properties.end();
}

ClassPropertyDefinitionPtr FClassDefinition::GetProperty(const std::string& name) const
{
	auto it = m_properties.find(name);
	if (it != m_properties.end())
	{
		return it->second;
	}
	return nullptr;
}

PropertyUnorderedMap FClassDefinition::GetProperties() const
{
	return m_properties;
}

void FClassDefinition::AddMethod(Visibility visibility, ClassMethodDefinitionPtr method)
{
	const auto& name   = method->GetName();
	m_visibility[name] = visibility;
	m_methods[name]    = method;
}

bool FClassDefinition::HasMethod(const std::string& name) const
{
	return m_methods.find(name) != m_methods.end();
}

ClassMethodDefinitionPtr FClassDefinition::GetMethod(const std::string& name) const
{
	auto it = m_methods.find(name);
	if (it != m_methods.end())
	{
		return it->second;
	}
	return nullptr;
}

MethodUnorderedMap FClassDefinition::GetMethods() const
{
	return m_methods;
}

ValuePtr FClassDefinition::NewInstance(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
	// Create an instance of the class with its name
	auto instance = std::make_unique<FObjectValue>(m_name);

	// Handle the parent class if defined
	if (!m_parent.empty())
	{
		const auto& parentDefinition = context.GetClassDefinition(m_parent);

		for (const auto& property : parentDefinition->GetProperties())
		{
			const auto& defaultValue = property.second->GetType()->GetDefaultValue();
			context.SetVariable(property.first, defaultValue);

			// instance->AddProperty(property.first, defaultValue);
		}
	}

	// Handle interfaces implemented by the class
	for (const auto& interface : m_interfaces)
	{

	}

	// Initialize properties of the class
	for (const auto& property : m_properties)
	{
		const auto& defaultValue = property.second->GetType()->GetDefaultValue();
		context.SetVariable(property.first, defaultValue);
	}

	// Initialize methods of the class
	for (const auto& method : m_methods)
	{

	}

	// Return the created and initialized instance
	return instance;
}
