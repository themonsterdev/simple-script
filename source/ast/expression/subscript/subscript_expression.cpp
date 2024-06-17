/**
 * @file subscript_expression.cpp
 * @brief Implementation of the subscript expression class.
 */

// Include the header file for the FSubscriptExpression class
#include "ast/expression/subscript/subscript_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "value/array_value.hpp"
#include "value/number_value.hpp"

FSubscriptExpression::FSubscriptExpression(ExpressionPtr array, ExpressionPtr index)
    : m_array(std::move(array))
    , m_index(std::move(index))
{}

ValuePtr FSubscriptExpression::Evaluate(const FContext& context) const
{
    const auto& elements_value = m_array->Evaluate(context);
    const auto& element_index  = m_index->Evaluate(context);

    const auto& elements = dynamic_cast<FArrayValue*>(elements_value.get());
    const auto& index = dynamic_cast<FNumberValue*>(element_index.get());

    if (elements && index)
    {
        return elements->GetElement(index->GetValue());
    }

    return {};
}
