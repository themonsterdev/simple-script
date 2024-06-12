/**
 * @file type.cpp
 * @brief Implementation of the FType class.
 */

#include "type/type.hpp"

FType::FType(const std::string& name)
	: m_name(name)
	, m_defaultValue(nullptr)
{}

const std::string& FType::GetName() const
{
	return m_name;
}

void FType::SetDefaultValue(ValuePtr defaultValue)
{
	m_defaultValue = defaultValue;
}

const ValuePtr FType::GetDefaultValue() const
{
	return m_defaultValue;
}
