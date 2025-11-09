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
			{"UserHash", User.UserHash}
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
		Logger(LogType::WARNING) << "LoadUsers: Couldnt open users.";
		return false;
	}

	//Not my code
	if (iFile.peek() == std::ifstream::traits_type::eof())
	{
		Logger(LogType::WARNING) << "LoadUsers: File is either corrupted or empty.";
		return false;
	}

	json j;
	iFile >> j;
	iFile.close();

	for (const auto& user : j)
	{
		User AddUser;
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

	if (i < 0 || i >= j.size())
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

	int i{ GetUserIndex(vUsers, UserDetails.Username) };


	if (i == -1)
	{
		Logger(LogType::WARNING) << "User '" << UserDetails.Username << "' not found.";
		return false;
	}

	std::string storedHash = FindPassword(vUsers, UserDetails.Username);

	if (!VerifyPassword(UserDetails.UserHash, storedHash))
	{
		Logger(LogType::WARNING) << "Password doesnt match. Abort.";
		return false;
	}

	if (!DeleteUserFromJson(Config::USERS_FILE, i))
	{
		Logger(LogType::ERROR) << "Failed to delete user from json.";
		return false;
	}

	vUsers.erase(vUsers.begin() + i);
	Logger(LogType::INFO) << "User '" << UserDetails.Username << "' has been deleted";
	return true;
}