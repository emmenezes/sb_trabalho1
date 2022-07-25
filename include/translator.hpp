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
void CheckSections(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, int> * use_map, std::map<std::string, int> * def_map);
void CheckSymbols(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, int> * symbol_map);

// Sintetizador
bool IsModule(tokenMatrix * matrix);
void GenerateCodeProgram(tokenMatrix * matrix, std::map<std::string, int> * symbol_map, fileData * file);
void GenerateModuleProgram(tokenMatrix * matrix, std::map<std::string, int> * symbol_map, std::map<std::string, int> * use_map, std::map<std::string, int> * def_map, fileData * file);

// Conversor
void ConvertCodeToFile(std::vector <std::string> instruction_list, fileData * file);
void ConvertModuleToFile(std::vector <std::string> instruction_list, std::map<std::string, int> * use_map, std::map<std::string, int> * def_map, fileData * file);

#endif