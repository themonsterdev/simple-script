#include "ast/expression/access/access_method_expression.hpp"
#include "ast/expression/identifier_expression.hpp"

#include "context/context.hpp"
#include "value/object_value.hpp"
#include "value/string_value.hpp"
#include "value/class_value.hpp"

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
    std::vector<ValuePtr> arguments;
    for (const auto& argument : m_arguments)
    {
        arguments.push_back(argument->Evaluate(context));
    }

    // Evaluate the expression to get the value
    ValuePtr value = m_expression->Evaluate(context);

    if (value->IsClass())
    {
        const auto& currentClass = context.GetCurrentClass();
        context.SetCurrentClass(value);

        if (!context.IsSymbolDeclared("self"))
            context.DeclareSymbol("self");
        context.AssignSymbol("self", value);

        const auto& object = std::dynamic_pointer_cast<FClassValue>(value);

        if (object->HasMember(m_memberName))
        {
            const auto& method = object->GetMember(m_memberName);
            const auto& returnValue = method->CallMethod(context, m_memberName, arguments);

            context.SetCurrentClass(currentClass);
            return returnValue;
        }
    }

    return value->CallMethod(context, m_memberName, arguments);
}

void FAccessMethodExpression::SetArguments(ExpressionList arguments)
{
    m_arguments = std::move(arguments);
}
