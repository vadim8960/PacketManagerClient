#include <iostream>
#include <filesystem>
#include "cxxopts.hpp"
#include "App.h"
#include "version.h"
#include <string>
#include "Utils.h"
#include <toml++/toml.h>
#include "FileReader.h"
#include "NetworkApi.h"

namespace fs = std::filesystem;

App *App::getInstance() {
    static App instance;
    return &instance;
}

void App::init() {
    std::string currentDir = PacketManagerUtils::getCurrentPath();
    static constexpr std::string_view packinfo_sourse = "[info]\n"
                                                        "name = \"\"\n"
                                                        "version = \"\"\n"
                                                        "author = \"\"\n"
                                                        "contact = \"\"\n"
                                                        "link = \"\"\n"
                                                        "\n"
                                                        "dependencies = [\n"
                                                        "]\n";
    fs::create_directories(currentDir + "/.depend");
    std::ofstream out(currentDir + "/packinfo.toml");
    out << packinfo_sourse;
}

void App::update() {
    std::string currentDir = PacketManagerUtils::getCurrentPath();
    auto file = FileReader::read(currentDir + "/packinfo.toml", false);
    toml::table config = toml::parse(file);
    toml::array* deps = config["info"]["dependencies"].as_array();
    for (std::size_t i = 0; i < deps->size(); ++i) {
        std::string packet = *deps->get(i)->value<std::string>();
        std::cout << packet << std::endl;
        NetworkApi::getInstance().getPacket(packet);
    }
}

void App::add(std::string_view NamePacket) {
    std::string currentDir = PacketManagerUtils::getCurrentPath();
    auto file = FileReader::read(currentDir + "/packinfo.toml", false);
    toml::table config = toml::parse(file);
    config["info"]["dependencies"].as_array()->push_back(NamePacket);
    std::ofstream out(currentDir + "/packinfo.toml", std::ios::out);
    out << config;
}

void App::run(int argc, char **argv) {
    cxxopts::Options options("test", "A brief description");

    NetworkApi::getInstance().setPath("http://0.0.0.0:3000/packets_api/");

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