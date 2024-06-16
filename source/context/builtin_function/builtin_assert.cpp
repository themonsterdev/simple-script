#include "context/builtin_function/builtin_assert.hpp"

#include "value/boolean_value.hpp"
#include "value/number_value.hpp"
#include "value/string_value.hpp"

#include <iostream>

FBuiltinAssertFunction::FBuiltinAssertFunction(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinAssertFunction::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
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

FunctionDefinitionPtr CreateAssertFunction()
{
    std::string name = "assert";
    TypePtr returnType = std::make_shared<FType>(eTypeKind::VOID);

    FunctionParameters parameters = {
        { "condition", "boolean" },
        { "error", "string" },
    };

    return std::make_shared<FBuiltinAssertFunction>(
        name,
        returnType,
        parameters
    );
}
