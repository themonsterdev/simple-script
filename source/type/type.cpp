/**
 * @file type.cpp
 * @brief Implementation of the FType class.
 */

#include "type/type.hpp"

FType::FType(eTypeKind kind)
	: m_kind(kind)
	, m_defaultValue(nullptr)
{}

const eTypeKind& FType::GetKind() const
{
	return m_kind;
}

void FType::SetDefaultValue(ValuePtr defaultValue)
{
	m_defaultValue = defaultValue;
}

const ValuePtr FType::GetDefaultValue() const
{
	return m_defaultValue;
}
