#pragma once

#include "type/function/function_definition.hpp"
#include "ast/statement/block/block_statement.hpp"
#include "context/context.hpp"
#include <stdexcept>

CFunctionDefinition::CFunctionDefinition(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters,
    StatementPtr body)
    : m_name(name)
    , m_returnType(returnType)
    , m_parameters(parameters)
    , m_body(std::move(body))
{}

const std::string& CFunctionDefinition::GetName() const
{
    return m_name;
}

TypePtr CFunctionDefinition::GetReturnType() const
{
    return m_returnType;
}

const FunctionParameters& CFunctionDefinition::GetParameters() const
{
    return m_parameters;
}

const StatementPtr& CFunctionDefinition::GetBody() const
{
    return m_body;
}

ValuePtr CFunctionDefinition::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    context.EnterScope();
    context.ResetReturnValue();
    context.SetContinueFlag(false);
    context.SetThrowFlag(false);

    // Vérifiez que le nombre d'arguments correspond au nombre de paramètres
    if (arguments.size() != m_parameters.size())
    {
        throw std::runtime_error("Incorrect number of arguments provided for function call");
    }

    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        context.SetVariable(m_parameters[i].name, arguments[i]);
    }

    // Exécutez le corps de la fonction dans le nouveau contexte
    const auto& block = dynamic_cast<FBlockStatement*>(m_body.get());
    if (m_body)
    {
        // Execute each statement in the block sequentially
        for (const auto& statement : block->GetStatements())
        {
            statement->Execute(context);

            // Check if a return value has been set
            if (context.HasReturnValue())
            {
                // Exit the loop if a return statement was executed
                break;
            }

            // Check if a continue statement has been encountered
            if (context.GetContinueFlag())
            {
                // Exit the loop
                break;
            }

            // Check if a throw statement has been encountered
            if (context.GetThrowFlag())
            {
                // Exit the loop
                break;
            }
        }
    }
    // else // is builtin is a not body declared
    // {
    //     throw std::runtime_error("Function body is null");
    // }

    context.LeaveScope();

    if (context.HasReturnValue())
    {
        ValuePtr value = context.GetReturnValue();
        context.ResetReturnValue();
        return value;
    }

    return {}; // void ?
}
