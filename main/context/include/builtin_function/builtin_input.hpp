#pragma once

#include "function/function_definition.hpp"

class FBuiltinInputFunction final : public CFunctionDefinition
{
public:

    FBuiltinInputFunction(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const override;
};

FunctionDefinitionPtr CreateInputFunction();
