/**
 * @file call_expression.cpp
 * @brief Implementation of the call expression class.
 */

// Include the expression interface
#include "expression/invokable/call_expression.hpp"
#include "expression/identifier_expression.hpp"
#include "context.hpp"

FCallExpression::FCallExpression(ExpressionPtr identifier, std::vector<ExpressionPtr> arguments)
	: m_identifier(std::move(identifier))
	, m_arguments(std::move(arguments))
{}

ValuePtr FCallExpression::Evaluate(const FContext& context) const
{
    const auto& identifier = dynamic_cast<FIdentifierExpression*>(m_identifier.get());

    std::vector<ValuePtr> arguments;
    for (const auto& argument : m_arguments)
    {
        arguments.push_back(argument->Evaluate(context));
    }

    return context.CallFunction(identifier->GetName(), arguments);
}
