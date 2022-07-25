#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "datatypes.hpp"
#include "error.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include <iostream>

extern std::map<std::string, char> op_type_map;
extern std::map<std::string, int> op_size_map;
extern std::map<std::string, std::string> op_code_map;

void Translator(fileData * input_file, fileData * outuput_file);

// Analisador semântico
void CheckSections(tokenMatrix * matrix, std::vector<compilationError> * error_list, int * init_text);
void CheckSymbols(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, int> * symbol_map, int * init_text);

// Sintetizador
bool IsModule(tokenMatrix * matrix);
void GenerateCodeProgram(tokenMatrix * matrix, std::map<std::string, int> * symbol_map, fileData * file);
void GenerateModuleProgram(tokenMatrix * matrix, std::map<std::string, int> * symbol_map, fileData * file, int * init_text);

// Conversor
void ConvertCodeToFile(std::vector <std::string> instruction_list, fileData * file);
void ConvertModuleToFile(std::vector <std::string> instruction_list, std::vector<std::vector<std::string>> * use_vector, std::map<std::string, int> * def_map, fileData * file);

#endif