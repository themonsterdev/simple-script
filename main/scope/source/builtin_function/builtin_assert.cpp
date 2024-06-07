#include "builtin_function/builtin_assert.hpp"

#include "boolean_value.hpp"
#include "number_value.hpp"
#include "string_value.hpp"

#include <iostream>

FBuiltinAssertFunction::FBuiltinAssertFunction(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinAssertFunction::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    if (arguments.size() < 1)
    {
        throw std::runtime_error("assert function expects one argument");
    }

    ValuePtr value = arguments[0];
    bool condition = false;

    if (value->IsBoolean())
    {
        const auto& result = std::dynamic_pointer_cast<FBooleanValue>(value);

        condition = result->GetValue();
    }
    else if (value->IsNumber())
    {
        const auto& result = std::dynamic_pointer_cast<FNumberValue>(value);
        condition = result->GetValue() > 0;
    }
    else if (value->IsString())
    {
        const auto& result = std::dynamic_pointer_cast<FStringValue>(value);
        condition = result->GetValue().length() > 0;
    }

    std::string error = "";
    if (arguments.size() == 2)
    {
        // error = std::get<std::string>(arguments[1]);
    }

    if (!condition)
    {
        // Throw an exception with the optional message if the assertion fails
        throw std::runtime_error(error.empty() ? "Assertion failed" : "Assertion failed: " + error);
    }

    return {};
}

FunctionValuePtr CreateAssertFunction()
{
    std::string name = "assert";
    FunctionParameters parameters = { {"condition", ""}, {"error", ""}  };
    return std::make_shared<FBuiltinAssertFunction>(name, parameters);
}
