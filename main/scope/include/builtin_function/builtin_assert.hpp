#pragma once

#include <memory>
#include "function_value.hpp"

class FBuiltinAssertFunction : public CFunctionValue
{
public:

    FBuiltinAssertFunction(std::string name, FunctionParameters parameters);

    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

FunctionValuePtr CreateAssertFunction();
