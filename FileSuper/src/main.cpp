//Copyright(c) Goes to Jan Oliver Quant

#include <iostream>
#include <vector>
#include "json.hpp"
#include "User.hpp"
#include "UserDir.hpp"
#include "JsonHandler.hpp"
#include "Verification.hpp"
#include "LoginRegisterHandler.hpp"

using json = nlohmann::json;

int main()
{
	User UserDetails;
	UserDir UserDirDetails;
	std::vector<User> vUsers;
	char Input;



    if (!LoadUsers(vUsers, "users.json"))
    {
        return 1;
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
                if (!SaveUsersToJson(vUsers, "users.json"))
                {
                    std::cerr << "Saving to JSON failed.\n";
                    return 1;
                }
            }
            break;
        }
        case '3': // Temp
        {
            std::cout << "Closing Session\n";
            return 0;
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
	return 0;
}