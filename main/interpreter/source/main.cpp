/**
 * @file main.cpp
 * @brief Entry point of the interpreter program.
 */

// Include the standard input/output stream library
#include <iostream>

// Include the header file for the interpreter class
#include "interpreter.hpp"

int main(const int argc, const char* argv[])
{
	// Define keywords for the interpreter
	KeywordVector keywords = { "var", "print" };

	// Create an interpreter object with command-line arguments and keywords
	FInterpreter interpreter(argc, argv, keywords);

	try {
		// Call the function to interpret the input
		interpreter.Interpret();
	}
	catch (const std::exception& e)
	{
		// Print error message if an exception occurs
		std::cerr << e.what() << std::endl;

		// Return failure status
		return EXIT_FAILURE;
	}

	// Return success status
	return EXIT_SUCCESS;
}
