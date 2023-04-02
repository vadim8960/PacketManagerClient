#include <iostream>
#include <vector>
#include "cxxopts.hpp"

void init(){
    std::cout << "Вызвана команда init" << std::endl;
}

void update(){
    std::cout << "Вызвана команда update" << std::endl;
}

void deinit(){
    std::cout << "Вызвана команда deinit" << std::endl;
}

void add(std::string NamePacket){
    std::cout << "Вызвана команда add с параметром " << NamePacket << std::endl;
}

void version(){
    std::cout << "Вызвана команда version" << std::endl;
}




int main(int argc, char** argv)
{
    cxxopts::Options options("test", "A brief description");

    options.add_options()
            ("i,init", "Print usage")
            ("u,update", "Print usage")
            ("d,deinit", "Print usage")
            ("a,add", "Print usage", cxxopts::value<std::string>())
            ("h,help", "Print usage")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("init"))
        init();
    else if (result.count("update"))
        update();
    else if (result.count("deinit"))
        deinit();
    else if (result.count("add")){
        std::string NamePacket = result["add"].as<std::string>();
        add(NamePacket);
    }
    else if (result.count("version"))
        version();
    else{
        std::cout << options.help() << std::endl;
        exit(0);
    }

    return 0;
}