//
// Created by vadim on 08.04.23.
//

#ifndef PACKETMANAGERCLIENT_APP_H
#define PACKETMANAGERCLIENT_APP_H


class App {
private:
    App() {}
    App(const App &);
    App &operator=(App &);

    void init();
    void update();
    void deinit();
    void add(std::string NamePacket);
    void version();

public:
    static App *getInstance();

    void run(int argc, char **argv);
};

#endif //PACKETMANAGERCLIENT_APP_H
