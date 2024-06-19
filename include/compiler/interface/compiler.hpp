#pragma once

#include <string>

#include "ast/statement/interface/statement.hpp"

class ICompiler
{
public:

    virtual ~ICompiler() {}

    virtual void Compile(StatementList statements, const std::string& filename) = 0;
};
