#pragma once

#include "value/abstract/value.hpp"
#include "ast/statement/interface/statement.hpp"
#include "type/function/function_definition.hpp"

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
