reset
yacc ass3-1.y -v
lex ass3.l
# reset
g++ --std=c++1y y.tab.c lex.yy.c
./a.out < in.c