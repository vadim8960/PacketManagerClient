#include <iostream>
#include "App.h"

#include <zlib.h>

#include "NetworkApi.h"

int main(int argc, char *argv[]) {

    printf("%s\n", zlibVersion());
//    NetworkApi::getInstance().setPath("http://0.0.0.0:3000/packets_api/");
//    NetworkApi::getInstance().getPacket("testlib.1.0");
//    App* t = App::Run(argc, argv);
    App::getInstance()->run(argc, argv);
    return 0;
}