//Copyright(c) Goes to Jan Oliver Quant
#include "LoginRegisterHandler.hpp"
#include "User.hpp"
#include "UserDir.hpp"
#include <iostream>

bool RegisterNewUser(std::vector<User>& vUsers, User& UserDetails)
{
	char registerChoice;
	std::cout << "Would you like to make a new user?\n";

	std::cin >> registerChoice;

	if (registerChoice == 'y')
	{
		std::cout << "Enter your Username.\n";
		std::cin >> UserDetails.Username;
		std::cout << "Enter your password.\n";
		std::cin >> UserDetails.UserHash;


		std::cout << "Info: New User '" << UserDetails.Username << "' has been created.\n";
		vUsers.emplace_back(UserDetails);
	}
		else {
		std::cerr << "Info: An User might have tried to log in into a forreign account.\n";
		return false;
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
			std::cout << "User: '" << Username << "' Has logged in.\n";
			return true;
		}
	}
	std::cout << "Info: Login failed. User: '" << Username << "' not found or wrong password. Please try again.\n";
	return false;
}