#include "builtin_function/builtin_assert.hpp"
#include <iostream>

FBuiltinAssertFunction::FBuiltinAssertFunction(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinAssertFunction::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    if (arguments.size() < 1)
    {
        throw std::runtime_error("assert function expects one argument");
    }

    Value value = arguments[0];
    bool condition = value != Value(0)
        && value != Value(false)
        && value != Value("");

    std::string error = "";
    if (arguments.size() == 2)
    {
        error = std::get<std::string>(arguments[1]);
    }

    if (!condition)
    {
        // Throw an exception with the optional message if the assertion fails
        throw std::runtime_error(error.empty() ? "Assertion failed" : "Assertion failed: " + error);
    }

    return {};
}

std::shared_ptr<FInvokableFunction> CreateAssertFunction()
{
    std::string name = "assert";
    FunctionParameters parameters = { "condition", "error" };
    return std::make_shared<FBuiltinAssertFunction>(name, parameters);
}
