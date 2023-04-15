//
// Created by vadim on 13.04.23.
//

#include "Utils.h"

#include <unistd.h>
#include <iostream>

#define MAXIMUM_DIR_NAME_LEN 256

std::string PacketManagerUtils::getCurrentPath() {
    char dir[MAXIMUM_DIR_NAME_LEN];
    getcwd(dir, MAXIMUM_DIR_NAME_LEN);
    return std::string{dir};
}

void PacketManagerUtils::unzip(const std::string& path, const std::string& dest_path) {
    std::string cmd = "tar -xf " + path + " -C " + dest_path + " && rm " + path;
    system(cmd.c_str());
}