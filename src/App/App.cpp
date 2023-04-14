#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include "cxxopts.hpp"
#include "App.h"
#include "version.h"
#include <string>

namespace fs = std::filesystem;

App *App::getInstance() {
    static App instance;
    return &instance;
}

void App::init() {
    std::string s;
    char dir[256];
    getcwd(dir, 256);
    std::cout << "Current directory is " << dir << std::endl;
    fs::create_directories(std::string(dir) + "/.depend");
    std::ofstream f(std::string(dir) + "/dependences.txt");
    f.close();
}

void App::update() {
    std::cout << "Вызвана команда update" << std::endl;
}

void App::add(std::string NamePacket) {
    std::cout << "Вызвана команда add с параметром " << NamePacket << std::endl;
}

void App::run(int argc, char **argv) {
    cxxopts::Options options("test", "A brief description");

    options.add_options()
            ("i,init", "Print usage")
            ("u,update", "Print usage")
            ("a,add", "Print usage", cxxopts::value<std::string>())
            ("h,help", "Print usage")
            ("v,version", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("init"))
        init();
    if (result.count("update"))
        update();
    if (result.count("add")) {
        if (result.count("add") > 1) {
            std::cout << "ERROR" << std::endl;
            exit(0);
        } else {
            std::string NamePacket = result["add"].as<std::string>();
            add(NamePacket);
        }
    }
    if (result.count("version"))
        version();
    if ((result.count("init") + result.count("update") + result.count("version") + result.count("add") == 0) ||
        (result.count("help"))) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
}