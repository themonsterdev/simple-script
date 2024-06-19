#include "ast/expression/access/access_expression.hpp"

#include "context/context.hpp"

#include "value/object_value.hpp"
#include "value/class_value.hpp"

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
    // Handle member access based on the operator
    if (m_op == ".")
    {
        // Evaluate the expression to get the value
        ValuePtr value = m_expression->Evaluate(context);

        if (value->IsClass())
        {
            const auto& object = std::dynamic_pointer_cast<FClassValue>(value);

            if (object->HasMember(m_memberName))
            {
                return object->GetMember(m_memberName);
            }

            const auto& parentName = object->GetParent();

            if (!parentName.empty())
            {
                const auto& parentSymbol = context.GetSymbol(parentName);
                const auto& parentValue = std::dynamic_pointer_cast<FClassValue>(parentSymbol);
                
                if (parentValue->HasMember(m_memberName))
                {
                    return parentValue->GetMember(m_memberName);
                }
            }
        }

        throw std::runtime_error("Member '" + m_memberName + "' not found in class");
    }
    
    throw std::runtime_error("Unsupported access operator: " + m_op);
}
