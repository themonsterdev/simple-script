/**
 * @file assignment_expression.cpp
 * @brief Implementation of the assignment expression class.
 */

// Include the header file for the FAssignmentExpression class
#include "ast/expression/assignment/assignment_expression.hpp"
#include "ast/expression/identifier_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"
#include <stdexcept>

FAssignmentExpression::FAssignmentExpression(
    ExpressionPtr left,
    ExpressionPtr right)
    : m_left(std::move(left))
    , m_right(std::move(right))
{}

ValuePtr FAssignmentExpression::Evaluate(const FContext& context) const
{
    const auto& identifier = dynamic_cast<FIdentifierExpression*>(m_left.get());
    
    if (!identifier)
    {
        throw std::runtime_error("Invalid identifier expression");
    }

    const auto& identifierName = identifier->GetName();
    const auto& value = m_right->Evaluate(context);
    context.AssignVariable(identifierName, value);
    return value;
}
