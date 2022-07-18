#include "../include/datatypes.hpp"

void ConvertFileToMatrix(fileData * input_file, tokenMatrix * input_matrix){
    int lines = 0;
    std::string temp;
    std::vector<std::string> input_line;
    std::vector<std::string> matrix_line;

    input_line = Split(input_file->content, '\n');
    for (int i = 0; i<input_line.size(); i++){
        matrix_line = Split(input_line[i], ' ');
        input_matrix->matrix.push_back(matrix_line);
        lines++;
    }
    input_matrix->lines = lines;
}

void ConvertMatrixToFile(tokenMatrix * output_matrix, fileData * output_file){
    std::string text;
    std::vector <std::string> matrix_line;
    for (int i = 0; i < output_matrix->matrix.size(); i++){
        matrix_line = output_matrix->matrix[i];
        if (matrix_line.size() == 0){
            text.append("\n");
            continue;    
        }
        for (int j = 0; j < matrix_line.size(); j++){
            text.append(matrix_line[j]);
            text.append(" ");
        }
        text.pop_back();
        text.append("\n");
    }
    text.pop_back();
    output_file->content = text;
}

std::vector <std::string> Split(std::string text, char separator){
    std::string str;
    std::stringstream ss(text);
    std::vector <std::string> result;
    bool comment = false;
    while(getline(ss, str, separator)){
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        result.push_back(str);
    }
    return result;
}