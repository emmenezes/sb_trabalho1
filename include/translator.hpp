#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "datatypes.hpp"
#include "error.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include <iostream>

void Translator(fileData * input_file, fileData * outuput_file);

// Analisador semântico
void CheckSections(tokenMatrix * matrix, std::vector<compilationError> * error_list);
void CheckOperationSection(tokenMatrix * matrix, std::vector<compilationError> * error_list);
void CheckSymbols(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, std::string> * symbol_map);

// Sintetizador
bool IsModule(tokenMatrix * matrix);
void GenerateCodeProgram(tokenMatrix * matrix, std::map<std::string, std::string> * symbol_map, fileData * file);
void GenerateModuleProgram(tokenMatrix * matrix, std::map<std::string, std::string> * symbol_map, fileData * file);

// Conversor
void ConvertCodeToFile(std::vector <int> instruction_list, fileData * file);
void ConvertModuleToFile(std::vector <int> instruction_list, std::map<std::string, std::string> * use_map, std::map<std::string, std::string> * def_map, fileData * file);

#endif