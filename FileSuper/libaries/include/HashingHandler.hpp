//Copyright(c) Goes to Jan Oliver Quant
#pragma once
#include <string>
#include <vector>

bool initSodium();

std::string HashPassword(const std::string& Password);

bool VerifyPassword(const std::string& Password, const std::string& hash);