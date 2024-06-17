#include "value/array_value.hpp"

FArrayValue::FArrayValue(ArrayElementVector elements)
    : m_elements(elements)
{}

bool FArrayValue::IsArray() const
{
    return true;
}

const std::string FArrayValue::ToString() const
{
    std::string expression("[\n");

    for (size_t i = 0; i < m_elements.size(); i++)
    {
        if (i > 0)
        {
            expression += ", ";
            expression += '\n';
        }

        expression += "    ";
        expression += m_elements[i]->ToString();
    }

    expression += "\n]";

    return expression;
}

const ArrayElementVector& FArrayValue::GetElements() const
{
    return m_elements;
}

const ValuePtr& FArrayValue::GetElement(uint32_t index) const
{
    if (m_elements.size() <= index)
    {
        throw std::runtime_error("Failed to index for the array elements");
    }

    return m_elements[index];
}
