//
// Created by vadim on 11.04.23.
//

#include "NetworkApi.h"
#include <iostream>

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

void NetworkApi::getPacket(std::string_view packet_name) {
    RestClient::Response resp = RestClient::get(rest_path.append(packet_name));
    std::cout << resp.body << std::endl;
}
