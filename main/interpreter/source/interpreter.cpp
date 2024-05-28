#include "interpreter.hpp"

#include "tokenizer.hpp"
#include "parser.hpp"

// Statement
#include "statement/assignment_statement.hpp"
#include "statement/print_statement.hpp"
#include "statement/var_declaration_statement.hpp"

// Expression
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"

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
    FContext context{};

    try {
        StatementList statements = parser.Parse();

        for (const auto& statement : statements)
        {
            statement->Execute(context);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
