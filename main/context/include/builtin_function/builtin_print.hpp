#pragma once

#include "function/function_definition.hpp"

class FBuiltinPrintFunction final : public CFunctionDefinition
{
public:

    FBuiltinPrintFunction(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    FBuiltinPrintFunction(FunctionDefinitionPtr functionDefinition);

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const override;
};

FunctionDefinitionPtr CreatePrintFunction();
