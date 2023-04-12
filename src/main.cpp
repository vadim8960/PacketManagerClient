#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include "App.h"

#include "NetworkApi.h"

int main(int argc, char *argv[]) {
    NetworkApi::getInstance().setPath("http://0.0.0.0:3000/packets_api/");
    NetworkApi::getInstance().getPacket("testlib.1.0");
//    App* t = App::Run(argc, argv);
    return 0;
}