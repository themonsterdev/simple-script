#include "expression/access/access_expression.hpp"

#include "context.hpp"
#include "object_value.hpp"

#include <stdexcept>

FAccessExpression::FAccessExpression(
    ExpressionPtr expression,
    std::string op,
    std::string memberName
)
    : m_expression(std::move(expression))
    , m_op(op)
    , m_memberName(memberName)
{}

ValuePtr FAccessExpression::Evaluate(const FContext& context) const
{
    // Evaluate the expression to get the object
    ValuePtr objectValue = m_expression->Evaluate(context);

    // Check if the value is an object that supports member access
    if (!objectValue->IsObject())
    {
        throw std::runtime_error("Expression does not evaluate to an object");
    }

    auto object = std::dynamic_pointer_cast<FObjectValue>(objectValue);

    // Handle member access based on the operator
    if (m_op == ".")
    {
        return EvaluateDotOperator(object, context);
    }
    else
    {
        throw std::runtime_error("Unsupported access operator: " + m_op);
    }

    return {};
}

ValuePtr FAccessExpression::EvaluateDotOperator(const ObjectValuePtr& object, const FContext& context) const
{
    // Accessing a property in the current object
    if (context.IsVariableDeclared(m_memberName))
    {
        return context.GetVariable(m_memberName);
    }

    throw std::runtime_error("Property '" + m_memberName + "' not found in object");
}
