#pragma once

#include "interface/value.hpp"

class AValue : public IValue
{
public:

    // Override these methods in derived classes if needed
    virtual bool IsBoolean() const override { return false; }
    virtual bool IsNumber() const override { return false; }
    virtual bool IsString() const override { return false; }
    virtual bool IsObject() const override { return false; }
    virtual bool IsFunction() const override { return false; }
    // Add more type checks as needed
};
