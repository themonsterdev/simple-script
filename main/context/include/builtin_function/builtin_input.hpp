#pragma once

#include <memory>
#include "function/invokable_function.hpp"

class FBuiltinInputFunction : public FInvokableFunction
{
public:

    FBuiltinInputFunction(std::string name, FunctionParameters parameters);

    Value Invoke(const std::vector<Value>& arguments, const FContext& context) const override;
};

std::shared_ptr<FInvokableFunction> CreateInputFunction();
