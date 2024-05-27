#pragma once

#include <vector>
#include <string>

class FInterpreter final
{
	int m_argc;
	const char** m_argv;
	std::vector<std::string> m_keywords;

public:

	FInterpreter(const int argc, const char* argv[], const std::vector<std::string>& keywords);
	void Interpret();

private:

	void PrintUsage() const;
	void InterpretFile(const std::string& filename);
	void InterpretText(const std::string& input);
};
