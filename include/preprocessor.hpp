#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "datatypes.hpp"

#include <map>

void PreProcessing(fileData * input_file, fileData * outuput_file);
void CreateTokenMatrix(fileData * input_file, tokenMatrix * input_matrix);
bool FindEQU(tokenMatrix * input_matrix, std::map<const char*, std::string> * equ_amp);
void ProcessIF(tokenMatrix * input_matrix, tokenMatrix * output_matrix, std::map<const char*, std::string> * equ_map);
void ConvertMatrixToFile(tokenMatrix * output_matrix, fileData * output_file);

#endif