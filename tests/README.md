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
| test_lexic1       | X | Léxico        | Nomes de identificadores começam com números | LexicCheck |
| test_seqid1       | X | Sintático     | Dois identificadores em sequência | CheckSequentialIdentifiers |
| test_seqid2       | X | Sintático     | Três identificadores em sequência | CheckSequentialIdentifiers |
| test_seqid3       | X | Sintático     | Identificador antes de seção | CheckSequentialIdentifiers |
| test_quantop1     | X | Sintático     | SPACE com 1 argumento | CheckOperations |
| test_quantop2     | X | Sintático     | COPY com argumento sem vírgula | CheckOperations |
| test_quantop3     | X | Sintático     | COPY com 1 argumento | CheckOperations |
| test_quantop4     | X | Sintático     | BEGIN com argumento | CheckOperations |
| test_quantop5     | X | Sintático     | Identificador e COPY não separado por vírgula | CheckOperations |
| test_quantop6     | X | Sintático     | Identificador não separado por dois pontos | CheckOperations |
| test_section1     | X | Semântico     | Falta da seção texto | CheckSections |
| test_section2     | X | Semântico     | Identificador sem dois pontos, operação não identificada na seção texto | CheckSections |
| test_section3     | X | Semântico     | Operação CONST na seção texto | CheckSections |
| test_section4     | X | Semântico     | Operação SPACE na seção texto | CheckSections |
| test_section5     | X | Semântico     | Identificador sem dois pontos, operação não identificada na seção dados | CheckSections |
| test_section6     | X | Semântico     | Operação ADD na seção dados | CheckSections |
| test_section7     | X | Semântico     | Operação COPY na seção dados | CheckSections |
| test_section8     | X | Semântico     | Operação EXTERN na seção texto | CheckSections |
| test_symbols1     | X | Semântico     | Identificadores repetido 2 vezes | CheckSymbols |
| test_symbols2     | X | Semântico     | Identificadores repetido 3 vezes | CheckSymbols |
| test_symbols3     | X | Semântico     | Dois identificadores repetidos | CheckSymbols |
| test_symbols     | - | Semântico     |  | CheckSymbols |



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
| Sintático | OK | Instruções com a quantidade de operando errado |
| Sintático | OK | Dois identificadores na mesma linha |
| Semântico | OK | Falta da seção texto |
| Semântico | OK | Instruções ou diretivas nas seções erradas |
| Semântico | | Declarações de rótulos ausentes |
| Semântico | | Declarações ou rótulos repetidos |