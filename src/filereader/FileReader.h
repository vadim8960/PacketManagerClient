//
// Created by vadim on 07.03.23.
//

#ifndef PACKETMANAGERSERVER_FILEREADER_H
#define PACKETMANAGERSERVER_FILEREADER_H

#include <string>
#include <vector>

typedef std::string Line;

class FileReader {
public:
    static Line read(const std::string &path, bool isbin);
    static std::vector<Line> readlines(const std::string& path);
};


#endif //PACKETMANAGERSERVER_FILEREADER_H
