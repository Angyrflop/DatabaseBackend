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
	char registerChoice;

	std::string Password;

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
		std::cin >> Password;

		UserDetails.UserHash = HashPassword(Password);

		Logger(LogType::INFO) << "New User '" << UserDetails.Username << "' has been created.";
		vUsers.emplace_back(UserDetails);
	}
	return true;
}

bool LoginUser(const std::vector<User>& vUsers, User& UserDetails)
{
	std::string Username;
	std::string password;
	//Temporary
	std::cin >> Username;
	std::cin >> password;

	for (const auto& User : vUsers)
	{
		if (Username == User.Username)
		{
		if (VerifyPassword(password, User.UserHash))
		{
			Logger(LogType::INFO) << "Login successful.";
			return true;
		}
		}


	}
	Logger(LogType::INFO) << "Usernames dont match with anyone in our database. Are you sure you dont want to register a new user?";
	return false;
}

