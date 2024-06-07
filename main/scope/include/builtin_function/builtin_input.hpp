#pragma once

#include <memory>
#include "function_value.hpp"

class FBuiltinInputFunction : public CFunctionValue
{
public:

    FBuiltinInputFunction(std::string name, FunctionParameters parameters);

    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

FunctionValuePtr CreateInputFunction();
