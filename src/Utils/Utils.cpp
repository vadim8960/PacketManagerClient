//
// Created by vadim on 13.04.23.
//

#include "Utils.h"

#include <unistd.h>

#define MAXIMUM_DIR_NAME_LEN 256

std::string PacketManagerUtils::getCurrentPath() {
    char dir[MAXIMUM_DIR_NAME_LEN];
    getcwd(dir, MAXIMUM_DIR_NAME_LEN);
    return std::string{dir};
}
