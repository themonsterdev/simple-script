#include "context/builtin_function/builtin_input.hpp"
#include "value/string_value.hpp"
#include <iostream>

FBuiltinInputFunction::FBuiltinInputFunction(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinInputFunction::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    for (const auto& arg : arguments)
    {
        std::cout << arg->ToString();
    }

    std::string input;
    std::getline(std::cin, input);
    return std::make_shared<FStringValue>(input);
}

FunctionDefinitionPtr CreateInputFunction()
{
    std::string name   = "input";
    TypePtr returnType = std::make_shared<FType>(eTypeKind::STRING);

    FunctionParameters parameters = {
        { "question", "string" }
    };

    return std::make_shared<FBuiltinInputFunction>(
        name,
        returnType,
        parameters
    );
}
