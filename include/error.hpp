#ifndef ERROR_H
#define ERROR_H

#include <string>

struct compilationError {
    std::string type;
    std::string mensagem;
    int line; 
};

#endif 