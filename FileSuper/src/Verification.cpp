////Copyright(c) Goes to Jan Oliver Quant
//#include "Verification.hpp"
//#include <iostream>
//#include "logginHandler.hpp"
//
//bool VerifyUser(const User& UserDetails, const UserDir& UserDirDetails)
//{
//	if (UserDetails.Username != UserDirDetails.Owner)
//	{
//		Logger(LogType::WARNING) << UserDetails.Username << "Doesnt match '" << UserDirDetails.Owner << "'\n";
//		return false;
//	}
//
//	if (UserDetails.UserHash != UserDirDetails.RequiredHash)
//	{
//		Logger(LogType::WARNING) << "User: '" << UserDetails.Username << "' Has entered the wrong password.\n";
//		return false;
//	}
//	return true;
//}