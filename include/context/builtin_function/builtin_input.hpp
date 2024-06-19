#pragma once

#include "value/function_value.hpp"

class FBuiltinInputFunction final : public CFunctionValue
{
public:

    FBuiltinInputFunction(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

FunctionValuePtr CreateInputFunction();
