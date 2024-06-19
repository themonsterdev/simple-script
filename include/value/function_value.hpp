#pragma once

#include "value/abstract/value.hpp"
#include "type/function/function_definition.hpp"

class CFunctionValue : public AValue
{
    FunctionDefinitionPtr m_functionDefinition;

public:

    CFunctionValue(FunctionDefinitionPtr functionDefinition);

    bool IsFunction() const override;
    const std::string ToString() const override;
    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;

    const FunctionDefinitionPtr& GetFunctionDefinition() const;
};

using FunctionValuePtr = std::shared_ptr<CFunctionValue>;
