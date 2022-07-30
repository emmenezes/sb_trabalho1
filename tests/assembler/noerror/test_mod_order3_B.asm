m2: begin
l1: extern
public x
public Y
public Z
secao texto
copy x, maior
load maior
sub Y
jmpp maiorz
copy y, maior
maiorz: load MAIOR
SUB Z
JMPP MENORX
Copy z, maior
menorx: 
copy x, menor
load menor
sub Y
jmpn menorz
copy y, MENOR
menorZ: load menor
sub Z
jmpn meiox
copy z, Menor
meiox: load X
ADD Y
ADD Z
sub MENOR
sub MAIOR
store meio
fim: output menor
output meio
output maior
jmp l1
secao dados
x: space
y: space
z: space
maior: space
meio: space
menor: space
