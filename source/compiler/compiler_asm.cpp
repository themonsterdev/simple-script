#include "compiler/compiler_asm.hpp"
#include <fstream>

void FCompilerASM::Compile(StatementList statements, const std::string& filename)
{
    std::ofstream asmFile(filename);
    
    asmFile << "section .data\n";
    asmFile << "    identifier dd 0\n";
    asmFile << "    format db \"%d\", 10, 0\n";
    asmFile << "\n";
    asmFile << "section .text\n";
    asmFile << "    global _start\n";
    asmFile << "_start:\n";
    asmFile << "    mov eax, [identifier]\n";
    asmFile << "    push eax\n";
    asmFile << "    push format\n";
    asmFile << "    call printf\n";
    asmFile << "    add esp, 8\n";
    asmFile << "    call exit\n";
    
    asmFile.close();
}
