#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>
#include <vector>
#include <sstream>

struct fileData {
    std::string name;
    std::stringstream content;
};

struct tokenMatrix {
    int lines;
    std::vector<std::vector<std::string>> matrix;
};

struct equIdentifier {
    std::string name;
    int value;
};

#endif