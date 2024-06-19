#pragma once

#include <string>
#include <vector>
#include <memory>

class IValue;
class FContext;

using ValuePtr = std::shared_ptr<IValue>;

class IValue
{
public:

    virtual ~IValue() = default;
    virtual const std::string ToString() const = 0;
    virtual ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const = 0;

    virtual bool IsBoolean()  const = 0;
    virtual bool IsNumber()   const = 0;
    virtual bool IsString()   const = 0;
    virtual bool IsArray()    const = 0;
    virtual bool IsObject()   const = 0;
    virtual bool IsClass()    const = 0;
    virtual bool IsFunction() const = 0;
};
