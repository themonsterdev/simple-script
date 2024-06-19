#pragma once

#include "value/function_value.hpp"

class FBuiltinPrintFunction final : public CFunctionValue
{
public:

    FBuiltinPrintFunction(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

FunctionValuePtr CreatePrintFunction();
