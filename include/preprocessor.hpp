#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "datatypes.hpp"

#include <map>

void PreProcessing(fileData * input_file, fileData * outuput_file);
bool FindEQU(tokenMatrix * input_matrix, std::map<std::string, std::string> * equ_map);
void ProcessIF(tokenMatrix * input_matrix, tokenMatrix * output_matrix, std::map<std::string, std::string> * equ_map);

#endif