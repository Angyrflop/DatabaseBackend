//Copyright(c) Goes to Jan Oliver Quant
#include <UserDir.hpp>

/*
	Constructor
	Lets us create users without hard coding
*/

UserDir::UserDir(const std::string& sOwner, const std::string& sRequiredHash)
	:	Owner(sOwner), RequiredHash(sRequiredHash)
{}