#include <iostream>
#include "version.h"
#include "config.h"

void version(){
    std::cout << PROJECT_NAME << " " << PROJECT_VERSION << std::endl;
}