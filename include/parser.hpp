#ifndef PARSER_H
#define PARSER_H

#include "datatypes.hpp"
#include "error.hpp"

#include <string>

extern std::map<std::string, int> op_args_map;



void CheckSequentialIdentifiers(tokenMatrix * matrix, std::vector<compilationError> * error_list);
void CheckOperations(tokenMatrix * matrix, std::vector<compilationError> * error_list);

#endif