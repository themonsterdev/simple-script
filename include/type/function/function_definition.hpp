#pragma once

#include <memory>
#include <vector>

#include "ast/statement/interface/statement.hpp"

using FunctionParameters = std::vector<std::string>;

class CFunctionDefinition
{
    std::string m_functionName;
    FunctionParameters m_parameters;
    std::string m_returnType;
    StatementPtr m_body;

public:

    CFunctionDefinition(
        const std::string& functionName,
        const FunctionParameters& parameters,
        const std::string& returnType,
        StatementPtr body
    );

    const std::string& GetFunctionName() const;
    const FunctionParameters& GetParameters() const;
    const std::string& GetReturnType() const;
    const StatementPtr& GetBody() const;
};

using FunctionDefinitionPtr = std::shared_ptr<CFunctionDefinition>;
