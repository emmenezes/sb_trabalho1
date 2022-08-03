#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define TAM 500
#define NULO -'F'
#define TABELAS 100

// Funcao que le os dois arquivos.obj
void ligador(char *, char *);

//Funcao que abre o arquivo 1
void ligador(char *nome_arq1, char *nome_arq2){
    FILE *arq1;
    arq1 = fopen(nome_arq1, "r");   

//Caso nao seja possivel abrir o arquivo 
    if(arq1 == NULL){
        printf("Erro na leitura do arquivo 1 \n");
        exit(1);
    }
//Cria o arquivo de saida com o nome "programa_ligado"
    FILE *saida = fopen("programa_ligado", "w");  
    if(saida == NULL){
        printf("Erro no arquivo de saida\n");
        exit(1);
    }

    char linha[TAM];
    int flag_t = 0;

    if(nome_arq2 != NULL){ 
        int codigo_obj1[TAM], codigo_obj2[TAM];
        int cont = 0, cont_l = 0, cont_cod=0, cont_c = 0, cont_u = 0, cont_d = 0, fator_correcao = 0;        
        char *tabela_uso1[TABELAS], *tabela_uso2[TABELAS], *tabela_def1[TABELAS], *tabela_def2[TABELAS], map_bits[300];

        for (int k = 0; k < TABELAS ; k++) {  
            tabela_uso1[k] = (char*)malloc(50*sizeof(char));
            strcpy(tabela_uso1[k], "undefined");
            tabela_uso2[k] = (char*)malloc(50*sizeof(char));
            strcpy(tabela_uso2[k], "undefined");
            tabela_def1[k] = (char*)malloc(50*sizeof(char));
            strcpy(tabela_def1[k], "undefined");
            tabela_def2[k] = (char*)malloc(50*sizeof(char));
            strcpy(tabela_def2[k], "undefined");
        }
        for(int i = 0; i < TAM; i++){   
            codigo_obj1[i] = NULO;
            codigo_obj2[i] = NULO;
        }
//Funcao que abre o arquivo 2       
        FILE *arq2;
        arq2 = fopen(nome_arq2, "r");   

        if(arq2 == NULL){
            printf("Erro na leitura do arquivo 2\n");
            exit(1);
        }

        while(fgets(linha, sizeof(linha), arq1)){ 
            cont++;
        }
        arq1 = fopen(nome_arq1, "r");
        while(fgets(linha, sizeof(linha), arq1)){   
            char *token = strtok(linha, " \n\t");
            cont_l++;// conta as linhas do arquivo
            if(cont_l == cont) {
                cont_c = 3;
            }

            while(token) { 
                if(!strcmp(token, "TABELA")) {
                    token = strtok(NULL, " \n\t");

                    if(!strcmp(token, "USO")) {
                        cont_c = 1;
                    } else if(!strcmp(token, "DEF")) {
                        cont_c = 2;
                    }
                } else {
                    if(cont_c == 1) { // Guarda os dados da tabela de uso do codigo objeto 1
                        strcpy(tabela_uso1[cont_u], token);
                        cont_u++;
                    } else if(cont_c == 2) {// Guarda os dados da tabela de definicoes do codigo objeto 1
                        strcpy(tabela_def1[cont_d], token);
                        cont_d++;
                    } else if(cont_c == 3) {   // Guarda os dados do codigo objeto 1
                        sscanf(token, "%d", &codigo_obj1[fator_correcao]);
                        fator_correcao++; //Guarda o tamanho do codigo objeto 1
                    }
                }
                token = strtok(NULL, " \n\t");
            }
        }
        //Reinicia os valores para o arquivo 2
        cont_l = 0;
        cont_c = 0;
        cont_cod = 0;
        cont_u = 0;
        cont_d = 0;
        cont = 0;

        while(fgets(linha, sizeof(linha), arq2)){
            cont++;
        }
        arq2 = fopen(nome_arq2, "r");
        strcat(strcpy(map_bits,""),"");
        while(fgets(linha, sizeof(linha), arq2)){ 
            char *token = strtok(linha, " \n\t");
            cont_l++;
            if(cont_l == cont) {
                cont_c = 3;
            }

            while(token) {
                if(!strcmp(token, "TABELA")) {
                    token = strtok(NULL, " \n\t");

                    if(!strcmp(token, "USO")) {
                        cont_c = 1;
                    } else if(!strcmp(token, "DEF")) {
                        cont_c = 2;
                    }
                } else {
                    if(cont_c == 1) {  // Guarda os dados da tabela de uso do codigo objeto 2
                        strcpy(tabela_uso2[cont_u], token);    
                        cont_u++;
                    } else if(cont_c == 2) {  // Guarda os dados da tabela de definicoes do codigo objeto 2
                        strcpy(tabela_def2[cont_d], token);
                        cont_d++;
                    } else if(cont_c == 3) {  // Guarda os dados do codigo objeto 1
                        sscanf(token, "%d", &codigo_obj2[cont_cod]);

                        if(cont_l == 0) {    // Armazena o mapa de bits do arq2
                            strcat(map_bits,"0");
                        } else if(codigo_obj2[cont_cod] == 9) { //caso seja COPY-09
                            token = strtok(NULL, " \n\t");
                            cont_cod++;
                            sscanf(token, "%d", &codigo_obj2[cont_cod]);
                            token = strtok(NULL, " \n\t");
                            cont_cod++;
                            sscanf(token, "%d", &codigo_obj2[cont_cod]);
                            strcat(map_bits,"011");// coloca no mapa de bits a r r
                        } else if(codigo_obj2[cont_cod] == 14) {//caso seja STOP-14
                            strcat(map_bits,"0");// coloca no mapa de bits a 
                            cont_l = 0;
                        } else {
                            if(codigo_obj2[cont_cod] == 5) {
                                cont_l = 0;
                            }
                            token = strtok(NULL, " \n\t");
                            cont_cod++;
                            sscanf(token, "%d", &codigo_obj2[cont_cod]);
                            strcat(map_bits,"01");// coloca no mapa de bits a r 
                        }
                        cont_cod++;
                    }
                }
                token = strtok(NULL, " \n\t");
            }
        }
        //reinicia os valores dos contadores
        cont_l = 0;
        cont_c = 0;
        cont_cod = 0;
        cont_u = 0;
        cont_d = 0;
        cont = 0;
        int aux1, aux2;
        
    
        while(strcmp(tabela_uso1[cont_u], "undefined")){// utiliza as tabelas do modulo 1
            while(strcmp(tabela_def2[cont_d], "undefined")){
                if(!strcmp(tabela_uso1[cont_u], tabela_def2[cont_d])){
                    sscanf(tabela_uso1[cont_u + 1], "%d", &aux1);//soma os valores da tabela de definicao do modulo 2
                    sscanf(tabela_def2[cont_d + 1], "%d", &aux2);//aplica o fator de correcao do modulo 2
                    codigo_obj1[aux1] += aux2;
                    codigo_obj1[aux1] += fator_correcao;
                }
                cont_d += 2;
            }
            cont_u += 2;
            cont_d = 0;
        }
        while(codigo_obj1[cont] != NULO){ // escreve a saida do modulo 1
            fprintf(saida, "%d ", codigo_obj1[cont]);
            cont++;
        }

        cont_u = 0;
        cont_d = 0;
        cont = 0;

        while(strcmp(tabela_uso2[cont_u], "undefined")){// utiliza as tabelas do modulo 2
            while(strcmp(tabela_def1[cont_d], "undefined")){
                if(!strcmp(tabela_uso2[cont_u], tabela_def1[cont_d])){
                    sscanf(tabela_uso2[cont_u + 1], "%d", &aux1);
                    sscanf(tabela_def1[cont_d + 1], "%d", &aux2);
                    codigo_obj2[aux1] += aux2;
                    map_bits[aux1] = '0'; //auxilia no fator de correcao
                }
                cont_d += 2;
            }
            
            cont_u += 2;
            cont_d = 0;
        }

        while(codigo_obj2[cont] != NULO){  // Modulo 2
            if(map_bits[cont] == '1')   
                codigo_obj2[cont] += fator_correcao;  // aplica o fator de correcao
            fprintf(saida, "%d ", codigo_obj2[cont]); // salva os dados no arquivo de saida
            cont++;
        }
//libera a memoria
        for(int k = 0; k < TABELAS ; k++){
            free(tabela_uso1[k]);
            free(tabela_uso2[k]);
            free(tabela_def1[k]);
            free(tabela_def2[k]);
        }

    } else { // Caso so tenha um modulo
        int cont = 0, cont_l = 0;
        while(fgets(linha, sizeof(linha), arq1)){ 
            cont++;
        }
        arq1 = fopen(nome_arq1, "r");
        while(fgets(linha, sizeof(linha), arq1)){   
            char *token = strtok(linha, " \n\t");
            cont_l++;
            if(cont_l == cont) {
                while(token) {
                    fprintf(saida, "%s ", token);// salva os dados no arquivo de saida
                    token = strtok(NULL, " \n\t");
                }
            }
        }
    }
}

int main(int argc, char** argv){

    ligador(argv[1], argv[2]);
    printf("\nPrograma ligado com sucesso\n\n");

    return 0;
}