#pragma once

#include "value/function_value.hpp"

class FBuiltinAssertFunction final : public CFunctionValue
{
public:

    FBuiltinAssertFunction(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

FunctionValuePtr CreateAssertFunction();
