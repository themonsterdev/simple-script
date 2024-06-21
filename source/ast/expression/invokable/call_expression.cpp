/**
 * @file call_expression.cpp
 * @brief Implementation of the call expression class.
 */

// Include the expression interface
#include "ast/expression/invokable/call_expression.hpp"
#include "ast/expression/identifier_expression.hpp"
#include "context/context.hpp"

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
        const auto& value = argument->Evaluate(context);
        arguments.push_back(value);
    }

    return context.Call(identifier->GetName(), arguments);
}

const ExpressionPtr& FCallExpression::GetIdentifier() const
{
    return m_identifier;
}

const std::vector<ExpressionPtr>& FCallExpression::GetArguments() const
{
    return m_arguments;
}
