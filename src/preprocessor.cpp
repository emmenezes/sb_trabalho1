#include "../include/preprocessor.hpp"

void PreProcessing(fileData * input_file, fileData * outuput_file){
    std::map<std::string, std::string> * equ_map = new std::map<std::string, std::string>();
    tokenMatrix * input_matrix = new tokenMatrix{ .lines = 0};
    tokenMatrix * output_matrix = new tokenMatrix{ .lines = 0};

    ConvertFileToMatrix(input_file, input_matrix);
    if (!FindEQU(input_matrix, equ_map)){
        ConvertMatrixToFile(input_matrix, outuput_file);
        return;
    }

    ProcessIF(input_matrix, output_matrix, equ_map);
    ConvertMatrixToFile(output_matrix, outuput_file);
}

bool FindEQU(tokenMatrix * input_matrix, std::map<std::string, std::string> * equ_map){
    std::vector<std::string> line;
    line = input_matrix->matrix[0];
    bool equ_exists = false;
    for (int i = 0; i < input_matrix->lines; i++){
        line = input_matrix->matrix[i];
        if (line.empty())
            continue;
        if (line[1] != "EQU")
            break;
        if (line[0][0] == ';')
            continue;
        (*equ_map)[line[0].substr(0, line[0].size()-1)] = line[2];
        equ_exists = true;
    }
    if (equ_exists)
        return 1;
    else
        return 0;
}

void ProcessIF(tokenMatrix * input_matrix, tokenMatrix * output_matrix, std::map<std::string, std::string> * equ_map){
    std::vector<std::string> input_line;
    std::vector<std::string> output_line;
    std::map<std::string, std::string>::iterator it;

    for (int i = 0; i < input_matrix->lines; i++){
        input_line = input_matrix->matrix[i];
        output_line = {};
        if (input_line[1] == "EQU"){
            output_matrix->matrix.push_back({});            
            continue;
        }
        for (long unsigned int j = 0; j < input_line.size(); j++){
            if (input_line[j][0] == ';'){
                for (; j<input_line.size(); j++){
                    output_line.push_back(input_line[j]);    
                }
                break;
            }
            it = (*equ_map).find(input_line[j]);
            if (it == (*equ_map).end()){
                output_line.push_back(input_line[j]);
            } else {
                // 2 casos: IF e apenas substituição
                if (input_line[0] == "IF"){
                    output_line.pop_back();
                    if (it->second == "0"){
                        output_matrix->matrix.push_back(output_line);
                        i++;
                    }
                } else {
                    output_line.push_back(it->second);
                }
            }
        }
        output_matrix->matrix.push_back(output_line);
    }
}