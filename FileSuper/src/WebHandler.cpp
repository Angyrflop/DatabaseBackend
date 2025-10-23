#include "WebHandler.hpp"
#include <crow.h>

bool StartWebPage()
{
	crow::SimpleApp app;

    CROW_ROUTE(app, "/<int>")([](int age) {
        auto page = crow::mustache::load("index.html");
        crow::mustache::context ctx({ {"age", age} });
        return page.render(ctx);
        });

    app.port(8080).multithreaded().run();
    return true;
}