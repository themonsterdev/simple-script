/**
 * @file class_method_definition.hpp
 * @brief Implementation of the FClassMethodDefinition class.
 */

#include "oop/class_method_definition.hpp"

FClassMethodDefinition::FClassMethodDefinition(
	const std::string& name,
	TypePtr returnType,
	FunctionParameters parameters)
	: m_name(name)
	, m_returnType(returnType)
	, m_parameters(parameters)
{}

const std::string& FClassMethodDefinition::GetName() const
{
	return m_name;
}

TypePtr FClassMethodDefinition::GetReturnType() const
{
	return m_returnType;
}

FunctionParameters FClassMethodDefinition::GetParameters() const
{
	return m_parameters;
}
