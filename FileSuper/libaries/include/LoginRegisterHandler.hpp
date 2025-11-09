//Copyright(c) Goes to Jan Oliver Quant
#pragma once
#include <vector>
#include "User.hpp"

bool RegisterNewUser(std::vector<User>& vUsers, User& UserDetails);

bool LoginUser(const std::vector<User>& vUsers, User& UserDetails);

std::string FindPassword(const std::vector<User>& vUsers, const std::string& username);

bool FindUser(const std::vector<User>& vUsers, const std::string& username);

int GetUserIndex(const std::vector<User>& vUsers, const std::string& username);