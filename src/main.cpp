#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
// #include <dir.h>
#include "cxxopts.hpp"

void init() {
    std::cout << "Вызвана команда init" << std::endl;
}

void update() {
    std::cout << "Вызвана команда update" << std::endl;
}

void deinit() {
    std::cout << "Вызвана команда deinit" << std::endl;
}

void add(std::string NamePacket) {
    std::cout << "Вызвана команда add с параметром " << NamePacket << std::endl;
}

void version() {
    std::cout << "Вызвана команда version" << std::endl;
}

int main(int argc, char **argv) {
    cxxopts::Options options("test", "A brief description");
// Начало
    char buff[16384];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1)
        buff[len] = '\0';
    std::cout << buff << std::endl;
//Конец

 /*   char dir[MAXDIR];
    getcwd(dir, MAXDIR);
    printf("Current directory is %s", dir);
    return 0; */

    options.add_options()
            ("i,init", "Print usage")
            ("u,update", "Print usage")
            ("d,deinit", "Print usage")
            ("a,add", "Print usage", cxxopts::value<std::string>())
            ("h,help", "Print usage")
            ("v,version", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("init"))
        init();
    if (result.count("update"))
        update();
    if (result.count("deinit"))
        deinit();
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
    if ((result.count("init") + result.count("update") + result.count("deinit") + result.count("add") == 0) ||
        (result.count("help"))) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    return 0;
}