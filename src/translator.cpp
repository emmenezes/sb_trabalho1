#include "../include/translator.hpp"

void Translator(fileData * input_file, fileData * outuput_file){
    std::map<std::string, std::string> * symbol_map = new std::map<std::string, std::string>();
    std::vector <compilationError> * error_list = new std::vector <compilationError>();

    tokenMatrix * input_matrix = new tokenMatrix{ .lines = 0};

    ConvertFileToMatrix(input_file, input_matrix);
    
    // Scanner
    CleanMatrix(input_matrix);
    LexicCheck(input_matrix, error_list);

    // Parser
    CheckSequentialIdentifiers(input_matrix, error_list);
    CheckOperations(input_matrix, error_list);

    for (int i = 0; i < (*error_list).size(); i++){
        compilationError e = (*error_list)[i];
        std::cout << e.line << "  " << e.type << "  " << e.message << std::endl;
    }

    // // Análise semântica
    // CheckSections(input_matrix, error_list);
    // CheckOperationSection(input_matrix, error_list);
    // CheckSymbols(input_matrix, error_list, symbol_map);

    // // Gerador de código
    // if (IsModule(input_matrix)){
    //     GenerateModuleProgram(input_matrix, symbol_map, outuput_file);
    // } else {
    //     GenerateCodeProgram(input_matrix, symbol_map, outuput_file);
    // }

}

// Analisador semântico
void CheckSections(tokenMatrix * matrix, std::vector<compilationError> * error_list){

}

void CheckOperationSection(tokenMatrix * matrix, std::vector<compilationError> * error_list){

}

void CheckSymbols(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, std::string> * symbol_map){
    
}

// Sintetizador
bool IsModule(tokenMatrix * matrix){
    return true;
}

void GenerateCodeProgram(tokenMatrix * matrix, std::map<std::string, std::string> * symbol_map, fileData * file){
    std::vector <int> instruction_list;

    ConvertCodeToFile(instruction_list, file);
}

void GenerateModuleProgram(tokenMatrix * matrix, std::map<std::string, std::string> * symbol_map, fileData * file){
    std::map<std::string, std::string> * use_map = new std::map<std::string, std::string>();
    std::map<std::string, std::string> * def_map = new std::map<std::string, std::string>();
    std::vector <int> instruction_list;

    ConvertModuleToFile(instruction_list, use_map, def_map, file);

}

// Conversor
void ConvertCodeToFile(std::vector <int> instruction_list, fileData * file){

}

void ConvertModuleToFile(std::vector <int> instruction_list, std::map<std::string, std::string> * use_map, std::map<std::string, std::string> * def_map, fileData * file){

}