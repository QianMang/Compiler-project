%{
	
	#include "Ast.h"
	# include <stdio.h>
	# include <stdlib.h>
	# include <string.h>
	# include <stdarg.h>
	
	extern int yylex();
	extern FILE *yyin;
	//extern int errorFlag;
	int symbolVal(int symbol);
	int updateSymbolVal(int symbol,int val);
	
	struct Identifier{
		char symbol[20];
		int val;
	};
	struct Identifier id[100];
	int curIndex=0;
	int idLength=0;
%}

/* declare tokens */

%union {struct ast* node;}


%token <node> _INT _ID
%token <node> OP_PLUS OP_MINUS OP_MULT OP_DIV
%token <node> DOT DOTDOT COMMA SEMI ASSIGN 
%token <node> OP_EXCHANGE OP_LESS OP_GREATER OP_LESSEQUAL OP_GREATEREQUAL OP_EQUAL OP_NOTEQUAL
%token <node> KW_ARRAY KW_TUPLE KW_GLOBAL KW_LOCAL KW_DEFUN KW_END KW_WHILE KW_DO
%token <node> KW_IF KW_THEN KW_ELSIF KW_ELSE 
%token <node> KW_FOREACH KW_IN KW_FOR
%token <node> LPAR RPAR LBRAK RBRAK
%token <node> PRINT RETURN
%token <node> _EOF


%type <node> program input stmts stmt decl defn bool-expr bool-op lhs lhs_item lhs_items _elseif _else for_in assign_init array_init parameters func_body exp
%start program


%%
program: input 				{$$=$1;}
	;

input: input stmt           {$$=combineNode($1,$2);}
	| input decl            {$$=combineNode($1,$2);}
	| input defn            {$$=combineNode($1,$2);}
	| input _EOF 			{	//printf("-------------------------------------\n");
								if(GetErrorFlag()==0){
									//preOrder($$,0);
									//printf("-------------------------------------\n");
									printHead();
									exec($$);
									printTail();
									//printf("-------------------------------------\n");
									//printf("SUCCESS\n");
									//printf("-------------------------------------\n");
								}
								return 0;
							}      //EOF
	| stmt                  {$$=$1;}
	| decl                  {$$=$1;}
	| defn                  {$$=$1;}
	| error 				{/*printf("error happen here\n");*/}
	;

stmts: stmts stmt           {$$=combineNode($1,$2);}
	| stmt                  {$$=$1;}
	;
//--------------------
stmt: lhs ASSIGN exp SEMI             	{$$=newAstNode_Assign($1,$3);}  //assignment
	| lhs OP_EXCHANGE lhs SEMI          {$$=newAstNode_Operator("OP_EXCHANGE",$1,$3);}
	| PRINT exp SEMI					{$$=newAstNode_One("PRINT",$2);}
	| RETURN exp SEMI                   {$$=newAstNode_One("RETURN",$2);}
	| KW_WHILE bool-expr KW_DO stmts KW_END KW_WHILE               {$$=newAstNode_While($2,$4);}
	| KW_IF bool-expr KW_THEN stmts _elseif _else KW_END KW_IF     {$$=newAstNode_If($2,$4,$5,$6);}
	| KW_FOREACH _ID KW_IN for_in KW_DO stmts KW_END KW_FOR        {$$=newAstNode_Foreach($2,$4,$6);}
	;

bool-expr: exp bool-op exp              {$$=newAstNode_Operator($2->token_name,$1,$3);}
	;


bool-op: OP_LESS                        {$$=$1;}
	|OP_GREATER           				{$$=$1;}
	|OP_LESSEQUAL        				{$$=$1;}
	|OP_GREATEREQUAL       				{$$=$1;}
	|OP_EQUAL     						{$$=$1;}
	|OP_NOTEQUAL         				{$$=$1;}
	;

//left hand side
lhs : lhs_items                         {$$=$1;}
	;

lhs_item :                              {$$=0;}
	| _ID                               {$$=$1;}
	| _ID DOT _INT                      {$$=newAstNode_Dot($1,$3);}  //tuple
	| _ID LBRAK exp RBRAK               {$$=newAstNode_Bracket($1,$3);}   //array
	;
lhs_items: lhs_item                     {$$=$1;}
	| lhs_items COMMA lhs_item          {$$=newAstNode_Comma($1,$3);}
	;

_elseif:                                           {$$=0;}
	| _elseif KW_ELSIF bool-expr KW_THEN stmts     {$$=combineNode($1,newAstNode_Elsif($3,$5));}
	| KW_ELSIF bool-expr KW_THEN stmts             {$$=newAstNode_Elsif($2,$4);}
	;
_else:     								{$$=0;}
	| KW_ELSE stmts 					{$$=newAstNode_One("ELSE",$2);}
	;

for_in: _ID   							{$$=$1;}
	| exp DOTDOT exp 					{$$=newAstNode_DotDot($1,$3);}
	;
//----------------------
decl: KW_ARRAY _ID LBRAK exp DOTDOT exp RBRAK array_init SEMI      {$$=newAstNode_ArrayDecal(newAstNode_Bracket($2,newAstNode_DotDot($4,$6)),$8);}
	| KW_LOCAL _ID assign_init SEMI		                           {$$=newAstNode_Decal("LOCAL_DECAL",$2,$3);}
	| KW_GLOBAL _ID assign_init SEMI		      			  	   {$$=newAstNode_Decal("GLOBAL_DECAL",$2,$3);}
	;

array_init:     						{$$=0;}
	| _ID ASSIGN exp   					{$$=newAstNode_Assign($1,$3);}
	;

assign_init:							{$$=0;}
	| ASSIGN exp 						{$$=$2;}
	;

//---------------------
defn: KW_DEFUN _ID LPAR parameters RPAR func_body KW_END KW_DEFUN     {$$=newAstNode_Func($2,$4,$6);Set_CurFunc(NULL);}
	;	

parameters:                             {$$=0;}
	|  _ID  							{$$=newAstNode_Parameters($1,NULL);}
//	| parameters COMMA _ID              {$$=newAstNode_Parameters($1,$3);}
	;   

func_body: func_body stmt   			{$$=combineNode($1,$2);}
	| func_body decl 					{$$=combineNode($1,$2);}
	| stmt   							{$$=$1;}
	| decl 								{$$=$1;}
	;



exp: _INT				           {$$=$1;}
	 | exp COMMA exp               {$$=newAstNode_Operator(",",$1,$3);}
	 | exp OP_MULT exp             {$$=newAstNode_Operator("*",$1,$3);}
	 | exp OP_DIV exp  			   {$$=newAstNode_Operator("/",$1,$3);}
	 | exp OP_PLUS exp			   {$$=newAstNode_Operator("+",$1,$3);}
	 | exp OP_MINUS exp  	       {$$=newAstNode_Operator("-",$1,$3);}
	 | LPAR exp RPAR 		       {$$=newAstNode_Par($2,$3);}
	 | _ID						   {$$=$1;}
	 | _ID exp                     {$$=newAstNode_FuncCall($1,$2);}
	 | _ID DOT _INT                {$$=newAstNode_Dot($1,$3);}
	 | _ID LBRAK exp RBRAK         {$$=newAstNode_Bracket($1,$3);}
	 ;

 
%%

/*



*/



int main(int argc,char** argv)
{
  //printf("-------------------------------------\n");
  if (argc == 1){
    yyparse();
    
  }
  else if(argc == 2) {
  	fileName=argv[2];
  	FILE* f=fopen(argv[1], "r");
  	if(f==NULL){
  		printf("file is not exist\n");
  		return 0;
  	}
    yyin = f;
    InitTable();
    yyparse();
    
  }
}

