#include "expression/access/access_expression.hpp"
#include "expression/identifier_expression.hpp"

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
    // context.SetObjectValue(object);

    // Handle member access based on the operator
    if (m_op == ".")
    {
        return EvaluateDotOperator(object, context);
    }
    else
    {
        throw std::runtime_error("Unsupported access operator: " + m_op);
    }

    // This line should never be reached
    return {};
}

ValuePtr FAccessExpression::EvaluateDotOperator(const ObjectValuePtr& object, const FContext& context) const
{
    // Accessing a property or method in the current object
    if (object->HasProperty(m_memberName))
    {
        return object->GetProperty(m_memberName, context);
    }

    throw std::runtime_error("Property '" + m_memberName + "' not found in object");
}

ValuePtr FAccessExpression::CallObjectMethod(const ObjectValuePtr& object, const FContext& context) const
{
    if (!context.IsVariableDeclared("self"))
        context.DeclareVariable("self");
    context.AssignVariable("self", object);

    std::vector<ValuePtr> parameters;
    // auto objectValue = std::make_shared<FObjectValue>("test");
    // parameters.push_back(objectValue);

    const auto& value = object->CallMethod(m_memberName, parameters, context);

    return value;
}
