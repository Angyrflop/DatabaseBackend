//Copyright(c) Goes to Jan Oliver Quant
#include <sodium.h>
#include <string>
#include <logginHandler.hpp>
#include <vector>

/*
Since i do not really know what this libary does and all
i will add comments for myself to somewhat understand whats going on
*/

bool initSodium()
{
    if (sodium_init() == -1)
    {
        return false;
    }
    return true;
}

std::string HashPassword(const std::string& Password)
{
    //Acts as an container for the password
    std::vector<char> out(crypto_pwhash_STRBYTES);

    std::vector<char> pwd(Password.begin(), Password.end());

    int result = crypto_pwhash_str(
        out.data(),
        Password.c_str(), // password as const char *
        Password.size(),  // password length as unsigned long long
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE
    );

    //Clears hash and password from buffer if i believe
    sodium_memzero(pwd.data(), pwd.size());

    //Checks if the result was succesfull
    if (result != 0)
    {
        Logger(LogType::ERROR) << "Hashing failed, do we have enough memory?";
        return {};
    }
    return std::string(out.data());
}

bool VerifyPassword(const std::string& Password, const std::string& hash)
{
    if (hash.empty())
    {
        Logger(LogType::WARNING) << "Empty Hash!!!";
        return false;
    }

    std::vector<char> pwd(Password.begin(), Password.end());

    int VerifyResult = crypto_pwhash_str_verify(
        hash.c_str(),
        pwd.data(),
        static_cast<size_t>(pwd.size())
    );

    sodium_memzero(pwd.data(), pwd.size());

    if (VerifyResult == 0)
    {
        return true; // password matches hash
    }
    else
    {
        Logger(LogType::INFO) << "Password verification failed";
        return false;
    }
}
