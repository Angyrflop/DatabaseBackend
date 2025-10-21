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

int main()
{

    if (!initSodium())
    {
        Logger(LogType::ERROR) << "Failed to init sodium!";
        return 1;
    }

	User UserDetails;
	UserDir UserDirDetails;
	std::vector<User> vUsers;
	char Input;

    if (!LoadUsers(vUsers, Config::USERS_FILE))
    {
        abort();
    }

    while (true)
    {
        std::cin >> Input;

        switch (Input)
        {
        case '1':
        {
            LoginUser(vUsers, UserDetails);
            break;
        }
        case '2':
        {
            if (RegisterNewUser(vUsers, UserDetails))
            {
                if (!SaveUsersToJson(vUsers, Config::USERS_FILE))
                {
                    std::cerr << "Saving to JSON failed.\n";
                    std::abort();
                }
            }
            break;
        }
        case '3': // Temp
        {
            std::cout << "Closing Session\n";
            std::exit(0);
        }
        case '4':
        {
           DeleteUser(vUsers, UserDetails);
           break;
        }
        default:
        {
            std::cerr << "Invalid choice. Please try again.\n";
            break;
        }
        }
    }
    std::exit(0);
}