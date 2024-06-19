#include "context/builtin_function/builtin_assert.hpp"

#include "value/boolean_value.hpp"
#include "value/number_value.hpp"
#include "value/string_value.hpp"

#include <iostream>

FBuiltinAssertFunction::FBuiltinAssertFunction(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinAssertFunction::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    if (args.size() < 1)
    {
        throw std::runtime_error("assert function expects one argument");
    }

    ValuePtr value = args[0];
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
    if (args.size() == 2)
    {
        // error = std::get<std::string>(args[1]);
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
    std::string functionName = "assert";
    FunctionParameters parameters = { "boolean", "string" };
    std::string returnType = "void";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinAssertFunction>(definition);
}
