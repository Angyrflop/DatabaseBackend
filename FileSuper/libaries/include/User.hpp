#pragma once
#include <string>

struct User
{
public:
	std::string Username;
	std::string UserHash;
	bool IsVerified;

	User(const std::string& sUsername = "", const std::string& sUserHash = "", bool bVerified = false);
};