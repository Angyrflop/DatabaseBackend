//Copyright(c) Goes to Jan Oliver Quant
#include "Verification.hpp"
#include <iostream>
#include "logginHandler.hpp"

bool VerifyUser(const User& UserDetails, const UserDir& UserDirDetails)
{
	bool bVerify{ true };
	if (UserDetails.Username != UserDirDetails.Owner)
	{
		Logger(LogType::WARNING) << UserDetails.Username << "Doesnt match '" << UserDirDetails.Owner << "'\n";
		bVerify = false;
	}

	if (UserDetails.UserHash != UserDirDetails.RequiredHash)
	{
		Logger(LogType::WARNING) << "User: '" << UserDetails.Username << "' Has entered the wrong password.\n";
		bVerify = false;
	}
	return bVerify;
}