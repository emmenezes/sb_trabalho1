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

    for (int i = 0; i < input_matrix->lines; i++){
        matrix_line = input_matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++){
            if (isdigit(matrix_line[j][0])){
                token = matrix_line[j];
                is_number = true;
                for (long unsigned int k = 0; k < token.size(); k++){
                    if (!isdigit(token[k])){
                        if (k == 1 && token[k] == 'X'){
                            int number = (int)std::strtol(token.c_str(), NULL, 0);
                            input_matrix->matrix[i][j] = std::to_string(number);
                            break;
                        } else {
                            is_number = false;
                            break;
                        }
                    }
                }
                if (!is_number){
                    error.line = i;
                    error.message = "Token \'" + token + "\' invalido";
                    error_list->push_back(error);
                }
            }
            if (matrix_line[j].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_:,") != std::string::npos){
                error.line = i;
                error.message = "Token \'" + token + "\' invalido";
                error_list->push_back(error);
            }
        }
    }
}