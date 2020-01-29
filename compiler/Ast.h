//extern char* name;
#ifndef AST_H
#define AST_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

extern int yylineno;
extern char* yytext;
extern int position;
extern int nextPosition;
static char* lastText;
static char* curText;
static char* fileName;

static char* curFunc;


//int errorFlag;
static int errorFlag=0;
typedef enum union_type{binary,if_stmt,foreach_stmt,function} union_type;

typedef struct ast{

	int line;
	char* token_name;
	union_type type;  //define union type  : 1 for two; 2 for if_stmt
	union{
		struct{
			struct ast * left;
			struct ast * right;
		}binary;
		struct{
			struct ast* bool_expr;
			struct ast* stmts;
			struct ast* elseif;
			struct ast* else_stmts;
		}if_stmt;
		struct{
			struct ast* id;
			struct ast* for_in;
			struct ast* stmts;
		}foreach_stmt;
		struct{
			struct ast* func_id;
			struct ast* parameters;
			struct ast* func_body;
		}function;
	}data;
	union{
		int int_lit;
		char* id;
	};
}ast;


typedef struct Symbol_node{
	char* identifier;
	char* scope;
	char* type;
	int lineNo;
	char* func;
	struct Symbol_node* next;
	union{
		int value;

	}node_value;
}Symbol_node;



//symbol talbe's function
int hashFun(const char* id);
int find(const char*);
int insert(char* id,char* scope,char* type,const int lineno);  //actually return bool type
int modify(char* id,char* type, const int lineno);
int setValue(char* id, char* scope,char* type, int value);
int getValue(char* id,char*scope,char*type);
void InitTable();
int checkType(ast* A,ast* B);
int findGetType(const char* id);




ast* newAstNode(char* name,int lineno);  //1,tokenName;2,argNum;3,lineNo
ast* combineNode(ast* stmts,ast* stmt);
ast* newAstNode_One(char* name,ast* exp);
ast* newAstNode_Assign(ast* lhs,ast* exp);
ast* newAstNode_Operator(char* op,ast* exp1,ast* exp2);  //+-*/
ast* newAstNode_Par(ast* exp,ast* rightP); //  ()
ast* newAstNode_Bracket(ast* id,ast* exp);
ast* newAstNode_Dot(ast* id,ast* num);
ast* newAstNode_DotDot(ast* l,ast* r);
ast* newAstNode_Comma(ast* lhs_items,ast* lhs_item);
ast* newAstNode_While(ast* bool_expr,ast* _do);
ast* newAstNode_If(ast* bool_expr,ast* stmts,ast* elseif,ast* else_stmts);
ast* newAstNode_Elsif(ast* bool_expr,ast* then);
ast* newAstNode_Foreach(ast* id,ast* for_in,ast* stmts);
ast* newAstNode_Decal(char* decl,ast* id,ast* exp);
ast* newAstNode_ArrayDecal(ast* array,ast* array_init);
//ast* newAstNode_TupleDecal(ast* tuple,ast* tuple_init);
//ast* combineTuple(ast* tuples,ast* tuple); 
ast* newAstNode_Func(ast* func_id,ast* parameters,ast* func_body);
ast* newAstNode_Parameters(ast* paras,ast* para);
ast* newAstNode_FuncCall(ast* id,ast* para);
void preOrder(ast *node,int level);


void printHead();
void printTail();

int exec(ast *node);
int exec_without_print(ast *node);
int exec_if(ast* node);
int exec_if_without_print(ast* node);
int exec_while(ast* node);
int exec_while_without_print(ast* node);
int exec_elsif(ast* node);
int GetErrorFlag();
char* Get_LastText();
void Set_LastText(char* s);
char* Get_CurText();
void Set_CurText(char* s);

void Set_CurFunc(char* funcId);


void yyerror(char* s,...);


#endif


