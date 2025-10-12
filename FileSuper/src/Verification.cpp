//Copyright(c) Goes to Jan Oliver Quant
#include "Verification.hpp"
#include <iostream>

bool VerifyUser(const User& UserDetails, const UserDir& UserDirDetails)
{
	bool bVerify{ true };
	if (UserDetails.Username != UserDirDetails.Owner)
	{
		std::cerr << UserDetails.Username << "Doesnt match " << UserDirDetails.Owner << "\n";
		bVerify = false;
	}

	if (UserDetails.UserHash != UserDirDetails.RequiredHash)
	{
		std::cerr << "User: " << UserDetails.Username << " Has entered the wrong password.\n";
		bVerify = false;
	}
	return bVerify;
}