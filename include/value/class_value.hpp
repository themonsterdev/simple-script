#pragma once

#include "abstract/value.hpp"
#include "type/oop/class_definition.hpp"

class FClassValue final : public AValue
{
    ClassDefinitionPtr m_definition;

public:

    FClassValue(ClassDefinitionPtr definition);

    bool IsClass() const override;
    const std::string ToString() const override;
    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;

    const std::string& GetName() const;

    void SetParent(const std::string& parent);
    const std::string& GetParent() const;

    void AddInterface(const std::string& interface);
    const InterfaceVector& GetInterfaces() const;

    void AddMember(const std::string& name, ValuePtr value);
    ValuePtr GetMember(const std::string& name) const;
    bool HasMember(const std::string& name) const;
};
