/**
 * @file interpreter.hpp
 * @brief Declaration of the FInterpreter class.
 */

// Ensure this file is included only once
#pragma once

#include <vector>
#include <string>

/**
 * @brief Represents a vector of keywords.
 */
using KeywordVector = std::vector<std::string>;

/**
 * @brief Represents the interpreter class.
 */
class FInterpreter final
{
	int m_argc;					// The number of command line arguments.
	const char** m_argv;		// The array of command line argument strings.
	KeywordVector m_keywords;	// Vector of keywords.

public:

	/**
	 * @brief Constructor for FInterpreter.
	 * @param argc The number of command line arguments.
	 * @param argv The array of command line argument strings.
	 * @param keywords Vector of keywords.
	 */
	FInterpreter(const int argc, const char* argv[], const KeywordVector& keywords);
	
	/**
	 * @brief Interpret the input.
	 */
	void Interpret();

private:

	/**
	 * @brief Print the usage information.
	 */
	void PrintUsage() const;

	/**
	 * @brief Interpret a file.
	 * @param filename The name of the file to interpret.
	 */
	void InterpretFile(const std::string& filename);

	/**
	 * @brief Interpret text input.
	 * @param input The text input to interpret.
	 */
	void InterpretText(const std::string& input);
};
