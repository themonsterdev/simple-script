#include "object_value.hpp"
#include "function_value.hpp"
#include "context.hpp"
#include <stdexcept>

SMember::SMember(AccessSpecifier accessSpecifier, ValuePtr val)
    : access(accessSpecifier)
    , value(std::move(val))
{}

FObjectValue::FObjectValue(
    const std::string& className,
    ObjectValuePtr parentClass)
    : m_name(className)
    , m_parentClass(parentClass)
{}

bool FObjectValue::IsObject() const
{
    return true;
}

const std::string FObjectValue::ToString() const
{
    return m_name;
}

const std::string& FObjectValue::GetName() const
{
    return m_name;
}

void FObjectValue::AddMethod(const std::string& name, AccessSpecifier access, FunctionValuePtr value)
{
    m_methods[name] = SMember(access, std::move(value));
}

void FObjectValue::AddProperty(const std::string& name, AccessSpecifier access, ValuePtr value)
{
    m_properties[name] = SMember(access, std::move(value));
}

bool FObjectValue::HasMethod(const std::string& name) const
{
    const FObjectValue* current = this;

    while (current)
    {
        if (current->m_methods.find(name) != current->m_methods.end())
        {
            return true;
        }

        current = current->m_parentClass.get();
    }
    return false;
}

bool FObjectValue::HasProperty(const std::string& name) const
{
    const FObjectValue* current = this;

    while (current)
    {
        if (current->m_properties.find(name) != current->m_properties.end())
        {
            return true;
        }

        current = current->m_parentClass.get();
    }
    return false;
}

FunctionValuePtr FObjectValue::GetMethod(const std::string& name, const FContext& context) const
{
    const FObjectValue* current = this;

    while (current)
    {
        auto it = current->m_methods.find(name);

        if (it != current->m_methods.end())
        {
            if (!IsAccessible(it->second.access, context))
            {
                throw std::runtime_error("Method not access: " + name);
            }

            return std::static_pointer_cast<CFunctionValue>(it->second.value);
        }

        current = current->m_parentClass.get();
    }

    throw std::runtime_error("Method not found: " + name);
}

ValuePtr FObjectValue::GetProperty(const std::string& name, const FContext& context) const
{
    const FObjectValue* current = this;

    while (current)
    {
        auto it = current->m_properties.find(name);

        if (it != current->m_properties.end())
        {
            if (!IsAccessible(it->second.access, context))
            {
                throw std::runtime_error("Propety not access: " + name);
            }

            return it->second.value;
        }

        current = current->m_parentClass.get();
    }
    
    throw std::runtime_error("Property not found: " + name);
}

ValuePtr FObjectValue::CallMethod(const std::string& name, const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    const auto& method = GetMethod(name, context);
    return method->Invoke(arguments, context);
}

bool FObjectValue::IsAccessible(AccessSpecifier access, const FContext& context) const
{
    // Implement the logic to check if the current context allows access
    // For example, check if the context is within the same class, a derived class, etc.
    // For simplicity, let's assume public members are always accessible
    switch (access)
    {
    case AccessSpecifier::Public:
        return true;
    case AccessSpecifier::Protected:
        // Add logic to check if the context is a derived class
        return false;
    case AccessSpecifier::Private:
        // Add logic to check if the context is the same class
        return false;
    }

    return false;
}

bool FObjectValue::IsDerivedFromClass(const FObjectValue* object) const
{
    const FObjectValue* current = this;
    while (current)
    {
        if (current->IsSameClass(object))
        {
            return true;
        }
        current = current->GetParentClass().get();
    }
    return false;
}

bool FObjectValue::IsSameClass(const FObjectValue* object) const
{
    return m_name == object->m_name;
}

ObjectValuePtr FObjectValue::GetParentClass() const
{
    return m_parentClass;
}

AccessSpecifier FObjectValue::GetMethodAccessSpecifier(const std::string& name) const
{
    const FObjectValue* current = this;

    while (current)
    {
        auto it = current->m_methods.find(name);
        if (it != current->m_methods.end())
        {
            return it->second.access;
        }
        current = current->m_parentClass.get();
    }

    throw std::runtime_error("Property not found: " + name);
}
