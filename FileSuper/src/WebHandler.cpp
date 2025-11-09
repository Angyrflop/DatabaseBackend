// Copyright (c) goes to Jan Oliver Quant
#include "WebHandler.hpp"
#include <crow.h>
#include "crow/mustache.h"
#include <User.hpp>
#include <fstream>
#include <vector>
#include <JsonHandler.hpp>
#include <config.hpp>
#include <LoginRegisterHandler.hpp>
#include <HashingHandler.hpp>

bool StartWebPage()
{
	crow::SimpleApp app;


    CROW_ROUTE(app, "/Style.css")
        ([](const crow::request&, crow::response& res) {
        res.set_static_file_info("Style.css");
        res.end();
            });

    CROW_ROUTE(app, "/script.js")
        ([](const crow::request&, crow::response& res) {
        res.set_static_file_info("script.js");
        res.end();
            });

    CROW_ROUTE(app, "/login").methods("GET"_method)
        ([](){
            auto page = crow::mustache::load_text("index.html");
            return page;
        });

    CROW_ROUTE(app, "/login").methods("POST"_method)
        ([](const crow::request& req) {

        auto x = crow::json::load(req.body);

        if (!x || !x.has("username") || !x.has("password")) {
            return crow::response(404, "Invalid input.");
        }

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        User user(username, password);

        if (!LoginUser(vUsers, user)) {
            return crow::response(404, "User doesn't exist or wrong password.");
        }

        return crow::response(201, "Login successful!");
            });

    CROW_ROUTE(app, "/privacy-policy")
        ([](const crow::request&, crow::response& res) {
        std::ifstream pdf_file("PrivacyNotice.pdf", std::ios::binary);

        if (!pdf_file)
        {
            res.code = 404;
            res.write("PDF not found. Please contact the owner of this website, this is clearly a mistake.");
            res.end();
            return;
        }

        std::string pdf_content((std::istreambuf_iterator<char>(pdf_file)),
                                std::istreambuf_iterator<char>());
        pdf_file.close();

        res.set_header("Content-Type", "application/pdf");
        res.set_header("Content-Disposition", "inline; filename=\"PrivacyNotice.pdf");

        res.write(pdf_content);
        res.end();
            });

    CROW_ROUTE(app, "/register").methods("GET"_method)
        ([](){
            auto page = crow::mustache::load_text("register.html");
            return page;
        });

    CROW_ROUTE(app, "/register").methods("POST"_method)
        ([](const crow::request& req) {

        auto x = crow::json::load(req.body);

        // Checks if the json is empty
        if (!x || !x.has("username") || !x.has("password")) {
            return crow::response(400, "Invalid input.");
        }

        std::string username = x["username"].s();   //The '.s()' basically converts the json to a string
        std::string password = x["password"].s();

        if (FindUser(vUsers, username)) {
            return crow::response(404, "User already exists.");
        }

        std::string HashedPassword = HashPassword(password);

        User user(username, HashedPassword);

        vUsers.push_back(user);
        SaveUsersToJson(vUsers, Config::USERS_FILE);

        return crow::response(201, "User registered");
            });

    CROW_ROUTE(app, "/delete-account").methods("GET"_method)
        ([]() {
        auto page = crow::mustache::load_text("delete.html");
        return page;
            });
    CROW_ROUTE(app, "/delete-account").methods("DELETE"_method)
        ([](const crow::request& req) {

        auto x = crow::json::load(req.body);

        if (!x || !x.has("username") || !x.has("password")) {
            return crow::response(404, "Invalid input");
        }

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        User user(username, password);

        DeleteUser(vUsers, user);

        return crow::response(200, "User deleted");
            });
    app.port(8080).multithreaded().run();
    return true;
}