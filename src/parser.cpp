#include "../include/parser.hpp"

std::map<std::string, int> op_args_map = {
    // Operações
    {"ADD", 1}, {"SUB", 1}, {"MUL", 1}, {"DIV", 1}, {"JMP", 1}, {"JMPN", 1}, {"JMPP", 1},{"JMPZ", 1},
    {"COPY", 2}, {"LOAD", 1}, {"STORE", 1}, {"INPUT", 1}, {"OUTPUT", 1}, {"STORE", 0 }, 
    // Diretivas
    {"SPACE", 0}, {"CONST", 1}, {"BEGIN", 0}, {"END", 0}, {"EXTERN", 0}, {"PUBLIC", 0}
    };

void CheckSequentialIdentifiers(tokenMatrix * matrix, std::vector<compilationError> * error_list){
    std::vector<std::string> matrix_line;
    bool prev_is_symbol = false;
    compilationError error;
    error.type = "Sintatico";

    for (int i = 0; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (int j = 0; j < matrix_line.size(); j++){
            if (matrix_line[j][matrix_line[j].size()-1] == ':'){
                if (prev_is_symbol){
                    error.message = "Dois ou mais identificadores em sequencia";
                    error.line = i;
                    error_list->push_back(error);
                } 
                prev_is_symbol = true;
                error.line = i;
            } else if ((matrix_line[j] == "SECAO") && (prev_is_symbol)){
                error.message = "Identificador sem atribuição";
                error_list->push_back(error);
                prev_is_symbol = false;
            } else {
                prev_is_symbol = false;
            } 
        }
    }
    if (prev_is_symbol){
        error.message = "Identificador sem atribuição";
        error.line = matrix->lines;
        error_list->push_back(error);
    }
}

void CheckOperations(tokenMatrix * matrix, std::vector<compilationError> * error_list){
    std::vector<std::string> matrix_line;
    std::map<std::string, int>::iterator it;
    std::string op;
    int op_quant;
    compilationError error;
    error.type = "Sintatico";

    for (int i = 0; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        // Checa se é identificador
        if (matrix_line.size() == 0)
            continue;
        if (matrix_line[0] == "SECAO")
            continue; 
        if (matrix_line[0][matrix_line[0].size()-1] == ':'){
            if (matrix_line.size() == 1)
                continue;
            op = matrix_line[1];
            op_quant = matrix_line.size()-2;
        } else {
            op = matrix_line[0];
            op_quant = matrix_line.size()-1;
        }
        it = op_args_map.find(op);
        if (it == op_args_map.end()){
            error.message = "Operacao " + op + " nao identificada, com " + std::to_string(op_quant) + " operando(s)";
            error.line = i;
            error_list->push_back(error);
            continue;
        }
        if (it->second != op_quant){
            error.message = "Quantidade de operando incorreta na operacao " + op + ", com " + std::to_string(op_quant) + " operando(s)";
            error.line = i;
            error_list->push_back(error);
            continue;
        }
        if (op == "COPY"){
            if (matrix_line[matrix_line.size()-2][matrix_line[matrix_line.size()-2].size()-1] != ','){
                error.message = "Operacao COPY nao esta separada por virgulas";
                error.line = i;
                error_list->push_back(error);
            }
        }
    }
}