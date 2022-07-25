#include "../include/translator.hpp"

std::map<std::string, char> op_type_map = {
    // 't' para operação da seção texto
    // 'd' para operação da seção dados
    // 'c' para operação do cabeçalho
    // Operações
    {"ADD", 't'}, {"SUB", 't'}, {"MUL", 't'}, {"DIV", 't'}, {"JMP", 't'}, {"JMPN", 't'}, {"JMPP", 't'},{"JMPZ", 't'},
    {"COPY", 't'}, {"LOAD", 't'}, {"STORE", 't'}, {"INPUT", 't'}, {"OUTPUT", 't'}, {"STOP", 't'}, 
    // Diretivas
    {"SPACE", 'd'}, {"CONST", 'd'}, {"BEGIN", 'c'}, {"END", 'd'}, {"EXTERN", 'c'}, {"PUBLIC", 'c'}
};

std::map<std::string, int> op_size_map = {
    // Operações
    {"ADD", 2}, {"SUB", 2}, {"MUL", 2}, {"DIV", 2}, {"JMP", 2}, {"JMPN", 2}, {"JMPP", 2},{"JMPZ", 2},
    {"COPY", 3}, {"LOAD", 2}, {"STORE", 2}, {"INPUT", 2}, {"OUTPUT", 2}, {"STOP", 1 }, 
    // Diretivas
    {"SPACE", 1}, {"CONST", 1}, {"BEGIN", 0}, {"END", 0}, {"EXTERN", 0}, {"PUBLIC", 0}
    };

void Translator(fileData * input_file, fileData * outuput_file){
    std::map<std::string, int> * symbol_map = new std::map<std::string, int>();
    std::vector <compilationError> * error_list = new std::vector <compilationError>();

    tokenMatrix * input_matrix = new tokenMatrix{ .lines = 0};

    ConvertFileToMatrix(input_file, input_matrix);
    
    // Scanner
    CleanMatrix(input_matrix);
    LexicCheck(input_matrix, error_list);

    // Parser
    CheckSequentialIdentifiers(input_matrix, error_list);
    CheckOperations(input_matrix, error_list);


    // Análise semântica
    CheckSections(input_matrix, error_list);
    CheckSymbols(input_matrix, error_list, symbol_map);
    for (int i = 0; i < (*error_list).size(); i++){
        compilationError e = (*error_list)[i];
        std::cout << e.line << "  " << e.type << "  " << e.message << std::endl;
    }

    std::map<std::string, int>::iterator it = (*symbol_map).begin();
    while (it != (*symbol_map).end()){
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }

    // // Gerador de código
    // if (IsModule(input_matrix)){
    //     GenerateModuleProgram(input_matrix, symbol_map, outuput_file);
    // } else {
    //     GenerateCodeProgram(input_matrix, symbol_map, outuput_file);
    // }

}

// Analisador semântico
void CheckSections(tokenMatrix * matrix, std::vector<compilationError> * error_list){
    std::vector<std::string> matrix_line;
    std::map<std::string, char>::iterator it;
    std::string op;
    bool break_for = false;
    bool is_section = false;
    compilationError error;
    error.type = "Semantico";
    int i;

    // Procura SECAO TEXTO
    for (i = 0; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (int j = 0; j < matrix_line.size(); j++) {
            if (matrix_line[j] == "SECAO"){
                is_section = true;
            } else if (is_section){
                if (matrix_line[j] == "TEXTO") {
                    matrix->matrix[i] = {};
                } else{
                    error.message = "Falta da secao texto";
                    error.line = 0;
                    error_list->push_back(error);
                }
                break_for = true;
                break;
            }
        }
        if (break_for)
            break;
    }
    
    break_for = false;

    // Confere SECAO TEXTO e procura SECAO DADOS
    for (i; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (int j = 0; j < matrix_line.size(); j++) {
            if (matrix_line[j] == "SECAO") 
                continue;
            if (matrix_line[j] == "DADOS") {
                matrix->matrix[i] = {};
                break_for = true;
                break;
            } else {
                // Confere se não é rótulo, se for ignora
                if (matrix_line[j][matrix_line[j].size()-1] != ':'){
                    op = matrix_line[j];
                    it = op_type_map.find(op);
                    if (it == op_type_map.end()){
                        error.message = "Operacao " + op + " nao identificada na secao TEXTO";
                        error.line = i;
                        error_list->push_back(error);
                    } else {
                        if (it->second != 't'){
                            error.message = "Operacao " + op + " na secao TEXTO";
                            error.line = i;
                            error_list->push_back(error);
                        }
                    }
                    break;
                }
            }
        }
        if (break_for)
            break;
    }

    // Confere SECAO DADOS
    for (i; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (int j = 0; j < matrix_line.size(); j++) {
            // Confere se não é rótulo, se for ignora
            if (matrix_line[j][matrix_line[j].size()-1] != ':'){
                op = matrix_line[j];
                it = op_type_map.find(op);
                if (it == op_type_map.end()){
                    error.message = "Operacao " + op + " nao identificada na secao DADOS";
                    error.line = i;
                    error_list->push_back(error);
                } else {
                    if (it->second != 'd'){
                        error.message = "Operacao " + op + " na secao DADOS";
                        error.line = i;
                        error_list->push_back(error);
                    }
                }
                break;
            }
        }
    }
}

void CheckSymbols(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, int> * symbol_map){
    std::vector<std::string> matrix_line;
    std::map<std::string, int>::iterator it;
    std::string token;
    int pos_counter = 0;
    bool symbol_exists = false;
    compilationError error;
    error.type = "Semantico";

    for (int i = 0; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (int j = 0; j < matrix_line.size(); j++){
            if (matrix_line[j][matrix_line[j].size()-1] == ':'){
                token = matrix_line[j].substr(0, matrix_line[j].size()-1);
                it = (*symbol_map).find(token);
                if (it == (*symbol_map).end()){
                    (*symbol_map)[token] = pos_counter;
                } else {
                    error.line = i;
                    error.message = "Declaracao ou rotulo " + token + " repetido";
                    error_list->push_back(error);
                }
                symbol_exists = true;
            } else {
                token = matrix_line[j];
                it = op_size_map.find(token);
                if (it != op_size_map.end()) {
                    pos_counter += it->second;
                }
                break;
            }
        }
        if (symbol_exists)
            matrix->matrix[i].erase(matrix->matrix[i].begin());
        symbol_exists = false;
    }
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