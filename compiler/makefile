main: 
	bison -d fb.y
	flex fb.l
	gcc fb.tab.c lex.yy.c Ast.c -o fd820
	#clang fb.tab.c lex.yy.c Ast.c -S -emit -llvm
	 
	
