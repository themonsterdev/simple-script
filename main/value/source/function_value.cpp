#include "function_value.hpp"
#include "statement/block/block_statement.hpp"
#include "context.hpp"

#include <stdexcept>

CFunctionValue::CFunctionValue(const std::string& name)
    : m_name(name)
    , m_parameters({})
    , m_body(nullptr)
{}

bool CFunctionValue::IsFunction() const
{
    return true;
}

const std::string CFunctionValue::ToString() const
{
    return m_name;
}

const std::string& CFunctionValue::GetValue() const
{
    return m_name;
}

ValuePtr CFunctionValue::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
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

void CFunctionValue::SetParameters(const FunctionParameters& parameters)
{
    m_parameters = parameters;
}

void CFunctionValue::SetBody(IStatement* body)
{
    m_body = std::move(body);
}
