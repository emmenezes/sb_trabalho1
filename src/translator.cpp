#include "../include/translator.hpp"

std::map<std::string, char> op_type_map = {
    // 't' para operação da seção texto
    // 'd' para operação da seção dados
    // 'c' para operação do cabeçalho
    // Instruções
    {"ADD", 't'}, {"SUB", 't'}, {"MUL", 't'}, {"DIV", 't'}, {"JMP", 't'}, {"JMPN", 't'}, {"JMPP", 't'},{"JMPZ", 't'},
    {"COPY", 't'}, {"LOAD", 't'}, {"STORE", 't'}, {"INPUT", 't'}, {"OUTPUT", 't'}, {"STOP", 't'}, 
    // Diretivas
    {"SPACE", 'd'}, {"CONST", 'd'}, {"BEGIN", 'c'}, {"END", 'd'}, {"EXTERN", 'c'}, {"PUBLIC", 'c'}
};

std::map<std::string, int> op_size_map = {
    // Instruções
    {"ADD", 2}, {"SUB", 2}, {"MUL", 2}, {"DIV", 2}, {"JMP", 2}, {"JMPN", 2}, {"JMPP", 2},{"JMPZ", 2},
    {"COPY", 3}, {"LOAD", 2}, {"STORE", 2}, {"INPUT", 2}, {"OUTPUT", 2}, {"STOP", 1}, 
    // Diretivas
    {"SPACE", 1}, {"CONST", 1}, {"BEGIN", 0}, {"END", 0}, {"EXTERN", 0}, {"PUBLIC", 0}
};

std::map<std::string, std::string> op_code_map = {
    // Operações
    {"ADD", "1"}, {"SUB", "2"}, {"MUL", "3"}, {"DIV", "4"}, {"JMP", "5"}, {"JMPN", "6"}, {"JMPP", "7"},{"JMPZ", "8"},
    {"COPY", "9"}, {"LOAD", "10"}, {"STORE", "11"}, {"INPUT", "12"}, {"OUTPUT", "13"}, {"STOP", "14"},
};

void Translator(fileData * input_file, fileData * outuput_file){
    std::map<std::string, int> * symbol_map = new std::map<std::string, int>();
    std::vector <compilationError> * error_list = new std::vector <compilationError>();
    int * init_text = new int();

    tokenMatrix * input_matrix = new tokenMatrix{ .lines = 0};

    ConvertFileToMatrixCaps(input_file, input_matrix);
    
    // Scanner
    CleanMatrix(input_matrix);
    LexicCheck(input_matrix, error_list);

    // Parser
    CheckSequentialIdentifiers(input_matrix, error_list);
    CheckOperations(input_matrix, error_list);

    // Análise semântica
    CheckSections(input_matrix, error_list, init_text);
    CheckSymbols(input_matrix, error_list, symbol_map, init_text);
    
    // Gerador de código
    if (IsModule(input_matrix)){
        GenerateModuleProgram(input_matrix, symbol_map, outuput_file, init_text);
        std::cout << "Modulo montado!" << std::endl;
    } else {
        GenerateCodeProgram(input_matrix, symbol_map, outuput_file);
        std::cout << "Codigo montado!" << std::endl;
    }
}

// Analisador semântico
void CheckSections(tokenMatrix * matrix, std::vector<compilationError> * error_list, int * init_text) {
    std::vector<std::string> matrix_line;
    std::map<std::string, char>::iterator it;
    std::string op;
    bool break_for = false;
    bool is_section = false;
    compilationError error;
    error.type = "Semantico";
    int i;

    // Procura SECAO TEXTO
    for (i = 0; i < matrix->lines; i++) {
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
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
    
    *init_text = i;
    break_for = false;

    // Confere SECAO TEXTO e procura SECAO DADOS
    for (; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
            if (matrix_line[j] == "SECAO") 
                continue;
            if (matrix_line[j] == "DADOS") {
                matrix->matrix[i] = {};
                break_for = true;
                break;
            } else {
                // Ignora rótulos e analisa operações
                if (matrix_line[j][matrix_line[j].size()-1] != ':') {
                    op = matrix_line[j];
                    it = op_type_map.find(op);
                    if (it == op_type_map.end()) {
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
    for (; i < matrix->lines; i++) {
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
            // Confere se não é rótulo, se for ignora
            if (matrix_line[j][matrix_line[j].size()-1] != ':') {
                op = matrix_line[j];
                it = op_type_map.find(op);
                if (it == op_type_map.end()) {
                    error.message = "Operacao " + op + " nao identificada na secao DADOS";
                    error.line = i;
                    error_list->push_back(error);
                } else {
                    if (it->second != 'd') {
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

void CheckSymbols(tokenMatrix * matrix, std::vector<compilationError> * error_list, std::map<std::string, int> * symbol_map, int * init_text) {
    std::vector<std::string> matrix_line;
    std::map<std::string, int>::iterator it;
    std::string token;
    int pos_counter = 0;
    bool symbol_exists = false;
    compilationError error;
    error.type = "Semantico";

    for (int i = *init_text; i < matrix->lines; i++){
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++){
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
bool IsModule(tokenMatrix * matrix) {
    std::vector<std::string> matrix_line;
    for (int i = 0; i < matrix->lines; i++) {
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
            if (matrix_line[j][matrix_line[j].size()-1] == ':') {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void GenerateCodeProgram(tokenMatrix * matrix, std::map<std::string, int> * symbol_map, fileData * file) {
    std::vector<std::string> matrix_line;
    std::vector<std::string> instruction_list;
    std::map<std::string, int>::iterator it;
    std::map<std::string, char>::iterator it_aux;
    std::string token;

    for (int i = 0; i < matrix->lines; i++) {
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
            token = matrix_line[j];
            it_aux = op_type_map.find(token);
            if (it_aux != op_type_map.end()){
                if (it_aux->second == 't'){
                    instruction_list.push_back(op_code_map[token]);
                } else if (it_aux->second == 'd') {
                    if (token == "SPACE")
                        instruction_list.push_back("0");
                    else
                        instruction_list.push_back(matrix_line[++j]);
                }
            } else {
                it = (*symbol_map).find(token);
                if (it != ((*symbol_map).end())) {
                    instruction_list.push_back(std::to_string(it->second));
                } else {
                    instruction_list.push_back("??");
                }
            }
        }
    }

    ConvertCodeToFile(instruction_list, file);
}

void GenerateModuleProgram(tokenMatrix * matrix, std::map<std::string, int> * symbol_map, fileData * file, int * init_text) {
    std::vector<std::vector<std::string>> * use_vector = new std::vector<std::vector<std::string>>();
    std::map<std::string, int> * def_map = new std::map<std::string, int>();
    std::map<std::string, int> * use_map = new std::map<std::string, int>();
    std::map<std::string, int>::iterator it;
    std::map<std::string, char>::iterator it_char;
    std::vector<std::string> instruction_list;
    std::vector<std::string> matrix_line;
    std::string token;
    int i = 0;

    // Analisa diretivas antes da SEÇÃO TEXTO
    for (; i < *init_text; i++) {
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
            if (matrix_line[j] == "EXTERN")
                (*use_map)[matrix_line[j-1].substr(0, matrix_line[j-1].size()-1)] = 0;
            else if (matrix_line[j] == "PUBLIC")
                (*def_map)[matrix_line[j+1]] = 0;
        }
    }

    std::map<std::string, int>::iterator it_aux = (*def_map).begin();
    while (it_aux != (*def_map).end()){
        it = (*symbol_map).find(it_aux->first);
        (*def_map)[it_aux->first] = it->second;
        it_aux++;
    }

    // Analisa resto do programa
    for (; i < matrix->lines; i++) {
        matrix_line = matrix->matrix[i];
        for (long unsigned int j = 0; j < matrix_line.size(); j++) {
            token = matrix_line[j];
            it_char = op_type_map.find(token);
            if (it_char != op_type_map.end()){
                if (it_char->second == 't'){
                    instruction_list.push_back(op_code_map[token]);
                } else if (it_char->second == 'd') {
                    if (token == "SPACE")
                        instruction_list.push_back("0");
                    else
                        instruction_list.push_back(matrix_line[++j]);
                }
            } else {
                it = (*symbol_map).find(token);
                it_aux = (*def_map).find(token);
                if ((it != ((*symbol_map).end())) && (it_aux != ((*def_map).end()))) {
                    instruction_list.push_back(std::to_string(it->second));
                } else {
                    it_aux = (*use_map).find(token);
                    if (it_aux != ((*use_map).end())) {
                        use_vector->push_back({token, std::to_string(instruction_list.size())});
                        instruction_list.push_back("0");
                    } else if (it != ((*symbol_map).end())) {
                        instruction_list.push_back(std::to_string(it->second));
                    } else {
                        instruction_list.push_back("??");
                    }
                }
            }
        }
    }

    ConvertModuleToFile(instruction_list, use_vector, def_map, file);
}

// Conversor
void ConvertCodeToFile(std::vector <std::string> instruction_list, fileData * file) {
    std::string text;
    for (long unsigned int i = 0; i < instruction_list.size(); i++) {
        text.append(instruction_list[i]);
        text.append(" ");
    }
    text.pop_back();
    file->content = text;
}

void ConvertModuleToFile(std::vector <std::string> instruction_list, std::vector<std::vector<std::string>> * use_vector, std::map<std::string, int> * def_map, fileData * file) {
    std::string text;
    std::map<std::string, int>::iterator it;

    text.append("TABELA USO\n");
    for (unsigned long int i = 0; i < (*use_vector).size(); i++)
        text.append((*use_vector)[i][0] + " " + (*use_vector)[i][1] + "\n");
    text.append("\n");

    text.append("TABELA DEF\n");
    it = (*def_map).begin();
    while (it != (*def_map).end()){
        text.append(it->first + " " + std::to_string(it->second) + "\n");
        it++;
    }
    text.append("\n");

    for (long unsigned int i = 0; i < instruction_list.size(); i++) {
        text.append(instruction_list[i]);
        text.append(" ");
    }
    text.pop_back();
    file->content = text;
}