/**
 * @file main.cpp
 * @brief Entry point of the compiler program.
 */

// Include the standard input/output stream library
#include <iostream>

// Include the header file for the compiler class
#include "compiler/compiler.hpp"

int main(const int argc, const char* argv[])
{
	// Create an compiler object with command-line arguments
	FCompiler compiler(argc, argv);

	try {
		// Call the function to compile the input
		compiler.Compile();
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
