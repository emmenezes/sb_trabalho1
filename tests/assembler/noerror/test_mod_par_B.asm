modb: begin
n: extern
a: extern
f: extern
PUBLIC modb

secao texto
load n
loop: sub um
jmpz impar
sub um
jmpz par
jmp loop

par:
load 2
store A
jmp f

impar:
load 1
store a
JMP F

secao dados
um: const 1
dois: const 2
end