#include <JsonHandler.hpp>
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "User.hpp"

using json = nlohmann::json;

bool SaveUsersToJson(const std::vector<User>& vUsers, const std::string& sFilePath)
{

	nlohmann::json j;

	for (const auto& User : vUsers)
	{
		j.push_back({
			{"Username", User.Username},
			{"UserHash", User.UserHash},
			{"IsVerified", User.IsVerified}
			});
	}

	std::ofstream oFile(sFilePath);
	if (!oFile.is_open())
	{
		std::cerr << "Error: could not open '" << sFilePath << "' for writing.\n";
		return false;
	}

	oFile << j.dump(4);
	oFile.close();
	return true;

}

bool LoadUsers(std::vector<User>& vUsers, const std::string& sFilePath)
{
	std::ifstream iFile(sFilePath);
	if (!iFile.is_open())
	{
		std::cerr << "Error: Couldnt read Users.\n";
		return false;
	}

	//Not my code
	if (iFile.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Warning: Users file is empty.\n";
		return false;
	}

	json j;
	iFile >> j;
	iFile.close();

	for (const auto& user : j)
	{
		User AddUser;
		AddUser.IsVerified = user["IsVerified"].get<bool>();
		AddUser.UserHash = user["UserHash"].get<std::string>();
		AddUser.Username = user["Username"].get<std::string>();
		vUsers.push_back(AddUser);

	}

	std::cout << "Info: Loaded '" << vUsers.size() << "' Users into vUsers.\n";
	std::cout << "Info: Users loading was successful.\n";
	return true;
}