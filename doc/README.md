# Bibliotecas


## Datatypes

Structs:

* fileData
* tokenMatrix
* equIdentifier

Funções:
* ConvertFileToMatrix
* ConvertMatrixToFile

## Scanner

Funções:
* CleanMatrix
* LexicCheckMatrix

Responsabilidades:
* Retira comentários
* Confere se há tokens inválidos (iniciados em número)

Erros que identifica:
* Tokens inválidos
    * Token que começa com letra


## Parser

Responsabilidades:


## Preprocessor

Funções:
* PreProcessing
* FindEQU
* ProcessIF

Responsabilidades:
* Procura diretivas de pré-processamento.
    * EQU: Substituir todas as aparições dos identificadores. Vem antes da seção texto.
    * IF: adicionar novos comandos para a seção texto se preciso. Vem depois na seção texto.

Obs:
- É garantido que não há erros de pré-processamento!

## Translator

Responsabilidades:

Obs:
- Em caso de códigos com erro e referências não encontradas, preencher o código de máquina com ??

## Linker

## Error

Struct:

* Erro {tipo, mensagem, localização}


# Referências

* [Guia de estilo de C++](https://google.github.io/styleguide/cppguide.html)
* [Regex](https://cplusplus.com/reference/regex/)
* [Fstream](https://cplusplus.com/reference/fstream/fstream/)
