#pragma once

#include "interface/compiler.hpp"

#include <sstream>
#include <unordered_map>
#include <variant>

using VarValue = std::variant<int, std::string>;

struct SInstruction
{
    std::string opcode;
    std::vector<VarValue> operands;
};

class FCompilerASM final : public ICompiler
{
    std::vector<SInstruction> instructions;
    std::unordered_map<std::string, VarValue> variables;
    std::unordered_map<std::string, size_t> buffers;
    
public:

    void Compile(StatementList statements, const std::string& filename) override;
    
private:

    void AddVariable(const std::string& varName, VarValue value = 0);
    void AddInstruction(const std::string& opcode, const std::vector<VarValue>& operands);
    void GenerateAssembly(const std::string& filename);
};
