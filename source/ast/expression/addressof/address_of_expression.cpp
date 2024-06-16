/**
 * @file address_of_expression.cpp
 * @brief Implementation of the address of expression class.
 */

// Include the header file for the FAddressOfExpression class
#include "ast/expression/addressof/address_of_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FAddressOfExpression::FAddressOfExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FAddressOfExpression::Evaluate(const FContext& context) const
{
    return {};
}
