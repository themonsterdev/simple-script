#pragma once

#include <string>
#include <memory>

class IValue
{
public:

    virtual ~IValue() = default;
    virtual const std::string ToString() const = 0;

    virtual bool IsBoolean() const = 0;
    virtual bool IsNumber() const = 0;
    virtual bool IsString() const = 0;
    virtual bool IsObject() const = 0;
    virtual bool IsFunction() const = 0;
};

using ValuePtr = std::shared_ptr<IValue>;
