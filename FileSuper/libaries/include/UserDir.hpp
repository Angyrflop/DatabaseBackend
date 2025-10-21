//Copyright(c) Goes to Jan Oliver Quant
#pragma once
#include <string>

struct UserDir
{
public:
	std::string Owner;
	std::string RequiredHash;

	UserDir(const std::string& sOwner = "", const std::string& sRequiredHash = "");
};