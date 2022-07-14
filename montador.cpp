#include "include/datatypes.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define TRUE 1
#define FALSE 0

#define PREPROCESSOR_MODE   'p'
#define ASSEMBLER_MODE      'o'

using namespace std;

bool CheckFlag(char processing_type);

int main (int argc, char** argv){
    if (argc != 5){
        cout << "Quantidade de argumentos invalida ("<< argc <<"),\ninsira no programa -diretiva nomedoprograma.asm nomedasaida.obj" << endl;
        return 0;
    }
    
    char processing_type = argv[1][1];
    if (string("op").find(processing_type) == string::npos){
        cout << "Diretiva invalida" << endl;
        return 0;
    }

    fileData * input = new fileData{ .name=argv[2], .content=""};
    fileData * output = new fileData{ .name=argv[3], .content=""};
    
    ifstream ifs(argv[2]);
    stringstream buffer;
    buffer << ifs.rdbuf();

    input->content = buffer.str();

    cout << input->content;

    ofstream ofs (output->name);
    ofs << input->content;
    ofs.close();
}