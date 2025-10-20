//Copyright(c) Goes to Jan Oliver Quant
#include "LoginRegisterHandler.hpp"
#include "User.hpp"
#include "UserDir.hpp"
#include "logginHandler.hpp"
#include "JsonHandler.hpp"
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
	char registerChoice;

	std::cout << "Would you like to make a new user?\n";

	std::cin >> registerChoice;

	if (registerChoice == 'y')
	{
		std::cout << "Enter your Username.\n";
		std::cin >> UserDetails.Username;

		if (FindUser(vUsers, UserDetails.Username))
		{
			Logger(LogType::WARNING) << "User Already exist. Please enter a different name.";
			return false;
		}

		std::cout << "Enter your password.\n";
		std::cin >> UserDetails.UserHash;

		Logger(LogType::INFO) << "New User '" << UserDetails.Username << "' has been created.";
		vUsers.emplace_back(UserDetails);
	}
	return true;
}

bool LoginUser(const std::vector<User>& vUsers, User& UserDetails)
{
	std::string Username;
	std::string UserHash;
	//Temporary
	std::cin >> Username;
	std::cin >> UserHash;

	for (const auto& User : vUsers)
	{
		if (User.UserHash == UserHash && User.Username == Username)
		{
			Logger(LogType::INFO) << "User: '" << Username << "' has loggin in.";
			return true;
		}
	}
	Logger(LogType::WARNING) << "Login failed. User: '" << Username << "' not found or wrong password.";
	return false;
}

bool DeleteUser(std::vector<User>& vUsers, User& UserDetails)
{
	std::string Username;
	std::string UserHash;
	//Temp
	std::cin >> Username;
	std::cin >> UserHash;

	int i{ GetUserIndex(vUsers, Username) };
	UserDetails.UserHash = FindPassword(vUsers, Username);

	if (i == -1)
	{
		Logger(LogType::WARNING) << "User '" << Username << "' not found.";
		return false;
	}

	if (UserHash != UserDetails.UserHash)
	{
		Logger(LogType::WARNING) << "Password doesnt match. Abort.";
		return false;
	}

	DeleteUserFromJson("users.json", i);

	vUsers.erase(vUsers.begin() + i);
	return true;
}