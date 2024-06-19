#pragma once

#include "interface/compiler.hpp"

class FCompilerASM final : public ICompiler
{
public:

    void Compile(StatementList statements, const std::string& filename) override;
    
};
