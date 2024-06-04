#include "builtin_function/builtin_print.hpp"
#include <iostream>

FBuiltinPrintFunction::FBuiltinPrintFunction(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinPrintFunction::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    for (const auto& arg : arguments)
    {
        std::visit([](auto&& value) { std::cout << value; }, arg);
    }
    std::cout << std::endl;
    return {};
}

std::shared_ptr<FInvokableFunction> CreatePrintFunction()
{
    std::string name = "print";
    FunctionParameters parameters = { "string" };
    return std::make_shared<FBuiltinPrintFunction>(name, parameters);
}
