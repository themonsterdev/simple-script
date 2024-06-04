#include "builtin_function/builtin_file_functions.hpp"

FBuiltinOpenFile::FBuiltinOpenFile(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinOpenFile::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    if (arguments.size() != 2)
    {
        throw std::runtime_error("open function requires exactly 2 arguments");
    }

    return {};
}

FBuiltinReadFile::FBuiltinReadFile(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinReadFile::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    if (arguments.size() != 1)
    {
        throw std::runtime_error("read function requires exactly 1 argument");
    }

    return {};
}

FBuiltinWriteFile::FBuiltinWriteFile(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinWriteFile::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    if (arguments.size() != 2)
    {
        throw std::runtime_error("write function expects two arguments");
    }

    return {};
}

FBuiltinCloseFile::FBuiltinCloseFile(std::string name, FunctionParameters parameters)
    : FInvokableFunction(name, parameters, nullptr)
{}

Value FBuiltinCloseFile::Invoke(const std::vector<Value>& arguments, const FContext& context) const
{
    if (arguments.size() != 1)
    {
        throw std::runtime_error("close function requires exactly 1 argument");
    }

    return {};
}

std::shared_ptr<FInvokableFunction> CreateOpenFileFunction()
{
    FunctionParameters parameters = { "string", "string" };
    return std::make_shared<FBuiltinOpenFile>("open", parameters);
}

std::shared_ptr<FInvokableFunction> CreateReadFileFunction()
{
    FunctionParameters parameters = { "string" };
    return std::make_shared<FBuiltinReadFile>("read", parameters);
}

std::shared_ptr<FInvokableFunction> CreateWriteFileFunction()
{
    FunctionParameters parameters = { "string", "string" };
    return std::make_shared<FBuiltinReadFile>("write", parameters);
}

std::shared_ptr<FInvokableFunction> CreateCloseFileFunction()
{
    FunctionParameters parameters = { "string" };
    return std::make_shared<FBuiltinCloseFile>("close", parameters);
}
