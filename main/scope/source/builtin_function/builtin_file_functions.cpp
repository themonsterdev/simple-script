#include "builtin_function/builtin_file_functions.hpp"

FBuiltinOpenFile::FBuiltinOpenFile(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinOpenFile::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    if (arguments.size() != 2)
    {
        throw std::runtime_error("open function requires exactly 2 arguments");
    }

    return {};
}

FBuiltinReadFile::FBuiltinReadFile(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinReadFile::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    if (arguments.size() != 1)
    {
        throw std::runtime_error("read function requires exactly 1 argument");
    }

    return {};
}

FBuiltinWriteFile::FBuiltinWriteFile(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinWriteFile::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    if (arguments.size() != 2)
    {
        throw std::runtime_error("write function expects two arguments");
    }

    return {};
}

FBuiltinCloseFile::FBuiltinCloseFile(std::string name, FunctionParameters parameters)
    : CFunctionValue(name)
{}

ValuePtr FBuiltinCloseFile::Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const
{
    if (arguments.size() != 1)
    {
        throw std::runtime_error("close function requires exactly 1 argument");
    }

    return {};
}

FunctionValuePtr CreateOpenFileFunction()
{
    FunctionParameters parameters = { { "string", "string" }, { "string", "string" } };
    return std::make_shared<FBuiltinOpenFile>("open", parameters);
}

FunctionValuePtr CreateReadFileFunction()
{
    FunctionParameters parameters = { { "string", "string" } };
    return std::make_shared<FBuiltinReadFile>("read", parameters);
}

FunctionValuePtr CreateWriteFileFunction()
{
    FunctionParameters parameters = { { "string", "string" }, { "string", "string" } };
    return std::make_shared<FBuiltinReadFile>("write", parameters);
}

FunctionValuePtr CreateCloseFileFunction()
{
    FunctionParameters parameters = { { "string", "string" } };
    return std::make_shared<FBuiltinCloseFile>("close", parameters);
}
