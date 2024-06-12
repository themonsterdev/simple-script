#include "context/builtin_function/builtin_print.hpp"
#include <iostream>

FBuiltinPrintFunction::FBuiltinPrintFunction(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinPrintFunction::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    for (const auto& arg : arguments)
    {
        std::cout << arg->ToString();
    }
    std::cout << std::endl;
    return {};
}

FunctionDefinitionPtr CreatePrintFunction()
{
    std::string name   = "print";
    TypePtr returnType = std::make_shared<FType>("void");

    FunctionParameters parameters = {
        { "expression", "any" }
    };

    return std::make_shared<FBuiltinPrintFunction>(
        name,
        returnType,
        parameters
    );
}
