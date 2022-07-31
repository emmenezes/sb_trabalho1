# Trabalho Prático de Software Básico - 2022/1 - UnB

Equipe:
* Daniel Sanchez Trujillo - 18/0039229
* Eduarda Costa de Menezes, Emme - 17/0032353


## Como compilar

## Como usar o montador

### Para pré-processamento

```
./montador -o meuprograma.asm saida.obj
```

O resultado do pré-processamento é apenas o arquivo original com as diretivas pré-processadas. Não é realizada a tradução do código.

### Para tradução do código

```
./montador -p meuprograma.asm saida.obj
```

## Como usar o ligador

```
./ligador arquivo.obj arquivo2.obj
```

A saída padrão do ligador é o arquivo *TODO*.
