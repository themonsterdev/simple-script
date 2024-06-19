#pragma once

#include "value/function_value.hpp"
#include <fstream>

class FBuiltinOpenFile final : public CFunctionValue
{
public:

    FBuiltinOpenFile(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

class FBuiltinReadFile final : public CFunctionValue
{
public:

    FBuiltinReadFile(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

class FBuiltinWriteFile final : public CFunctionValue
{
public:

    FBuiltinWriteFile(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

class FBuiltinCloseFile final : public CFunctionValue
{
public:

    FBuiltinCloseFile(FunctionDefinitionPtr functionDefinition);

    ValuePtr CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const override;
};

FunctionValuePtr CreateOpenFileFunction();
FunctionValuePtr CreateReadFileFunction();
FunctionValuePtr CreateWriteFileFunction();
FunctionValuePtr CreateCloseFileFunction();
