//Copyright(c) Goes to Jan Oliver Quant
#include <JsonHandler.hpp>
#include <json.hpp>
#include <fstream>
#include <iostream>
#include "User.hpp"
#include "LoginRegisterHandler.hpp"
#include "logginHandler.hpp"
#include <HashingHandler.hpp>
#include <config.hpp>

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
		Logger(LogType::ERROR) << "Could not open'" << sFilePath << "' for writing.\n";
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
		Logger(LogType::WARNING) << "Couldnt open users.";
		return false;
	}

	//Not my code
	if (iFile.peek() == std::ifstream::traits_type::eof())
	{
		Logger(LogType::WARNING) << "File is either corrupted or empty.";
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

	Logger(LogType::WARNING) << "Loaded '" << vUsers.size() << "' users from database.";
	Logger(LogType::INFO) << "Users loading was successful.";
	return true;
}

static bool DeleteUserFromJson(const std::string& sFilePath, int i)
{
	std::ifstream iFile(sFilePath);
	if (!iFile.is_open())
	{
		Logger(LogType::WARNING) << "Couldnt open users.";
		return false;
	}

	if (iFile.peek() == std::ifstream::traits_type::eof())
	{
		Logger(LogType::WARNING) << "File is either corrupted or empty.";
		return false;
	}

	json j;
	iFile >> j;
	iFile.close();

	if (j < 0 || i >= j.size())
	{
		Logger(LogType::WARNING) << "Invalid index. No User removed.";
		return false;
	}

	j.erase(j.begin() + i);

	std::ofstream oFile(sFilePath);
	if (!oFile.is_open())
	{
		Logger(LogType::ERROR) << "Couldnt open users.";
		return false;
	}

	oFile << std::setw(4) << j;
	oFile.close();

	Logger(LogType::INFO) << "User removed from json.";
	return true;
}

bool DeleteUser(std::vector<User>& vUsers, User& UserDetails)
{
	std::string Username;
	std::string password;
	//Temp
	std::cin >> Username;
	std::cin >> password;

	int i{ GetUserIndex(vUsers, Username) };
	UserDetails.UserHash = FindPassword(vUsers, Username);

	if (i == -1)
	{
		Logger(LogType::WARNING) << "User '" << Username << "' not found.";
		return false;
	}

	if (!VerifyPassword(password, UserDetails.UserHash))
	{
		Logger(LogType::WARNING) << "Password doesnt match. Abort.";
		return false;
	}

	DeleteUserFromJson(Config::USERS_FILE, i);

	vUsers.erase(vUsers.begin() + i);
	return true;
}