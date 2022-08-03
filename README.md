# Trabalho Prático de Software Básico - 2022/1 - UnB

Equipe:
* Daniel Erick Sanchez Trujillo - 18/0039229
* Eduarda Costa de Menezes, Emme - 17/0032353

Observação: os programas foram feitos para linux, mas o montador foi feito em C++ e o ligador em C. Na pasta de testes, há outro README explicando alguns testes que foram elaborados e onde estão localizados.

## Como compilar

## Como usar o montador

Para montar o programa, é preciso digitar:
```
g++ montador.cpp src/*.cpp -o montador
```

### Para pré-processamento

```
./montador -o meuprograma.asm saida.obj
```

O resultado do pré-processamento é apenas o arquivo original com as diretivas pré-processadas. Não é realizada a tradução do código. Ele não converte nenhum texto para maiúsculas, apenas processa EQU e IF.

### Para tradução do código

```
./montador -p meuprograma.asm saida.obj
```

A contagem de linhas para identificação de erro começa da linha 0.

## Como usar o ligador
Utiliza as saidas do montador(.obj) e liga os modulos. Para montar o programa, é preciso digitar:
```
gcc -o ligador ligador.c
```
Executa e gera o programa ligado com as entradas dos arquivos objeto.
```
./ligador arquivo1.obj arquivo2.obj
```

A saída padrão do ligador é o arquivo *TODO*.
