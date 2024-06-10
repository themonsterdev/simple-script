/**
 * @file compound_assignment_expression.cpp
 * @brief Implementation of the compound assignment expression class.
 */

// Include the header file for the FCompoundAssignmentExpression class
#include "expression/assignment/compound_assignment_expression.hpp"
#include "expression/identifier_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

#include "number_value.hpp"
#include "string_value.hpp"
#include <stdexcept>

FCompoundAssignmentExpression::FCompoundAssignmentExpression(
    const std::string& assignment,
    ExpressionPtr identifier,
    ExpressionPtr expression)
    : m_assignment(assignment)
    , m_identifier(std::move(identifier))
    , m_expression(std::move(expression))
{}

ValuePtr FCompoundAssignmentExpression::Evaluate(const FContext& context) const
{
    const auto& identifier = dynamic_cast<FIdentifierExpression*>(m_identifier.get());

    if (!identifier)
    {
        throw std::runtime_error("Invalid identifier expression");
    }

    const auto& identifierValue = m_identifier->Evaluate(context);
    const auto& expressionValue = m_expression->Evaluate(context);

    if (!identifierValue || !expressionValue)
    {
        throw std::runtime_error("Failed to evaluate expression");
    }

    if (identifierValue->IsNumber() && expressionValue->IsNumber())
    {
        const auto& currentIdentifierValue = std::dynamic_pointer_cast<FNumberValue>(identifierValue);
        const auto& currentExpressionValue = std::dynamic_pointer_cast<FNumberValue>(expressionValue);

        const auto& left = currentIdentifierValue->GetValue();
        const auto& right = currentExpressionValue->GetValue();

        if (m_assignment == "+=")
        {
            currentIdentifierValue->SetValue(left + right);
        }
        else if (m_assignment == "-=")
        {
            currentIdentifierValue->SetValue(left - right);
        }
        else if (m_assignment == "*=")
        {
            currentIdentifierValue->SetValue(left * right);
        }
        else if (m_assignment == "/=")
        {
            currentIdentifierValue->SetValue(left / right);
        }
        else if (m_assignment == "%=")
        {
            currentIdentifierValue->SetValue(left % right);
        }
        else if (m_assignment == "<<=")
        {
            currentIdentifierValue->SetValue(left << right);
        }
        else if (m_assignment == ">>=")
        {
            currentIdentifierValue->SetValue(left >> right);
        }
        else if (m_assignment == "&=")
        {
            currentIdentifierValue->SetValue(left & right);
        }
        else if (m_assignment == "^=")
        {
            currentIdentifierValue->SetValue(left ^ right);
        }
        else if (m_assignment == "|=")
        {
            currentIdentifierValue->SetValue(left | right);
        }
        else
        {
            throw std::runtime_error("Invalid compound assignment operator for numeric types");
        }
    }
    else if (identifierValue->IsString() && expressionValue->IsString())
    {
        const auto& currentIdentifierValue = std::dynamic_pointer_cast<FStringValue>(identifierValue);
        const auto& currentExpressionValue = std::dynamic_pointer_cast<FStringValue>(expressionValue);

        const auto& left = currentIdentifierValue->GetValue();
        const auto& right = currentExpressionValue->GetValue();

        if (m_assignment == "+=")
        {
            currentIdentifierValue->SetValue(left + right);
        }
        else
        {
            throw std::runtime_error("Invalid compound assignment operator for string types");
        }
    }
    else
    {
        throw std::runtime_error("Incompatible types for compound assignment");
    }

    return identifierValue;
}
