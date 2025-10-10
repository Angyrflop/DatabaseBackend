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

	//Startup
	std::vector<User> vUsers;

	//Loads all Users to vUsers
	LoadUsers(vUsers, "users.json") ;

	RegisterNewUser(vUsers, UserDetails);




	//if (!VerifyUser)
	//{
	//	RegisterNewUser(...)
	//}

	//UserDetails.IsVerified = VerifyUser(UserDetails, UserDirDetails);
	//StoreVerifiedUser(vUsers, UserDetails);

	//SaveUsersToJson(vUsers, "users.json");

	//std::cout << vUsers[0].Username << vUsers[0].UserHash << vUsers[0].IsVerified;






	if (SaveUsersToJson(vUsers, "users.json"))
	{
		if (!SaveUsersToJson(vUsers, "users.json"))
		{
			std::cerr << "Saving to JSON failed.\n";
		}
	}




	return 0;
}