//Copyright(c) Goes to Jan Oliver Quant
#include "LoginRegisterHandler.hpp"
#include "User.hpp"
#include "UserDir.hpp"
#include "logginHandler.hpp"
#include "JsonHandler.hpp"
#include <HashingHandler.hpp>
#include <iostream>

bool FindUser(const std::vector<User>& vUsers, const std::string& username)
{
	for (const auto& User : vUsers)
	{
		if (User.Username == username)
		{
			return true;
		}
	}

	return false;
}

std::string FindPassword(const std::vector<User>& vUsers, const std::string& username)
{
	for (const auto& User : vUsers)
	{
		if (User.Username == username)
		{
			return User.UserHash;
		}
	}
	return std::string();
}

int GetUserIndex(const std::vector<User>& vUsers, const std::string& username)
{
	for (size_t i = 0; i < vUsers.size(); ++i)
	{
		if (vUsers[i].Username == username)
		{
			return i;
		}
	}
	return -1;
}

bool RegisterNewUser(std::vector<User>& vUsers, User& UserDetails)
{

	std::string Password;

		if (FindUser(vUsers, UserDetails.Username))
		{
			Logger(LogType::WARNING) << "User Already exist. Please enter a different name.";
			return false;
		}

		std::cout << "Enter your password.\n";
		std::cin >> Password;

		UserDetails.UserHash = HashPassword(Password);

		Logger(LogType::INFO) << "New User '" << UserDetails.Username << "' has been created.";
		vUsers.emplace_back(UserDetails);

	return true;
}

bool LoginUser(const std::vector<User>& vUsers, User& UserDetails)
{
    if (!FindUser(vUsers, UserDetails.Username))
    {
        Logger(LogType::INFO) << "Attempted login failed - user not found.";
        return false;
    }

    std::string sStoredHash = FindPassword(vUsers, UserDetails.Username);

    // UserDetails.UserHash contains the plain password from the web request
    if (VerifyPassword(UserDetails.UserHash, sStoredHash))
    {
        Logger(LogType::INFO) << "Login successful.";
        return true;
    }

    Logger(LogType::INFO) << "Attempted login failed - wrong password.";
    return false;
}
