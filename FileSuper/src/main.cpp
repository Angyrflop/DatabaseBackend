//Copyright(c) Goes to Jan Oliver Quant
#include <User.hpp>
#include <JsonHandler.hpp>
#include <HashingHandler.hpp>
#include <logginHandler.hpp>
#include <cstdlib>
#include <config.hpp>
#include <WebHandler.hpp>

int main()
{

    if (!initSodium())
    {
        Logger (LogType::ERROR) << "Failed to init sodium!";
        return 1;
    }

    if (!LoadUsers(vUsers, Config::USERS_FILE))
    {
        Logger(LogType::ERROR) << "Failed to load users. Will proceed without users.";
    }

    StartWebPage();

    std::exit(0);
}