#include "context/builtin_function/builtin_input.hpp"
#include "value/string_value.hpp"
#include <iostream>

FBuiltinInputFunction::FBuiltinInputFunction(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinInputFunction::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    for (const auto& arg : args)
    {
        std::cout << arg->ToString();
    }

    std::string input;
    std::getline(std::cin, input);
    return std::make_shared<FStringValue>(input);
}

FunctionValuePtr CreateInputFunction()
{
    std::string functionName = "input";
    FunctionParameters parameters = { "string" };
    std::string returnType = "string";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinInputFunction>(definition);
}
