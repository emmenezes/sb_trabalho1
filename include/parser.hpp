#ifndef PARSER_H
#define PARSER_H

#include "datatypes.hpp"
#include "error.hpp"

#include <string>

std::map<std::string, int> op_args_map = {
    // Operações
    {"ADD", 1}, {"SUB", 1}, {"MUL", 1}, {"DIV", 1}, {"JMP", 1}, {"JMPN", 1}, {"JMPP", 1},{"JMPZ", 1},
    {"COPY", 2}, {"LOAD", 1}, {"STORE", 1}, {"INPUT", 1}, {"OUTPUT", 1}, {"STORE", 0 }, 
    // Diretivas
    {"SPACE", 0}, {"CONST", 1}, {"BEGIN", 0}, {"END", 0}, {"EXTERN", 0}, {"PUBLIC", 0}
    };



void CheckSequentialIdentifiers(tokenMatrix * matrix, std::vector<compilationError> * error_list);
void CheckOperations(tokenMatrix * matrix, std::vector<compilationError> * error_list);

#endif