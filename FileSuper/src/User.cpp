#include "User.hpp"

/*
	Constructor
	Lets us create users without hard coding
*/
User::User(const std::string& sUsername, const std::string& sUserHash, bool bVerified)
	: Username(sUsername), UserHash(sUserHash), IsVerified(bVerified)
{}