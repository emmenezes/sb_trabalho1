# Lista de testes

## Montador 

### Testes sem erros

#### Pré-processamento ```assembler/preprocessing```
| Nome do arquivo   | X | Descrição |
|-------------------|---|-----------|
| test_equ1         | X | Testa 2 EQU com IF e L1 é verdadeiro, testa comentários |
| test_equ2         | X | Testa 2 EQU com IF e L2 é verdadeiro, testa comentários |
| test_equ3         | X | Não tem EQU,testa comentários |
| test_equ4         | X | Testa EQU com apenas CONST, testa comentários |

Para fazer:
* EQU que não é utilizado
* Outros exemplos sem comentários

#### Geral ```assembler/noerror```
| Nome do arquivo   | X | Descrição |
|-------------------|---|-----------|
| test_sumab1 | O | Soma dois identificadores a + b |
| test_sumab2 | O | Soma dois identificadores a + b e permite refazer soma |

Obs:
* Esses testes só podem ser marcados como feitos após o assembler estar completo

### Testes com erros no Tradutor ```assembler/translator```

| Nome do arquivo   | X | Tipo do Erro  | Descrição | Função-teste |
|-------------------|---|---------------|-----------|--------------|
| test_lexic1       | O | Léxico        | Nomes de identificadores começam com números | LexicCheck |
| test_seqid1       | O | Sintático     | Dois identificadores em sequência | CheckSequentialIdentifiers |
| test_seqid2       | O | Sintático     | Três identificadores em sequência | CheckSequentialIdentifiers |
| test_seqid3       | O | Sintático     | Identificador antes de seção | CheckSequentialIdentifiers |
| test_quantop1     | O | Sintático     | SPACE com 1 argumento | CheckOperations |
| test_quantop2     | O | Sintático     | COPY com argumento sem vírgula | CheckOperations |
| test_quantop3     | O | Sintático     | COPY com 1 argumento | CheckOperations |
| test_quantop4     | O | Sintático     | BEGIN com argumento | CheckOperations |
| test_quantop5     | O | Sintático     | Identificador e COPY não separado por vírgula | CheckOperations |
| test_quantop6     | O | Sintático     | Identificador não separado por dois pontos | CheckOperations |


## Ligador

### Testes sem erros

| Programa | Processamento | Tipo | Entrada |
|-|-|-|-|
| | | | |

# Notação

* X : Testado
* O : Feito
* \- : Para fazer

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