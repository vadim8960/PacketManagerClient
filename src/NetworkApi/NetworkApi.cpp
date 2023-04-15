//
// Created by vadim on 11.04.23.
//

#include "NetworkApi.h"
#include <iostream>
#include <fstream>

#include "base64.hpp"
#include <jsoncpp/json/json.h>
#include "restclient-cpp/restclient.h"

NetworkApi *NetworkApi::instance = nullptr;
NetworkApiDestroyer NetworkApi::destroyer;

NetworkApiDestroyer::~NetworkApiDestroyer() {
    delete instance;
}

void NetworkApiDestroyer::init(NetworkApi *inst) {
    instance = inst;
}

NetworkApi &NetworkApi::getInstance() {
    if (!instance) {
        instance = new NetworkApi;
        destroyer.init(instance);
    }
    return *instance;
}

void NetworkApi::setPath(std::string_view path) {
    rest_path = path;
}

std::string NetworkApi::getPacket(std::string_view packet_name) {
    std::string path = rest_path;
    path.append(packet_name);
    RestClient::Response resp = RestClient::get(path);
    Json::Value root;
    Json::Reader reader;
    bool res = reader.parse(resp.body, root);
    if (!res) {
        std::cout << "Cannot parsing json\n";
        exit(1);
    }
    std::cout << packet_name << " ... " << (resp.code == 200 ? "done" : "error") << std::endl;
    return base64::from_base64(root["data"].asString());
//    std::ofstream out("../tmp.tar.xz", std::ios::binary | std::ios::out);
//    if (!out.is_open()) {
//        std::cout << "Error open file\n";
//        exit(1);
//    }
//    out << ;
//    out.close();
}
