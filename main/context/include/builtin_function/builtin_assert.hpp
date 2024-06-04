#pragma once

#include <memory>
#include "function/invokable_function.hpp"

class FBuiltinAssertFunction : public FInvokableFunction
{
public:

    FBuiltinAssertFunction(std::string name, FunctionParameters parameters);

    Value Invoke(const std::vector<Value>& arguments, const FContext& context) const override;
};

std::shared_ptr<FInvokableFunction> CreateAssertFunction();
