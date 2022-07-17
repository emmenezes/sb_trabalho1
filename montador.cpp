#include "include/datatypes.hpp"
#include "include/preprocessor.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define TRUE 1
#define FALSE 0

#define PREPROCESSOR_MODE   'p'
#define ASSEMBLER_MODE      'o'

using namespace std;

int main (int argc, char** argv){
    if (argc != 4){
        cout << "Quantidade de argumentos invalida ("<< argc <<"),\ninsira no programa -diretiva nomedoprograma.asm nomedasaida.obj" << endl;
        return 0;
    }
    
    char processing_type = argv[1][1];
    if (string("op").find(processing_type) == string::npos){
        cout << "Diretiva invalida" << endl;
        return 0;
    }

    fileData * input_file = new fileData{ .name=argv[2]};
    fileData * output_file = new fileData{ .name=argv[3]};
    
    ifstream ifs(argv[2]);
    stringstream buffer;
    buffer << ifs.rdbuf();
    input_file->content = buffer.str();

    if (processing_type == 'p'){
        PreProcessing(input_file, output_file);
    } else if (processing_type == 'o') {
        
    }

    ofstream ofs (output_file->name);
    ofs << output_file->content;
    ofs.close();
}