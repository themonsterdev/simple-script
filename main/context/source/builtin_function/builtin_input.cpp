#include "builtin_function/builtin_input.hpp"
#include <iostream>

FBuiltinInputFunction::FBuiltinInputFunction(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinInputFunction::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    for (const auto& arg : arguments)
    {
        std::visit([](auto&& value) { std::cout << value; }, arg);
    }

    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::shared_ptr<FInvokableFunction> CreateInputFunction()
{
    std::string name = "input";
    FunctionParameters parameters = { "string" };
    return std::make_shared<FBuiltinInputFunction>(name, parameters);
}
