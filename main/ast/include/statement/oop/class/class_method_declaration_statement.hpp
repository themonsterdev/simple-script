#pragma once

#include "statement/interface/statement.hpp"
#include "statement/function/function_parameter.hpp"
#include <string>

class FClassMethodDeclarationStatement final : public IStatement
{
    std::string m_methodVisibility;
    std::string m_methodName;
    FunctionParameters m_methodParameters;
    StatementPtr m_methodBody;

public:

    FClassMethodDeclarationStatement(
        const std::string methodVisibility,
        const std::string methodName,
        FunctionParameters methodParameters,
        StatementPtr methodBody
    );

    void Execute(const FContext& context) const override;

    const std::string& GetMethodVisibility() const;
    const std::string& GetMethodName() const;
    FunctionParameters GetMethodParameters() const;
    const StatementPtr& GetMethodBody() const;
};
