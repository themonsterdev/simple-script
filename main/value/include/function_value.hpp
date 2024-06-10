#pragma once

#include "abstract/value.hpp"
#include "statement/interface/statement.hpp"
#include "function/function_parameter.hpp"
#include "function/function_definition.hpp"
#include <vector>

class FContext;

class CFunctionValue : public AValue
{
    FunctionDefinitionPtr m_functionDefinition;

public:

    CFunctionValue(FunctionDefinitionPtr functionDefinition);

    bool IsFunction() const override;
    const std::string ToString() const override;

    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const;
};

using FunctionValuePtr = std::shared_ptr<CFunctionValue>;
