#pragma once

#include "abstract/value.hpp"
#include "function_value.hpp"
#include <unordered_map>

class FContext;

enum class AccessSpecifier
{
    Private,
    Protected,
    Public
};

struct SMember
{
    AccessSpecifier access;
    ValuePtr value; // This could be a property value or a method

    SMember() = default;
    SMember(AccessSpecifier accessSpecifier, ValuePtr val);
};

class FObjectValue;

using PropertyMap    = std::unordered_map<std::string, SMember>;
using MethodMap      = std::unordered_map<std::string, SMember>;
using ObjectValuePtr = std::shared_ptr<FObjectValue>;

class FObjectValue final : public AValue
{
    std::string m_name;
    PropertyMap m_properties;
    MethodMap m_methods;
    ObjectValuePtr m_parentClass;

public:

    FObjectValue(
        const std::string& className,
        ObjectValuePtr parentClass = nullptr
    );

    bool IsObject() const override;
    const std::string ToString() const override;

    const std::string& GetName() const;

    void AddMethod(const std::string& name, AccessSpecifier access, FunctionValuePtr value);
    void AddProperty(const std::string& name, AccessSpecifier access, ValuePtr value);

    bool HasMethod(const std::string& name) const;
    bool HasProperty(const std::string& name) const;

    FunctionValuePtr GetMethod(const std::string& name, const FContext& context) const;
    ValuePtr GetProperty(const std::string& name, const FContext& context) const;

    ValuePtr CallMethod(const std::string& name, const std::vector<ValuePtr>& arguments, const FContext& context) const;

    bool IsAccessible(AccessSpecifier access, const FContext& context) const;
    bool IsDerivedFromClass(const FObjectValue* object) const;
    bool IsSameClass(const FObjectValue* object) const;

    ObjectValuePtr GetParentClass() const;
    AccessSpecifier GetMethodAccessSpecifier(const std::string& name) const;
};
