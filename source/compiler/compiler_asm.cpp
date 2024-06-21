#include "compiler/compiler_asm.hpp"

#include "ast/statement/variable/variable_declaration_statement.hpp"
#include "ast/statement/expression/expression_statement.hpp"

#include "ast/expression/invokable/call_expression.hpp"
#include "ast/expression/literal/number_expression.hpp"
#include "ast/expression/literal/string_expression.hpp"
#include "ast/expression/identifier_expression.hpp"

#include <iostream>
#include <fstream>

void FCompilerASM::Compile(StatementList statements, const std::string& filename)
{
    for (const auto& statement : statements)
    {
        if (const auto& variable = dynamic_cast<FVariableDeclarationStatement*>(statement.get()))
        {
            const auto& identifierName = variable->GetIdentifier();

            const auto& expression = variable->GetExpression();
            if (const auto& numberExpression = dynamic_cast<FNumberExpression*>(expression.get()))
            {
                AddVariable(identifierName, numberExpression->GetValue());
            }
            else if (const auto& stringExpression = dynamic_cast<FStringExpression*>(expression.get()))
            {
                AddVariable(identifierName, stringExpression->GetValue());
            }
            else
            {
                // error not implemented
            }
        }
        else if (const auto& statementExpr = dynamic_cast<FExpressionStatement*>(statement.get()))
        {
            const auto& expression = statementExpr->GetExpression();
            const auto& callExpression = dynamic_cast<FCallExpression*>(expression.get());

            const auto& callable = dynamic_cast<FIdentifierExpression*>(callExpression->GetIdentifier().get());
            const auto& callableName = callable->GetName();

            if (callableName == "print")
            {
                const auto& arguments = callExpression->GetArguments();
                const auto& argument = arguments[0];

                if (const auto& numberExpression = dynamic_cast<FNumberExpression*>(argument.get()))
                {
                    std::cout << "number expression" << std::endl;
                }
                else if (const auto& stringExpression = dynamic_cast<FStringExpression*>(argument.get()))
                {
                    std::cout << "string expression" << std::endl;
                }
                else if (const auto& identifierExpression = dynamic_cast<FIdentifierExpression*>(argument.get()))
                {
                    const auto& identifierName = identifierExpression->GetName();
                    const auto& identifierValue = variables[identifierName];

                    if (std::holds_alternative<int>(identifierValue))
                    {
                        int value = std::get<int>(identifierValue);

                        size_t size = std::to_string(value).length();
                        buffers[identifierName] = size;
                        
                        std::string idBuffer("buffer_");
                        idBuffer += identifierName;

                        std::string bufferSize(idBuffer);
                        bufferSize += " + ";
                        bufferSize += std::to_string(size);

                        std::string bufferRel("[rel buffer_");
                        bufferRel += identifierName;
                        bufferRel += "]";

                        // Initialize buffer
                        AddInstruction("mov", {"rax", identifierName});
                        AddInstruction("mov", {"rax", "[rax]"});
                        AddInstruction("mov", {"rdi", bufferSize});
                        AddInstruction("mov", {"byte [rdi]", "0xA"});

                        AddInstruction("convert_digit:", {});
                        AddInstruction("dec", {"rdi"});
                        AddInstruction("xor", {"rdx", "rdx"});
                        AddInstruction("mov", {"rcx", "10"});
                        AddInstruction("div", {"rcx"});
                        AddInstruction("add", {"dl", "'0'"});
                        AddInstruction("mov", {"[rdi]", "dl"});
                        AddInstruction("test", {"rax", "rax"});
                        AddInstruction("jnz", {"convert_digit"});

                        AddInstruction("mov", {"rdx", std::to_string(size+1)});
                        AddInstruction("sub", {"rdx", "rdi"});

                        AddInstruction("mov", {"rax", "0x2000004"});
                        AddInstruction("mov", {"rdi", "1"});
                        AddInstruction("lea", {"rsi", bufferRel});
                        AddInstruction("mov", {"rdx", std::to_string(size+1)});
                        AddInstruction("syscall", {});
                    }
                    else if (std::holds_alternative<std::string>(identifierValue))
                    {
                        std::string value = std::get<std::string>(identifierValue);

                        size_t size = value.length();

                        AddInstruction("mov", {"rax", "0x2000004"});
                        AddInstruction("mov", {"rdi", "1"});
                        AddInstruction("mov", {"rsi", identifierName});
                        AddInstruction("mov", {"rdx", std::to_string(size+1)});
                        AddInstruction("syscall", {});
                    }
                    else
                    {
                        // throw error not implemented
                    }
                }
                else
                {
                    // throw error not implemented
                }
            }
        }
        else
        {
            // throw error not implemented
        }
    }

    GenerateAssembly(filename);
}

void FCompilerASM::AddVariable(const std::string& varName, VarValue value)
{
    variables[varName] = value;
}

void FCompilerASM::AddInstruction(const std::string& opcode, const std::vector<VarValue>& operands)
{
    SInstruction ins;
    ins.opcode = opcode;
    ins.operands = operands;
    instructions.push_back(ins);
}

void FCompilerASM::GenerateAssembly(const std::string& filename)
{
    std::ofstream outfile(filename);

    if (!outfile.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    {
        outfile << "bits 64" << std::endl;
        outfile << std::endl;
    }

    {
        outfile << "section .data" << std::endl;
        for (const auto& var : variables)
        {
            if (std::holds_alternative<int>(var.second))
            {
                int value = std::get<int>(var.second);
                outfile << "    " << var.first << " dq " << value << std::endl;
            }
            else if (std::holds_alternative<std::string>(var.second))
            {
                std::string value = std::get<std::string>(var.second);
                outfile << "    " << var.first << " db \"" << value << "\", 0xA" << std::endl;
            }
        }
        outfile << std::endl;
    }

    {
        std::string bss;

        for (const auto& buffer : buffers)
        {
            bss += "    ";
            bss += "buffer_";
            bss += buffer.first;
            bss += " resb ";
            bss += std::to_string(buffer.second);
            bss += "\n";
        }

        if (!bss.empty())
        {
            outfile << "section .bss" << std::endl;
            outfile << bss;
            outfile << std::endl;
        }
    }

    {
        outfile << "section .text" << std::endl;
        outfile << "    global start" << std::endl;
        outfile << std::endl;
    }
    outfile << "start:" << std::endl;
    outfile << std::endl;

    for (const auto& ins : instructions)
    {
        if (!ins.opcode.empty() && ins.opcode.back() == ':')
        {
            outfile << ins.opcode << std::endl;
        }
        else
        {
            outfile << "    " << ins.opcode << " ";
            for (size_t i = 0; i < ins.operands.size(); ++i)
            {
                if (i > 0)
                    outfile << ", ";

                if (std::holds_alternative<int>(ins.operands[i]))
                {
                    int value = std::get<int>(ins.operands[i]);
                    outfile << value;
                }
                else if (std::holds_alternative<std::string>(ins.operands[i]))
                {
                    std::string value = std::get<std::string>(ins.operands[i]);
                    outfile << value;
                }
            }
            outfile << std::endl;
        }
    }

    outfile << "    mov rax, 0x2000001" << std::endl;
    outfile << "    xor rdi, rdi" << std::endl;
    outfile << "    syscall" << std::endl;

    outfile.close();
}
