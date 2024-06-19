/**
 * @file compiler.hpp
 * @brief Declaration of the FCompiler class.
 */

// Ensure this file is included only once
#pragma once

#include <vector>
#include <string>

/**
 * @brief Represents the compiler class.
 */
class FCompiler final
{
	int m_argc;				// The number of command line arguments.
	const char** m_argv;    // The array of command line argument strings.

public:

	/**
	 * @brief Constructor for FInterpreter.
	 * @param argc The number of command line arguments.
	 * @param argv The array of command line argument strings.
	 */
	FCompiler(const int argc, const char* argv[]);
	
	/**
	 * @brief Compile the input.
	 */
	void Compile();

private:

	/**
	 * @brief Print the usage information.
	 */
	void PrintUsage() const;

	/**
	 * @brief Compile a file.
	 * @param filename The name of the file to compile.
	 */
	void CompileFile(const std::string& filename);

	/**
	 * @brief Compile text input.
	 * @param input The text input to compile.
	 */
	void CompileText(const std::string& input);
};
