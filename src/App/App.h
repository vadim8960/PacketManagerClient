//
// Created by vadim on 08.04.23.
//

#ifndef PACKETMANAGERCLIENT_APP_H
#define PACKETMANAGERCLIENT_APP_H

#include <string>

class App {
private:
    App() {}
    App(const App &);
    App &operator=(App &);

    void init();
    void update();
    void add(std::string_view NamePacket);

public:
    static App *getInstance();

    void run(int argc, char **argv);
};

#endif //PACKETMANAGERCLIENT_APP_H
