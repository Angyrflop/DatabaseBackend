//Copyright(c) Goes to Jan Oliver Quant

#include <iostream>
#include <vector>
#include <json.hpp>
#include <User.hpp>
#include <UserDir.hpp>
#include <JsonHandler.hpp>
#include <Verification.hpp>
#include <LoginRegisterHandler.hpp>
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

	User UserDetails;
	UserDir UserDirDetails;
	char Input;

    if (!LoadUsers(vUsers, Config::USERS_FILE))
    {
        abort();
    }

    StartWebPage();

    std::exit(0);
}