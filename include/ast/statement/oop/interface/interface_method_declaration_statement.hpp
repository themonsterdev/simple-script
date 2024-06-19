#pragma once

#include "ast/statement/interface/statement.hpp"
#include "value/function_value.hpp"

class FInterfaceMethodDeclarationStatement final : public IStatement
{
    std::string m_visibility;
    std::string m_name;
    std::string m_returnValue;
    FunctionParameters m_parameters;

public:

    FInterfaceMethodDeclarationStatement(
        const std::string& visibility,
        const std::string& name,
        const std::string& returnValue,
        FunctionParameters parameters
    );

    void Execute(const FContext& context) const override;

    const std::string& GetVisibility() const;
    const std::string& GetMethodName() const;
    FunctionParameters GetParameters() const;
};
