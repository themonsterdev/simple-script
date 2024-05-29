/**
 * @file interpreter.cpp
 * @brief Implementation of the interpreter class methods.
 */

#include "interpreter.hpp"  // Include the header file for the interpreter class
#include "lexer.hpp"        // Include the header file for the lexer class
#include "parser.hpp"       // Include the header file for the parser class

#include <iostream>         // Include the standard input/output stream library
#include <fstream>          // Include the file stream library

FInterpreter::FInterpreter(const int argc, const char* argv[], const KeywordVector& keywords)
    // Initialize the member variable 'm_argc' with the provided 'argc'
    : m_argc(argc)
    // Initialize the member variable 'm_argv' with the provided 'argv'
    , m_argv(argv)
    // Initialize the member variable 'm_keywords' with the provided 'keywords'
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
    // Check if the number of command-line arguments is not equal to 3
    if (m_argc != 3)
    {
        // Call the function to print usage instructions
        PrintUsage();

        // Exit the function
        return;
    }

    // Get the first command-line argument
    std::string arg = m_argv[1];

    // Check if the argument is for showing help message
    if (arg == "-h" || arg == "--help")
    {
        // Call the function to print usage instructions
        PrintUsage();
    }
    // Check if the argument is for interpreting script text
    else if (arg == "-t" || arg == "--text")
    {
        // Check if the number of command-line arguments is not equal to 3
        if (m_argc != 3)
        {
            // Call the function to print usage instructions
            PrintUsage();

            // Throw an error for invalid number of arguments
            throw std::runtime_error("Invalid number of arguments for --text option.");
        }

        // Get the script text from command-line arguments
        std::string scriptText = m_argv[2];

        // Call the function to interpret script text
        InterpretText(scriptText);
    }
    // Check if the argument is for interpreting script file
    else if (arg == "-f" || arg == "--file")
    {
        // Check if the number of command-line arguments is not equal to 3
        if (m_argc != 3)
        {
            // Call the function to print usage instructions
            PrintUsage();

            // Throw an error for invalid number of arguments
            throw std::runtime_error("Invalid number of arguments for --file option.");
        }

        // Get the script filename from command-line arguments
        std::string scriptFilename = m_argv[2];

        // Call the function to interpret script file
        InterpretFile(scriptFilename);
    }
    else // If the argument is not recognized
    {
        // Call the function to print usage instructions
        PrintUsage();
    }
}

void FInterpreter::InterpretFile(const std::string& filename)
{
    // Open the script file
    std::ifstream file(filename);

    // Check if the file is not opened successfully
    if (!file.is_open())
    {
        // Throw an error for failed to open file
        throw std::runtime_error("Error: Failed to open script file.");
    }

    // Read script content from file
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    // Close the file
    file.close();

    // Call the function to interpret script content
    InterpretText(input);
}

void FInterpreter::InterpretText(const std::string& input)
{
    // Create a lexer object with the script input
    FLexer lexer(input);

    // Create a parser object with the lexer
    FParser parser(lexer);

    // Create a context object for variable management
    FContext context{};

    try {
        // Parse the script input and get the list of statements
        StatementList statements = parser.Parse();

        // Iterate through each statement in the list
        for (const auto& statement : statements)
        {
            // Execute the statement with the context
            statement->Execute(context);
        }
    }
    // Catch any exceptions thrown during parsing or execution
    catch (const std::exception& e)
    {
        // Print the error message
        std::cerr << e.what() << std::endl;
    }
}
