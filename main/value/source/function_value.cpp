#include "function_value.hpp"
#include "statement/block/block_statement.hpp"
#include "context.hpp"

#include <stdexcept>

CFunctionValue::CFunctionValue(FunctionDefinitionPtr functionDefinition)
    : m_functionDefinition(functionDefinition)
{}

bool CFunctionValue::IsFunction() const
{
    return true;
}

const std::string CFunctionValue::ToString() const
{
    return m_functionDefinition->GetName();
}

ValuePtr CFunctionValue::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    context.EnterScope();
    context.ResetReturnValue();
    context.SetContinueFlag(false);
    context.SetThrowFlag(false);

    const auto& parameters = m_functionDefinition->GetParameters();

    // Vérifiez que le nombre d'arguments correspond au nombre de paramètres
    if (arguments.size() != parameters.size())
    {
        throw std::runtime_error("Incorrect number of arguments provided for function call");
    }

    for (size_t i = 0; i < parameters.size(); ++i)
    {
        context.SetVariable(parameters[i].name, arguments[i]);
    }

    // Exécutez le corps de la fonction dans le nouveau contexte
    const auto& block = dynamic_cast<FBlockStatement*>(m_functionDefinition->GetBody().get());
    if (block)
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
    else
    {
        throw std::runtime_error("Function body is null");
    }

    context.LeaveScope();

    if (context.HasReturnValue())
    {
        ValuePtr value = context.GetReturnValue();
        context.ResetReturnValue();
        return value;
    }

    return {}; // void ?
}
