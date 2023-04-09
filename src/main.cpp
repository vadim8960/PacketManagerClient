#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include "App.h"
#include "cxxopts.hpp"


int main(int argc, char *argv[]) {

    App* t = App::Run(argc, argv);
    return 0;
}