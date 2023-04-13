#include <iostream>
#include "App.h"

#include <zlib.h>

#include "NetworkApi.h"

int main(int argc, char *argv[]) {
    App::getInstance()->run(argc, argv);
    return 0;
}