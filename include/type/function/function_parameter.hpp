#pragma once

#include <string>
#include <vector>

class FFunctionParameter final
{
public:

    std::string name;
    std::string type;

    FFunctionParameter(const std::string& name, const std::string& type);
};

// using FunctionParameters = std::vector<FFunctionParameter>;
