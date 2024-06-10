#pragma once

#include "function/function_definition.hpp"

class FBuiltinAssertFunction final : public CFunctionDefinition
{
public:

    FBuiltinAssertFunction(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const override;
};

FunctionDefinitionPtr CreateAssertFunction();
