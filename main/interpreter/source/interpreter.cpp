#include "interpreter.hpp"

#include "tokenizer.hpp"
#include "parser.hpp"

// Statement
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/binary_operator_node.hpp"
#include "ast/statement/print_statement_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"

#include <iostream>
#include <fstream>

FInterpreter::FInterpreter(const int argc, const char* argv[], const std::vector<std::string>& keywords)
    : m_argc(argc)
    , m_argv(argv)
    , m_keywords(keywords)
{}

void FInterpreter::PrintUsage() const
{
    std::cerr << "Interpreter (Version 1.0.0)" << std::endl;
    std::cerr << "Licensed under the MIT License." << std::endl;
    std::cerr << std::endl;

    std::cerr << "Usage: interpreter [option]" << std::endl;

    std::cerr << "Options:" << std::endl;
    std::cerr << '\t' << "-t, --text <script_text>    Interpret the provided script text directly." << std::endl;
    std::cerr << '\t' << "-f, --file <script_file>    Interpret the script from the provided file." << std::endl;
    std::cerr << '\t' << "-h, --help                  Show this help message." << std::endl;
}

void FInterpreter::Interpret()
{
    if (m_argc != 3)
    {
        PrintUsage();
        return;
    }

    std::string arg = m_argv[1];
    if (arg == "-h" || arg == "--help")
    {
        PrintUsage();
    }
    else if (arg == "-t" || arg == "--text")
    {
        if (m_argc != 3)
        {
            PrintUsage();
            throw std::runtime_error("Invalid number of arguments for --text option.");
        }
        std::string scriptText = m_argv[2];
        InterpretText(scriptText);
    }
    else if (arg == "-f" || arg == "--file")
    {
        if (m_argc != 3)
        {
            PrintUsage();
            throw std::runtime_error("Invalid number of arguments for --file option.");
        }
        std::string scriptFilename = m_argv[2];
        InterpretFile(scriptFilename);
    }
    else
    {
        PrintUsage();
    }
}

void FInterpreter::InterpretFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Failed to open script file.");
    }

    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    InterpretText(input);
}

void FInterpreter::InterpretText(const std::string& input)
{
    FTokenizer tokenizer(input, m_keywords);
    FParser parser(tokenizer);

    try {
        std::unique_ptr<FSyntaxTree> tree = parser.Parse();

        if (tree)
        {
            const ASyntaxNode* root = tree->GetRoot();

            if (root)
            {
                FContext context{};
                root->Evaluate(context);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
