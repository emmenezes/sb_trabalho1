# Lista de testes

## Montador 

### Testes sem erros

#### Pré-processamento ```assembler/preprocessing```
| Nome do arquivo   | X | Descrição | Função teste |
|-------------------|---|-----------|--------------|
| test_equ1         | X | Testa 2 EQU com IF e L1 é verdadeiro, testa comentários ||
| test_equ2         | X | Testa 2 EQU com IF e L2 é verdadeiro, testa comentários ||
| test_equ3         | X | Não tem EQU,testa comentários ||
| test_equ4         | X | Testa EQU com apenas CONST, testa comentários ||

Para fazer:
* EQU que não é utilizado
* Outros exemplos sem comentários

#### Tradutor ```assembler/translator```
| Nome do arquivo   | Descrição | Função teste |
|-------------------|-----------|--------------|
| | |

### Testes com erros no Tradutor ```assembler/translator```

| Nome do arquivo   | X | Tipo do Erro  | Descrição | Função-teste |
|-------------------|---|---------------|-----------|--------------|
| test_lexic1       | - | Léxico        | Nomes de identificadores começam com números | LexicCheck |
| test_lexic2       | - | Léxico        |  | LexicCheck |
| test_seqid1       | - | Sintático     | Dois identificadores em sequência | CheckSequentialIdentifiers |
| test_seqid2       | - | Sintático     | Três identificadores em sequência | CheckSequentialIdentifiers |
| test_seqid3       | - | Sintático     | Identificador antes de seção | CheckSequentialIdentifiers |
| test_quantop1     | - | Sintático     | SPACE com 1argumento | CheckOperations |
| test_quantop2     | - | Sintático     | COPY com argumento sem vírgula | CheckOperations |
| test_quantop3     | - | Sintático     | COPY com 1 argumento | CheckOperations |
| test_quantop4     | - | Sintático     | BEGIN com 2 argumentos| CheckOperations |
| test_quantop5     | - | Sintático     | Identificador e COPY não separado por vírgula | CheckOperations |
| test_quantop6     | - | Sintático     | | CheckOperations |


## Ligador

### Testes sem erros

| Programa | Processamento | Tipo | Entrada |
|-|-|-|-|
| | | | |

# Notação

X : Testado
O : Feito
- : Para fazer

# Tipos de erros

| Tipo      | Resolvido | Erro  |
|-----------|-----------|-------|
| Léxico    | OK | Tokens inválidos |
| Sintático | | Instruções com a quantidade de operando errado |
| Sintático | | Dois identificadores na mesma linha |
| Semântico | | Falta da seção texto |
| Semântico | | Instruções ou diretivas nas seções erradas |
| Semântico | | Declarações de rótulos ausentes |
| Semântico | | Declarações ou rótulos repetidos |