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

static std::vector<std::string> splitString(std::string s, const std::string &del) {
    std::vector<std::string> res;
    std::string tmp;
    size_t pos;
    while ((pos = s.find(del)) != std::string::npos) {
        tmp = s.substr(0, pos);
        if (!tmp.empty())
            res.push_back(tmp);
        s.erase(0, pos + del.size());
    }
    if (!s.empty())
        res.push_back(s);
    return res;
}

static bool get_packet(const std::string &projectRoot, const std::string &packet_name) {
    auto pack = NetworkApi::getInstance().getPacket(packet_name);
    if (pack.empty()) return false;
    std::string packet_path = projectRoot + "/.depend/" + packet_name + ".tar.xz";
    std::string dest_packet_path = projectRoot + "/.depend/";
    std::ofstream out(packet_path, std::ios::out | std::ios::binary);
    out << pack;
    out.close();
    PacketManagerUtils::unzip(packet_path, dest_packet_path);
    return true;
}

static void recursive_packet_update(const std::string &projectRoot, const std::string &packet_path,
                                    std::map<std::string, bool> &valid_packets, unsigned prev_size = 0) {
    auto file = FileReader::read(packet_path, false);
    toml::table config = toml::parse(file);
    toml::array *deps = config["info"]["dependencies"].as_array();
    std::string packet;
    for (std::size_t i = 0; i < deps->size(); ++i) {
        packet = *deps->get(i)->value<std::string>();
        auto info = splitString(packet, "/");
        if (!get_packet(projectRoot, info[0] + "." + info[1]))
            continue;
        valid_packets[info[0]] = true;
        if (valid_packets.size() == prev_size)
            continue;
        recursive_packet_update(projectRoot, projectRoot + "/.depend/" + info[0] + "/packinfo.toml", valid_packets,
                                valid_packets.size());
    }
}

void App::update() {
    std::string projectRoot = PacketManagerUtils::getCurrentPath();
    std::map<std::string, bool> valid_packets;
    recursive_packet_update(projectRoot, projectRoot + "/packinfo.toml", valid_packets);
    std::ofstream cmake_out(projectRoot + "/.depend/CMakeLists.txt", std::ios::out);
    for (const auto &[key, value]: valid_packets) {
        cmake_out << "add_subdirectory(" + key + ")" << std::endl;
    }


//    auto file = FileReader::read(projectRoot + "/packinfo.toml", false);
//    toml::table config = toml::parse(file);
//    toml::array *deps = config["info"]["dependencies"].as_array();
//    std::string packet;
//    for (std::size_t i = 0; i < deps->size(); ++i) {
//        packet = *deps->get(i)->value<std::string>();
//        auto info = splitString(packet, "/");
//        if (!get_packet(projectRoot, info[0] + "." + info[1]))
//            continue;
//        cmake_out << "add_subdirectory(" + info[0] + ")" << std::endl;
//    }
}

void App::add(std::string_view NamePacket) {
    std::string projectRoot = PacketManagerUtils::getCurrentPath();
    auto file = FileReader::read(projectRoot + "/packinfo.toml", false);
    toml::table config = toml::parse(file);
    config["info"]["dependencies"].as_array()->push_back(NamePacket);
    std::ofstream out(projectRoot + "/packinfo.toml", std::ios::out);
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
    }
}