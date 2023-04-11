#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include "App.h"
#include "cxxopts.hpp"

#include "restclient-cpp/restclient.h"

int main(int argc, char *argv[]) {
    RestClient::Response r = RestClient::get("http://0.0.0.0:3000/packets_api/importantlib.1.0");
    std::cout << r.body << std::endl;
//    App* t = App::Run(argc, argv);
    return 0;
}