prefixer: lex.yy.c
	g++ -o prefixer expr_tree.cpp visitor.cpp lex.yy.c expr_bison.tab.cpp main.cpp

lex.yy.c: parser.tab.hpp
	flex expr_lex.l

parser.tab.hpp:
	bison -d expr_bison.ypp

clean:
	rm -f lex.yy.c expr_bison.tab.cpp expr_bison.tab.hpp prefixer
