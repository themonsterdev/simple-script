#pragma once

#include "ast/syntax_node.hpp"

template<typename TValue>
class ASyntaxLeaf
{
protected:

    TValue m_value;

public:

    virtual ~ASyntaxLeaf() = default;

    virtual eSyntaxNodeType GetType() const = 0;

    virtual Value Evaluate(const FContext& context) const
    {
        return m_value;
    }

    const TValue GetValue() const
    {
        return m_value;
    }

    void SetValue(TValue& value)
    {
        m_value = value;
    }
};
