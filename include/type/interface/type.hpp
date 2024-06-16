#pragma once

enum class eTypeKind
{
    ANY,
    VOID,
    NUMBER,
    STRING,
    BOOLEAN,
    FUNCTION,
    CLASS,
};

class IType
{
    eTypeKind m_kind;

public:

    virtual ~IType() = default;

    IType(eTypeKind kind)
        : m_kind(kind)
    {}

    virtual void* getDefaultValue() const = 0;

    virtual bool isEqual(const IType* other) const
    {
        return m_kind == other->m_kind;
    }
};
