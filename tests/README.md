# Lista de testes

## Montador 

### Testes sem erros

#### Pré-processamento "assembler/preprocessing"
| Nome do arquivo       | Descrição |
|-----------------------|-----------|
| test_equ1.ams         | Testa 2 EQU com IF e L1 é verdadeiro, testa comentários |
| test_equ2.ams         | Testa 2 EQU com IF e L2 é verdadeiro, testa comentários |
| test_equ3.ams         | Não tem EQU,testa comentários |
| test_equ4.ams         | Testa EQU com apenas CONST, testa comentários |

Para fazer:
* EQU que não é utilizado
* Outros exemplos sem comentários

#### Tradutor "assembler/translator"
| Nome do arquivo       | Descrição |
|-----------------------|-----------|
| | |

### Testes com erros no Tradutor

| Nome do arquivo | Descrição | Tipo do Erro |
|-|-|-|
| | |

## Ligador

### Testes sem erros

| Programa | Processamento | Tipo | Entrada |
|-|-|-|-|
| | | | |

## Tipos de erros

| Tipo      | Erro                                              |Tratado|
|-----------|---------------------------------------------------|-------|
| Léxico    | Tokens inválidos                                  |       |
| Sintático | Instruções com a quantidade de operando errado    |       |
| Sintático | Dois rótulos na mesma linha                       |       |
| Semântico | Falta da seção texto                              |       |
| Semântico | Instruções ou diretivas nas seções erradas        |       |
| Semântico | Declarações de rótulos ausentes                   |       |
| Semântico | Declarações ou rótulos repetidos                  |       |