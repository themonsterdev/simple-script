#include "builtin_function/builtin_input.hpp"
#include "string_value.hpp"
#include <iostream>

FBuiltinInputFunction::FBuiltinInputFunction(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinInputFunction::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    for (const auto& arg : arguments)
    {
        std::cout << arg->ToString();
    }

    std::string input;
    std::getline(std::cin, input);
    return std::make_shared<FStringValue>(input);
}

FunctionValuePtr CreateInputFunction()
{
    std::string name = "input";
    FunctionParameters parameters = { {"string", "string" }};
    return std::make_shared<FBuiltinInputFunction>(name, parameters);
}
