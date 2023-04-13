//
// Created by vadim on 11.04.23.
//

#ifndef PACKETMANAGERCLIENT_NETWORKAPI_H
#define PACKETMANAGERCLIENT_NETWORKAPI_H

#include <string>

class NetworkApi;

class NetworkApiDestroyer {
private:
    NetworkApi *instance;
public:
    ~NetworkApiDestroyer();

    void init(NetworkApi *inst);
};

class NetworkApi {
protected:
    NetworkApi() {}

    ~NetworkApi() {}

    NetworkApi(const NetworkApi &);

    NetworkApi &operator=(const NetworkApi &);

    friend class NetworkApiDestroyer;

public:
    static NetworkApi &getInstance();

    void setPath(std::string_view path);

    void getPacket(std::string_view packet_name);

private:
    static NetworkApi *instance;
    static NetworkApiDestroyer destroyer;
    std::string rest_path;
};

#endif //PACKETMANAGERCLIENT_NETWORKAPI_H
