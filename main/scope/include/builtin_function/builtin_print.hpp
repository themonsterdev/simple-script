#pragma once

#include <memory>
#include "function_value.hpp"

class FBuiltinPrintFunction : public CFunctionValue
{
public:

    FBuiltinPrintFunction(std::string name, FunctionParameters parameters);

    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

FunctionValuePtr CreatePrintFunction();
