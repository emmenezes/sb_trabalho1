MOD_B: BEGIN
FAT: EXTERN
N: EXTERN
PUBLIC MOD_B

SECAO TEXTO

STORE AUX
MUL N
STORE N
LOAD AUX
JMP FAT

SECAO DADOS

AUX: SPACE

END

