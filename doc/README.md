# Bibliotecas


## Datatypes

Classes:

* RawToken
    * Symbol
    * Location
* RawLine
    * vector &lt;Rawtoken>
* RawFile
    * vector &lt;Rawline>

* ObjectCode
* UseTable
* DefTable


## Scanner

Responsabilidades:
* Processar o arquivo inicial linha a linha
* Retirar espaçamentos, pula linha 
* Separa em tokens
* Retira comentários
* Torna toda as letras maiúsculas
* Confere se há tokens inválidos (iniciados em número)

## Parser

## Preprocessor

Responsabilidades:
* Procura diretivas de pré-processamento.
    * EQU: Substituir todas as aparições dos identificadores. Vem antes da seção texto.
    * IF: adicionar novos comandos para a seção texto se preciso. Vem depois na seção texto.

Obs:
É garantido que não há erros de pré-processamento!

## Assembler

## Linker

## Error

Classes:

* Erro
    * Tipo
    * Mensagem
    * Localização


# Referências

* [Guia de estilo de C++](https://google.github.io/styleguide/cppguide.html)
* [Regex](https://cplusplus.com/reference/regex/)
* [Fstream](https://cplusplus.com/reference/fstream/fstream/)
