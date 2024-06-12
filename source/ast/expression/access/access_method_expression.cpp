#include "ast/expression/access/access_method_expression.hpp"
#include "ast/expression/identifier_expression.hpp"

#include "context/context.hpp"
#include "value/object_value.hpp"

#include <stdexcept>

FAccessMethodExpression::FAccessMethodExpression(
    ExpressionPtr expression,
    std::string op,
    std::string memberName
)
    : m_expression(std::move(expression))
    , m_op(op)
    , m_memberName(memberName)
{}

ValuePtr FAccessMethodExpression::Evaluate(const FContext& context) const
{
    // Evaluate the expression to get the object
    ValuePtr objectValue = m_expression->Evaluate(context);

    // Check if the value is an object that supports member access
    if (objectValue->IsObject())
    {
        auto object = std::dynamic_pointer_cast<FObjectValue>(objectValue);

        // Handle member access based on the operator
        if (m_op == ".")
        {
            // Accessing a method
            if (object->HasMethod(m_memberName))
            {
                if (!context.IsVariableDeclared("self"))
                    context.DeclareVariable("self");
                context.AssignVariable("self", object);

                std::vector<ValuePtr> arguments;
                for (const auto& argument : m_arguments)
                {
                    arguments.push_back(argument->Evaluate(context));
                }

                ValuePtr value = object->CallMethod(m_memberName, arguments, context);

                return value;
            }

            throw std::runtime_error("Method '" + m_memberName + "' not found in object");
        }
        else
        {
            throw std::runtime_error("Unsupported access operator: " + m_op);
        }
    }
    else
    {
        throw std::runtime_error("Expression does not evaluate to an object");
    }

    // This line should never be reached
    return {};
}

void FAccessMethodExpression::SetArguments(ExpressionList arguments)
{
    m_arguments = std::move(arguments);
}
