//Copyright(c) Goes to Jan Oliver Quant
#include "User.hpp"
#include <vector>

/*
	Constructor
	Lets us create users without hard coding
*/
User::User(const std::string& sUsername, const std::string& sUserHash)
	: Username(sUsername), UserHash(sUserHash)
{}
std::vector<User> vUsers;