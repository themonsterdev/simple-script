#pragma once

#include <memory>

#include "statement/interface/statement.hpp"
#include "function/function_parameter.hpp"
#include "type.hpp"

class FContext;

class CFunctionDefinition
{
    std::string m_name;
    TypePtr m_returnType;
    FunctionParameters m_parameters;
    StatementPtr m_body;

public:

    CFunctionDefinition(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters,
        StatementPtr body
    );

    const std::string& GetName() const;
    TypePtr GetReturnType() const;
    const FunctionParameters& GetParameters() const;
    const StatementPtr& GetBody() const;

    virtual ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const;
};

using FunctionDefinitionPtr = std::shared_ptr<CFunctionDefinition>;
