#include "../include/scanner.hpp"
#include "../include/error.hpp"

// Retorna matrix sem comentários
void CleanMatrix(tokenMatrix * input_matrix){
    std::vector<std::vector<std::string>> matrix;
    std::vector<std::string> matrix_line;
    std::vector<std::string> clean_line;

    for (int i = 0; i < input_matrix->lines; i++){
        matrix_line = input_matrix->matrix[i];
        clean_line = {};
        for (long unsigned int j = 0; j < matrix_line.size(); j++){
            if (matrix_line[j][0] == ';')
                break;
            clean_line.push_back(matrix_line[j]);
        }
        matrix.push_back(clean_line);
    }
    input_matrix->matrix = matrix;
}

// Confere se todos os tokens não começam com número
void LexicCheck(tokenMatrix * input_matrix, std::vector<compilationError> * error_list){
    std::vector<std::string> matrix_line;
    std::string token;
    bool is_number = true;
    compilationError error;
    error.type = "Lexico";
    error.message = "Token invalido";

    for (int i = 0; i < input_matrix->lines; i++){
        matrix_line = input_matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++){
            if (isdigit(matrix_line[j][0])){
                token = matrix_line[j];
                is_number = true;
                for (long unsigned int k = 0; k < token.size(); k++){
                    if (!isdigit(token[k])){
                        is_number = false;
                        break;
                    }
                }
                if (!is_number){
                    error.line = i;
                    error_list->push_back(error);
                }
            }
        }
    }
}