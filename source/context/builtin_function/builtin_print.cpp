#include "context/builtin_function/builtin_print.hpp"
#include <iostream>

FBuiltinPrintFunction::FBuiltinPrintFunction(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinPrintFunction::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    for (const auto& arg : args)
    {
        std::cout << arg->ToString();
    }
    std::cout << std::endl;
    return {};
}

FunctionValuePtr CreatePrintFunction()
{
    std::string functionName = "print";
    FunctionParameters parameters = { "any" };
    std::string returnType = "void";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinPrintFunction>(definition);
}
