#pragma once

#include "abstract/value.hpp"
#include "statement/interface/statement.hpp"
#include "statement/function/function_parameter.hpp"
#include <vector>

class FContext;

class CFunctionValue : public AValue
{
    std::string m_name;
    FunctionParameters m_parameters;
    IStatement* m_body;

public:

    CFunctionValue(const std::string& name);

    bool IsFunction() const override;
    const std::string ToString() const override;

    const std::string& GetValue() const;

    void SetParameters(const FunctionParameters& parameters);
    void SetBody(IStatement* body);

    virtual ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const;
};

using FunctionValuePtr = std::shared_ptr<CFunctionValue>;
