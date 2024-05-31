/**
 * @file unary_not_expression.cpp
 * @brief Implementation of the unary not expression class.
 */

 // Include the header file for the FUnaryNotExpression class
#include "expression/operator/unary/unary_not_expression.hpp"
#include <stdexcept>

FUnaryNotExpression::FUnaryNotExpression(ExpressionPtr expression)
	: m_expression(std::move(expression))
{}

Value FUnaryNotExpression::Evaluate(const FContext& context) const
{
    // Évaluation de l'expression interne
    Value innerValue = m_expression->Evaluate(context);

    // Vérification si la valeur est integer
    if (!std::holds_alternative<bool>(innerValue)) {
        throw std::runtime_error("Operand of unary negate must be integer");
    }

    // Négation logique de la valeur integer
    bool result = !std::get<bool>(innerValue);

    return result;
}
