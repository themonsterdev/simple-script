#include "builtin_function/builtin_print.hpp"
#include <iostream>

FBuiltinPrintFunction::FBuiltinPrintFunction(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinPrintFunction::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    for (const auto& arg : arguments)
    {
        std::cout << arg->ToString();
    }
    std::cout << std::endl;
    return {};
}

FunctionValuePtr CreatePrintFunction()
{
    std::string name = "print";
    FunctionParameters parameters = { {"string", "string"} };
    return std::make_shared<FBuiltinPrintFunction>(name, parameters);
}
