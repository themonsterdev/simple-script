#pragma once

#include "function_value.hpp"
#include <fstream>

class FBuiltinOpenFile : public CFunctionValue
{
public:

    FBuiltinOpenFile(std::string name, FunctionParameters parameters);
    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

class FBuiltinReadFile : public CFunctionValue
{
public:

    FBuiltinReadFile(std::string name, FunctionParameters parameters);
    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

class FBuiltinWriteFile : public CFunctionValue
{
public:

    FBuiltinWriteFile(std::string name, FunctionParameters parameters);
    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

class FBuiltinCloseFile : public CFunctionValue
{
public:

    FBuiltinCloseFile(std::string name, FunctionParameters parameters);
    ValuePtr Invoke(const std::vector<ValuePtr>& arguments, const FContext& context) const override;
};

FunctionValuePtr CreateOpenFileFunction();
FunctionValuePtr CreateReadFileFunction();
FunctionValuePtr CreateWriteFileFunction();
FunctionValuePtr CreateCloseFileFunction();
