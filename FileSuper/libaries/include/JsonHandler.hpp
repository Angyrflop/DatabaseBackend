#pragma once

#include <vector>
#include <string>
#include "User.hpp"

bool SaveUsersToJson(const std::vector<User>& vUsers, const std::string& sFilePath);
bool LoadUsers(std::vector<User>& vUsers, const std::string& sFilePath);