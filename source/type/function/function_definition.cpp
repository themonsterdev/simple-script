#include "type/function/function_definition.hpp"

CFunctionDefinition::CFunctionDefinition(
    const std::string& functionName,
    const FunctionParameters& parameters,
    const std::string& returnType,
    StatementPtr body)
    : m_functionName(functionName)
    , m_parameters(parameters)
    , m_returnType(returnType)
    , m_body(std::move(body))
{}

const std::string& CFunctionDefinition::GetFunctionName() const
{
    return m_functionName;
}

const FunctionParameters& CFunctionDefinition::GetParameters() const
{
    return m_parameters;
}

const std::string& CFunctionDefinition::GetReturnType() const
{
    return m_returnType;
}

const StatementPtr& CFunctionDefinition::GetBody() const
{
    return m_body;
}
