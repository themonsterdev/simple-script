#include "compiler/compiler_machine.hpp"
#include <fstream>

void FCompilerMachine::Compile(StatementList statements, const std::string& filename)
{
    std::ofstream machineCodeFile(filename);
    
    // Hypothetical machine code generation
    machineCodeFile << "B8 00 00 00 00   ; mov eax, 0\n";
    machineCodeFile << "A3 00 00 00 00   ; mov [identifier], eax\n";
    machineCodeFile << "E8 00 00 00 00   ; call printf\n";
    
    machineCodeFile.close();
}
