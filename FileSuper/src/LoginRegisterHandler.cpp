#include "LoginRegisterHandler.hpp"
#include "User.hpp"
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

bool LoginUser(const std::vector<User>&, User& UserDetails)
{
	if (UserDetails.Username != )
}