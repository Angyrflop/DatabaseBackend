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
/*
Things to keep in mind:
Only one route. Dont overlap otherwise the programm will crash. Found out the hard way after debugging for half an hour.
*/
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

    CROW_ROUTE(app, "/login")
        ([](){
            auto page = crow::mustache::load_text("index.html");
            return page;
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

        std::cout << "METHOD: POST/register. Body: " << req.body << std::endl;

        auto x = crow::json::load(req.body);

        // Checks if the json is empty
        if (!x || !x.has("username") || !x.has("password")) {
            return crow::response(400, "Invalid input.");
        }

        std::string username = x["username"].s();   //The '.s()' basically converts the json to a string
        std::string password = x["password"].s();

        User user(username, password);

        vUsers.push_back(user);
        SaveUsersToJson(vUsers, Config::USERS_FILE);

        return crow::response(201, "User registered");
            });

    app.port(8080).multithreaded().run();
    return true;
}