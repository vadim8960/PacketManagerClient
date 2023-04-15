//
// Created by vadim on 13.04.23.
//

#ifndef PACKETMANAGERCLIENT_UTILS_H
#define PACKETMANAGERCLIENT_UTILS_H

#include <string>

namespace PacketManagerUtils {

    std::string getCurrentPath();

    void unzip(const std::string& path, const std::string& dest_path);

}

#endif //PACKETMANAGERCLIENT_UTILS_H
