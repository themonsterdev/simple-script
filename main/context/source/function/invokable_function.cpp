/**
 * @file invokable_function.cpp
 * @brief Implementation of the FInvokableFunction class.
 */

#include "function/invokable_function.hpp"
#include "statement/block/block_statement.hpp"
#include <stdexcept>
#include <memory>

 // Include declarations for context objects
#include "context.hpp"

FInvokableFunction::FInvokableFunction(std::string name, FunctionParameters parameters, IStatement* body)
    : m_name(name)
    , m_parameters(parameters)
    , m_body(body)
{}

Value FInvokableFunction::Invoke(const std::vector<Value>& arguments, const FContext& context) const
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

    // Créez un nouveau contexte pour l'appel de fonction
    FContext functionContext(context);

    // Mappez les arguments aux paramètres
    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        functionContext.SetVariable(m_parameters[i], arguments[i]);
    }

    // Exécutez le corps de la fonction dans le nouveau contexte
    const auto& block = dynamic_cast<FBlockStatement*>(m_body);
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
                // Reset the continue flag for the next iteration
                break; // Move to the next iteration
            }

            // Check if a throw statement has been encountered
            if (context.GetThrowFlag())
            {
                // Reset the throw flag for the next iteration
                break; // Move to the next iteration
            }
        }
    }
    else
    {
        throw std::runtime_error("Function body is null");
    }

    context.LeaveScope();

    if (context.HasReturnValue())
    {
        Value value = context.GetReturnValue();
        context.ResetReturnValue();
        return value;
    }

    return {}; // void ?
}

std::string FInvokableFunction::GetName() const
{
    return m_name;
}
