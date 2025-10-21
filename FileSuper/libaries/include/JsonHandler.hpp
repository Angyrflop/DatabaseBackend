//Copyright(c) Goes to Jan Oliver Quant
#pragma once

#include <vector>
#include <string>
#include "User.hpp"

bool SaveUsersToJson(const std::vector<User>& vUsers, const std::string& sFilePath);

bool LoadUsers(std::vector<User>& vUsers, const std::string& sFilePath);

bool DeleteUser(std::vector<User>& vUsers, User& UserDetails);

bool DeleteUserFromJson(const std::string& sFilePath, int i);