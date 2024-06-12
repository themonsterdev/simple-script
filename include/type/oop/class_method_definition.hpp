/**
 * @file class_method_definition.hpp
 * @brief Declaration of the ClassMethod class.
 */

#pragma once

#include "type/type.hpp"
#include "type/function/function_parameter.hpp"

class FClassMethodDefinition final
{
    std::string m_name;
    TypePtr m_returnType;
    FunctionParameters m_parameters;

public:

    FClassMethodDefinition(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    const std::string& GetName() const;
    TypePtr GetReturnType() const;
    FunctionParameters GetParameters() const;
};

using ClassMethodDefinitionPtr = std::shared_ptr<FClassMethodDefinition>;
