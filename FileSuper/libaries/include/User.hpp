//Copyright(c) Goes to Jan Oliver Quant
#pragma once
#include <string>
#include <vector>

struct User
{
public:
	std::string Username;
	std::string UserHash;


	User(const std::string& sUsername = "", const std::string& sUserHash = "");
};

extern std::vector<User> vUsers;