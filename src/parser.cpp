#include "../include/parser.hpp"

void CheckSequentialIdentifiers(tokenMatrix * matrix, std::vector<compilationError> * error_list){
    std::vector<std::string> matrix_line;
    bool prev_is_symbol = false;
    compilationError error;
    error.type = "Sintatico";
    error.message = "Dois ou mais identificadores em sequencia";

    for (int i = 0; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (int j = 0; j < matrix_line.size(); j++){
            if (matrix_line[j][matrix_line[j].size()-1] == ':'){
                if (prev_is_symbol){
                    error.line = i;
                    error_list->push_back(error);
                } 
                prev_is_symbol = true;
            } else {
                prev_is_symbol = false;
            }
            if ((matrix_line[j] == "SECAO") && (prev_is_symbol)){
                error.line = i;
                error_list->push_back(error);
                prev_is_symbol = false;
            }
        }
    }
    if (prev_is_symbol){
        error.message = "Identificador sem atribuição";
        error.line = matrix->lines - 1;
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
        if (it->second != op_quant){
            error.message = "Quantidade de operando incorreta na operacao " + op + ", com " + std::to_string(op_quant) + " operandos";
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