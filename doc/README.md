# Bibliotecas


## Datatypes

### Structs:
* fileData
* tokenMatrix
* equIdentifier

#### Funções:
* `ConvertFileToMatrix`
* `ConvertMatrixToFile`

## Scanner

### Funções:
* `CleanMatrix` retira comentários
* `LexicCheckMatrix` confere se há tokens inválidos 

### Obs:
* Tokens inválidos
    * Token que começa com número

## Parser

### Funções:
* `CheckSequentialIdentifiers` confere se existe identificadores em sequência
* `CheckOperations` confere a quantidade de argumentos por operação

## Preprocessor

### Funções:
* `PreProcessing`
* `FindEQU` procura e lista diretiva EQU
* `ProcessIF` computa IFs com base na lista gerada por `FindEQU`

### Obs:
- É garantido que não há erros de pré-processamento!
- EQU vem antes da seção texto

## Translator

### Funções:
* `CheckSections` confere se a seção texto existe e confere se as operações estão na seção correta
* `CheckSymbols` gera mapa de símbolos e checa se há símbolos repetidos. Faz o papel do algoritmo de primeira passagem
* `IsModule` identifica se a matrix fornecida é um módulo ou não
* `GenerateCodeProgram` converte a matriz em uma lista de instruções e checa se há símbolos não declarados. Faz o papel do algoritmo de segunda passagem.
* `GenerateModuleProgram` converte a matriz em uma lista de instruções, uma tabela de uso e uma tabela de definições. Faz o papel do algoritmo de segunda passagem.
* `ConvertCodeToFile` converte a lista de instruções em texto.
* `ConvertModuleToFile` converte a lista de instruções, tabela de uso e tabela de definições em texto.

### Obs:
- Em caso de códigos com erro e referências não encontradas, preencher o código de máquina com ??

## Linker

## Error

### Struct:
* Erro {tipo, mensagem, localização}


# Referências

* [Guia de estilo de C++](https://google.github.io/styleguide/cppguide.html)
* [Regex](https://cplusplus.com/reference/regex/)
* [Fstream](https://cplusplus.com/reference/fstream/fstream/)
