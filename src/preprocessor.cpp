#include "../include/preprocessor.hpp"
#include <string>

void PreProcessing(fileData * input_file, fileData * outuput_file){
    std::map<const char*, std::string> * equ_map;
    tokenMatrix * input_matrix = new tokenMatrix{ .lines = 0};
    tokenMatrix * output_matrix = new tokenMatrix{ .lines = 0};

    CreateTokenMatrix(input_file, input_matrix);
    if (!FindEQU(input_matrix, equ_map)){
        ConvertMatrixToFile(input_matrix, outuput_file);
        return;
    }

    ProcessIF(input_matrix, output_matrix, equ_map);
    ConvertMatrixToFile(output_matrix, outuput_file);

}

// TODO: Talvez eu devesse passar essa função para datatypes para ser reutilizada na tradução
// TODO: Reformular essa função para usar regex
// Cuidados que fileData.content é stringstream, mas pode ser string, precisa mexer na struct
void CreateTokenMatrix(fileData * input_file, tokenMatrix * input_matrix){
    int lines = 0;
    std::string temp;
    std::stringstream temp_ss;
    std::string temp_token;
    std::vector<std::string> matrix_line;

    getline(input_file->content, temp);
    do{
        matrix_line = {};
        temp_ss.str(temp);
        getline(temp_ss, temp_token, ' ');
        // TODO: temp_ss não está sendo atualizado mesmo que temp esteja
        // O processo de salvar a matrix dá certo
        do {
            matrix_line.push_back(temp_token);
        } while (getline(temp_ss, temp_token, ' '));
        input_matrix->matrix.push_back(matrix_line);
        lines++;
    } while(getline(input_file->content, temp));
    input_matrix->lines = lines;
}

bool FindEQU(tokenMatrix * input_matrix, std::map<const char*, std::string> * equ_amp){
    return 1;
}
void ProcessIF(tokenMatrix * input_matrix, tokenMatrix * output_matrix, std::map<const char*, std::string> * equ_map){

}
void ConvertMatrixToFile(tokenMatrix * output_matrix, fileData * output_file){

}