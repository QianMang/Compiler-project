%{
    #include "fb.tab.h"
    #include "Ast.h"
    int position=1;
	int nextPosition=1;
	//char* lastText="";
	int length=0;
	extern int idLength;

	const int INT_limit=2147483647;
	const int ID_limit=20;
%}
%option yylineno

KW_ARRAY array
KW_TUPLE tuple
KW_GLOBAL global
KW_LOCAL local
KW_DEFUN defun
KW_END end
KW_WHILE while
KW_DO do
KW_IF if
KW_THEN then
KW_ELSIF elsif
KW_ELSE else
KW_FOREACH foreach
KW_FOR for
KW_IN in
RETURN return
PRINT print

DOT [.]
DOTDOT [.][.]

COMMA [,]
SEMI [;]
ASSIGN [=]
OP_EXCHANGE [<][-][>]
OP_LESS [<]
OP_GREATER [>]
OP_LESSEQUAL [<][=]
OP_GREATEREQUAL [>][=]
OP_EQUAL [=][=]
OP_NOTEQUAL [!][=]
OP_PLUS [+]
OP_MINUS [-]
OP_MULT [*]
OP_DIV [/]


LBRAK \[
RBRAK \]
LPAR \(
RPAR \)

LINE [\n]
SPACE [ \t]*

_ID [a-zA-Z_]+
_INT [0-9]*

ERROR .


%%
{KW_ARRAY} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_ARRAY",yylineno); 
	return KW_ARRAY;
}
{KW_TUPLE} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_TUPLE",yylineno); 
	return KW_TUPLE;
}

{KW_GLOBAL} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_GLOBAL",yylineno); 
	return KW_GLOBAL;
}

{KW_LOCAL} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_LOCAL",yylineno); 
	return KW_LOCAL;
}

{KW_DEFUN} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_DEFUN",yylineno); 
	return KW_DEFUN;
}

{KW_END} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_END",yylineno); 
	return KW_END;
}

{KW_WHILE} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_WHILE",yylineno); 
	return KW_WHILE;
}

{KW_DO} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_DO",yylineno); 
	return KW_DO;
}

{KW_IF} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_IF",yylineno); 
	return KW_IF;
}

{KW_THEN} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_THEN",yylineno); 
	return KW_THEN;
}

{KW_ELSIF} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_ELSIF",yylineno); 
	return KW_ELSIF;
}

{KW_ELSE} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_ELSE",yylineno); 
	return KW_ELSE;
}

{KW_FOREACH} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_FOREACH",yylineno); 
	return KW_FOREACH;
}
{KW_FOR} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_FOR",yylineno); 
	return KW_FOR;
}


{KW_IN} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("KW_IN",yylineno); 
	return KW_IN;
}

{RETURN} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("RETURN",yylineno); 
	return RETURN;
}

{PRINT} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("PRINT",yylineno); 
	return PRINT;
}


{DOT} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("DOT",yylineno); 
	return DOT;
}

{DOTDOT} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("DOTDOT",yylineno); 
	return DOTDOT;
}


{COMMA} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("COMMA",yylineno); 
	return COMMA;	
}

{SEMI} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("SEMI",yylineno); 
	return SEMI;
}

{ASSIGN} {

	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("ASSIGN",yylineno); 
	return ASSIGN;
}

{OP_EXCHANGE} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_EXCHANGE",yylineno); 
	return OP_EXCHANGE;
}

{OP_LESS} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_LESS",yylineno); 
	return OP_LESS;
}

{OP_GREATER} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_GREATER",yylineno); 
	return OP_GREATER;
}

{OP_LESSEQUAL} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_LESSEQUAL",yylineno); 
	return OP_LESSEQUAL;
}

{OP_GREATEREQUAL} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_GREATEREQUAL",yylineno); 
	return OP_GREATEREQUAL;

}

{OP_EQUAL} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_EQUAL",yylineno); 
	return OP_EQUAL;
}

{OP_NOTEQUAL} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_NOTEQUAL",yylineno); 
	return OP_NOTEQUAL;
}

{OP_PLUS}    {
    position=nextPosition;
	nextPosition+=yyleng;

	yylval.node=newAstNode("OP_PLUS",yylineno);      //
	return OP_PLUS; 
}

{OP_MINUS}    { 
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_MINUS",yylineno); 
	return OP_MINUS; 
}
{OP_MULT}     { 
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_PLUS",yylineno); 
	return OP_MULT; 
}
{OP_DIV}      { 
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("OP_DIV",yylineno); 
	return OP_DIV; 
}

{LBRAK} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("LBRAK",yylineno); 
	return LBRAK;
}

{RBRAK} {
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("RBRAK",yylineno); 
	return RBRAK;
}

{LPAR}        { 
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("LPAR",yylineno); 
	return LPAR; 
}
{RPAR}        { 
	position=nextPosition;
	nextPosition+=yyleng;
	yylval.node=newAstNode("RPAR",yylineno); 
	return RPAR; 
}

{SPACE} {
	position=nextPosition;
	nextPosition+=yyleng;
}

{LINE} {
	position=1;
	nextPosition=1;
	
}

{_INT}    { 
	position=nextPosition;
	nextPosition+=yyleng;
	if(atoi(yytext)<=INT_limit && atoi(yytext)>=0 && yyleng<11){
		yylval.node=newAstNode("_INT",yylineno); 
		return _INT; 
	}
	
	
	yylval.node=newAstNode("ERROR_INT_TOO_LONG",yylineno);
	return _INT;
	

	

}
{_ID} {
	//printf("%s\n",yytext);
	position=nextPosition;
	nextPosition+=yyleng;
	if(yyleng>=ID_limit){
		yylval.node=newAstNode("ERROR_ID_TOO_LONG",yylineno);
		return _ID;
	}

	if(Get_LastText()!=NULL){
		if(strcmp(Get_CurText(),"defun")==0){
			char* idName=(char*)malloc(sizeof(char*)*20);
			strcpy(idName,yytext);
			Set_CurFunc(idName);
		}
	}
	yylval.node=newAstNode("_ID",yylineno);

	return _ID;
}

"***".*  {
	position=nextPosition;
	nextPosition=1;
}
<<EOF>> {
	return _EOF;
}

.    { 
	yylval.node=newAstNode("ERROR_UNDEFINED",yylineno); /*yyerror("Mystery character %c\n", *yytext); */
}
%%
int yywrap() { return 1; }









