#include "Ast.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
//errorFlag=0;
const int table_max=200;

Symbol_node* head[200];

int no=1;

struct ast* newAstNode(char* token,int lineno){
	//printf("%s ",yytext);
	if(sizeof(yytext)!=0){
		lastText=curText;
		char* newS=(char*)malloc(sizeof(char*)*20);
		strcpy(newS,yytext);
		curText=newS;
		
		
	}
	struct ast* node=(struct ast*)malloc(sizeof(struct ast));
	node->data.binary.left=NULL;
	node->data.binary.right=NULL;

	if(node==NULL){
		yyerror("Out of space");
		exit(0);
	}
	node->token_name=token;
	node->line=lineno;
	if(strcmp(node->token_name,"ERROR_ID_TOO_LONG")==0 ){
		errorFlag=1;
		yyerror("ID_TOO_LONG");
	}else if( strcmp(node->token_name,"ERROR_INT_TOO_LONG")==0){
		errorFlag=1;
		yyerror("INT_TOO_LONG");
	}
	if(strcmp(node->token_name,"ERROR_UNDEFINED")==0){
		errorFlag=1;
		yyerror("undefined symbol");
		;
	}

	if(strcmp(node->token_name,"_ID")==0){
		char* idName=(char*)malloc(sizeof(char*)*20);
		strcpy(idName,yytext);
		node->id=idName;
		//foreach
		if(lastText!=NULL && strcmp(lastText,"foreach")==0){
			insert(idName,"LOCAL_DECAL","int",yylineno);
			return node;
		}
		//parameter id
		if(curFunc!=NULL&&lastText!=NULL && strcmp(lastText,"(")==0 ){
			insert(idName,"LOCAL_DECAL","tuple_or_int",yylineno);
			return node;
		}
		//array init
		if(lastText!=NULL && strcmp(lastText,"]")==0){
			insert(idName,"LOCAL_DECAL","int",yylineno);
			return node;
		}
		//ignore decal sentence
		if(lastText!=NULL && strcmp(lastText,"global")!=0 && strcmp(lastText,"local")!=0 && strcmp(lastText,"defun")!=0 && strcmp(lastText,"array")!=0){  
			int f=find(idName);
			if(f==0){
				yyerror("id is not defined");
				//printf("id: %s is not defined\n",yytext);
			}else if(f==2){
				//printf("using %s declared on line %d, %s %s\n",idName,yylineno,"LOCAL_DECAL","int");
			}
		}
	}else if(strcmp(node->token_name,"_INT")==0){
		node->int_lit=atoi(yytext);
	}
	
	
	//printf("%s",lastText);
	return node;
}

ast* combineNode(ast* stmts,ast* stmt){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="Seqs";
	node->type=binary;
	node->data.binary.left=stmts;
	node->data.binary.right=stmt;
	return node;
}

ast* newAstNode_One(char* token,ast* exp){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name=token;
	node->type=binary;
	node->data.binary.left=exp;
	node->data.binary.right=NULL;
	return node;
}
//ASSIGN
ast* newAstNode_Assign(ast* lhs,ast* exp){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="ASSIGN";
	node->type=binary;
	node->data.binary.left=lhs;
	node->data.binary.right=exp;
	return node;
}


ast* newAstNode_Operator(char* op,ast* exp1,ast* exp2){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name=op;
	node->type=binary;
	node->data.binary.left=exp1;
	node->data.binary.right=exp2;
	
	int result=checkType(exp1,exp2);
	if(result==2){
		yyerror("Operate wrong type");
	}
	return node;
}

ast* newAstNode_Par(ast* exp,ast* rightP){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="PAR";
	node->type=binary;
	char r[]="(";
	char *str = malloc(strlen(r) + 1);
	strcpy(str,r);
	strcat(str,exp->token_name);
	exp->token_name=str;
	node->data.binary.left=exp;
	rightP->token_name=")";
	node->data.binary.right=rightP;
	return node;
}

ast* newAstNode_Bracket(ast* id,ast* exp){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="BRACKET";
	node->type=binary;
	node->data.binary.left=id;
	node->data.binary.right=exp;
	return node;
}

ast* newAstNode_Dot(ast* id,ast* num){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="DOT";
	node->type=binary;
	node->data.binary.left=id;
	node->data.binary.right=num;
	return node;
}

ast* newAstNode_DotDot(ast* l,ast* r){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="DOTDOT";
	node->type=binary;
	node->data.binary.left=l;
	node->data.binary.right=r;
	return node;
}
ast* newAstNode_Comma(ast* lhs_items,ast* lhs_item){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="COMMA";
	node->type=binary;
	node->data.binary.left=lhs_items;
	node->data.binary.right=lhs_item;
	return node;
}
ast* newAstNode_While(ast* bool_expr,ast* _do){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="WHILE";
	node->type=binary;
	node->data.binary.left=bool_expr;
	node->data.binary.right=_do;
	return node;
}

ast* newAstNode_If(ast* bool_expr,ast* stmts,ast* elseif,ast* else_stmts){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="IF";
	node->type=if_stmt;
	node->data.if_stmt.bool_expr=bool_expr;

	node->data.if_stmt.stmts=stmts;
	if(elseif!=NULL)
		node->data.if_stmt.elseif=elseif;
	else
		node->data.if_stmt.elseif=NULL;
	if(else_stmts!=NULL)
		node->data.if_stmt.else_stmts=else_stmts;
	else
		node->data.if_stmt.else_stmts=NULL;
	return node;
}

ast* newAstNode_Elsif(ast* bool_expr,ast* then){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="ELSEIF";
	node->type=binary;
	node->data.binary.left=bool_expr;
	node->data.binary.right=then;
	return node;
}

ast* newAstNode_Foreach(ast* id,ast* for_in,ast* stmts){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="FOREACH";
	node->type=foreach_stmt;
	node->data.foreach_stmt.id=id;
	node->data.foreach_stmt.for_in=for_in;
	node->data.foreach_stmt.stmts=stmts;

	//insert(id->id,"LOCAL_DECAL","int",yylineno);
	return node;
}

ast* newAstNode_Decal(char* decl,ast* newId,ast* exp){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name=decl;
	node->type=binary;
	node->data.binary.left=newId;
	node->data.binary.right=exp;
	//if defined already
	if(find(newId->id)==1){
		yyerror("Already defined");
		return node;
	}
	if(find(newId->id)==2&&strcmp(decl,"LOCAL_DECAL")==1){
		yyerror("Already defined");
		return node;
	}
	/*if(find(newId->id)==2&&strcmp(decl,"LOCAL_DECAL")==0){

	}*/
	//decal local out of function
	if(curFunc==NULL&&strcmp(decl,"LOCAL_DECAL")==0){
		yyerror("Define local out of function");

		return node;
	}
	//tuple or int
	int insertReturn;
	//int
	
	if(exp==NULL || strcmp(exp->token_name,"_INT")==0|| strcmp(exp->token_name,"_ID")==0 || strcmp(exp->token_name,"+")==0 || strcmp(exp->token_name,"-")==0 || strcmp(exp->token_name,"*")==0 || strcmp(exp->token_name,"/")==0){
		insertReturn=insert(newId->id,decl,"int",yylineno);

	}
	//tuple
	else{
		int tupleNum=1;
		ast* tupleLevel=(ast*)malloc(sizeof(struct ast));
		tupleLevel=exp;
		//get tuple level
		while(tupleLevel->data.binary.right){
			tupleLevel=tupleLevel->data.binary.right;
			++tupleNum;
		}
		char tupleNumStr[10];
		sprintf(tupleNumStr,"%d",tupleNum);
		strcat(tupleNumStr,"-tuple");
		insertReturn=insert(newId->id,decl,tupleNumStr,yylineno);
	}

	return node;
}

ast* newAstNode_ArrayDecal(ast* array,ast* array_init){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="ARRAY_DECAL";
	node->type=binary;
	node->data.binary.left=array;
	node->data.binary.right=array_init;
	modify(array->data.binary.left->id,"array",yylineno);
	
	return node;
}
/*ast* newAstNode_TupleDecal(ast* tuple,ast* tuple_init){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="TUPLE_DECAL";
	node->type=binary;
	node->data.binary.left=tuple;
	node->data.binary.right=tuple_init;
	return node;
}
ast* combineTuple(ast* tuples,ast* tuple){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="Tuple";
	node->type=binary;
	node->data.binary.left=tuples;
	node->data.binary.right=tuple;
	return node;
}*/
ast* newAstNode_Func(ast* func_id,ast* parameters,ast* func_body){
	ast* node=(ast*)malloc(sizeof(struct ast));
	//printf("%s\n",curFunc);
	node->token_name="DEFUN";
	node->type=function;
	node->data.function.func_id=func_id;
	node->data.function.parameters=parameters;
	node->data.function.func_body=func_body;
	insert(func_id->id,"GLOBAL","DEFUN",yylineno);
	return node;
}

ast* newAstNode_Parameters(ast* paras,ast* para){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="PARAMETERS";
	node->type=binary;
	node->data.binary.left=paras;
	node->data.binary.right=para;
	return node;
}
ast* newAstNode_FuncCall(ast* func_id,ast* paras){
	ast* node=(ast*)malloc(sizeof(struct ast));
	node->token_name="FUNC_CALL";
	node->type=binary;
	node->data.binary.left=func_id;
	node->data.binary.right=paras;
	return node;
}
//---------------------------------------------

int setValue(char* id, char* scope,char* type, int value){
	int index=hashFun(id);
	Symbol_node* start=head[index];
	if(start==NULL){
		return 0;
	}
	while(start!=NULL){
		if(strcmp(start->identifier,id)==0){
			start->node_value.value=value;
			return 1;
		}
		start=start->next;
	}
	return 0;
}

int getValue(char* id,char*scope,char*type){
	//printf("123");
	int index=hashFun(id);
	Symbol_node* start=head[index];
	if(start==NULL){
		return 0;
	}
	while(start!=NULL){
		if(strcmp(start->identifier,id)==0){
			
			return start->node_value.value;
		}
		start=start->next;
	}
	return 0;
}


void preOrder(struct ast *node,int level){

	if(node==NULL){
		return;
	}

	for(int i=0;i<level;i++){
		printf("..");
	}
	if(node->line!=-1){
		printf("%s",node->token_name);
		if(strcmp(node->token_name,"_ID")==0){
			printf(":%s",node->id);
		}else if(strcmp(node->token_name,"_INT")==0){
			printf(":%d",node->int_lit);
		}else{

		}
	}
	printf("\n");
	if(node->type==binary){
		preOrder(node->data.binary.left,level+1);
		preOrder(node->data.binary.right,level+1);
	}else if(node->type==if_stmt){
		preOrder(node->data.if_stmt.bool_expr,level+1);
		preOrder(node->data.if_stmt.stmts,level+1);
		preOrder(node->data.if_stmt.elseif,level+1);
		preOrder(node->data.if_stmt.else_stmts,level+1);
	}else if(node->type==foreach_stmt){
		preOrder(node->data.foreach_stmt.id,level+1);
		preOrder(node->data.foreach_stmt.for_in,level+1);
		preOrder(node->data.foreach_stmt.stmts,level+1);
	}else if(node->type==function){
		preOrder(node->data.function.func_id,level+1);
		preOrder(node->data.function.parameters,level+1);
		preOrder(node->data.function.func_body,level+1);
	}
}

void printHead(){
	printf("; ModuleID = 'xxx.c'\nsource_filename = \"xxx.c\"\ntarget datalayout = \"e-m:o-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-apple-macosx10.12.0\"\n@.str = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\", align 1\n; Function Attrs: nounwind ssp uwtable\ndefine i32 @main() #0 {\n");
}

void printTail(){
	printf("ret i32 0\n");
	printf("}\n\n");
	printf("declare i32 @printf(i8*, ...) #1\n");
	printf("attributes #0 = { nounwind ssp uwtable \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"penryn\" \"target-features\"=\"+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n attributes #1 = { \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"penryn\" \"target-features\"=\"+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n");
	printf("!llvm.module.flags = !{!0}\n!llvm.ident = !{!1}\n!0 = !{i32 1, !\"PIC Level\", i32 2}\n!1 = !{!\"Apple LLVM version 8.1.0 (clang-802.0.42)\"}\n");
}

int exec(struct ast *node){
	if(strcmp(node->token_name,"Seqs")==0){
		exec(node->data.binary.left);
		exec(node->data.binary.right);
	}
	else if(strcmp(node->token_name,"GLOBAL_DECAL")==0){
		setValue(node->data.binary.left->id,"GLOBAL_DECAL","int",no);
		printf("%%%d = alloca i32, align 4\n",no);
		++no;
		int thisNo=getValue(node->data.binary.left->id,"GLOBAL_DECAL","int");
		printf("store i32 %%%d, i32* %%%d, align 4\n",exec(node->data.binary.right),thisNo);

	}
	else if(strcmp(node->token_name,"LOCAL_DECAL")==0){
		setValue(node->data.binary.left->id,"LOCAL_DECAL","int",no);
		printf("%%%d = alloca i32, align 4\n",no);
		++no;
		int thisNo=getValue(node->data.binary.left->id,"LOCAL_DECAL","int");
		printf("store i32 %%%d, i32* %%%d, align 4\n",exec(node->data.binary.right),thisNo);

	}
	else if(strcmp(node->token_name,"DEFUN")==0){
		
	}
	else if(strcmp(node->token_name,"ASSIGN")==0){
		//setValue(node->data.binary.left->id,"GLOBAL_DECAL","int",exec(node->data.binary.right));
		int thisNo=getValue(node->data.binary.left->id,"GLOBAL_DECAL","int");
		printf("store i32 %%%d, i32* %%%d, align 4\n",exec(node->data.binary.right),thisNo);
	}
	//IF
	else if(strcmp(node->token_name,"IF")==0){
		exec_if(node);
		return 0;
	}
	else if(strcmp(node->token_name,"WHILE")==0){
		exec_while(node);
		return 0;
	}
	//print
	else if(strcmp(node->token_name,"PRINT")==0){
		//printf("%d\n",exec(node->data.binary.left));
		int thisNo=exec(node->data.binary.left);
		//printf("%%%d = load i32, i32* %%%d, align 4\n",no,thisNo);
		printf("%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%%d)\n",no,thisNo);
		++no;
		
		return 0;
	// + - * /
	}else if(strcmp(node->token_name,"+")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = add nsw i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;
	}else if(strcmp(node->token_name,"-")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = sub nsw i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;
	}else if(strcmp(node->token_name,"*")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = mul nsw i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;
	}else if(strcmp(node->token_name,"/")==0){int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = sdiv i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;return exec(node->data.binary.left)/exec(node->data.binary.right);
	}
	else if(strcmp(node->token_name,"OP_GREATER")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = icmp sgt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_GREATEREQUAL")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = icmp sge i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_LESS")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = icmp slt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_LESSEQUAL")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = icmp sle i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_EQUAL")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = icmp eq i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_NOTEQUAL")==0){
		int left=exec(node->data.binary.left);
		int right=exec(node->data.binary.right);
		printf("%%%d = icmp ne i32 %%%d, %%%d\n",no,left,right);
	}
	else if(strcmp(node->token_name,"_INT")==0){
		printf("%%%d = alloca i32, align 4\n",no);
		printf("store i32 %d, i32* %%%d, align 4\n",node->int_lit,no);
		printf("%%%d = load i32, i32* %%%d, align 4\n",no+1,no);
		int returnNo=no+1;
		no++;no++;
		return returnNo;
	}else if(strcmp(node->token_name,"_ID")==0){
		int thisNo= getValue(node->id,"GLOBAL_DECAL","int");
		printf("%%%d = load i32, i32* %%%d, align 4\n",no,thisNo);
		no++;
		return no-1;
	}
	return 0;
}

int exec_without_print(struct ast *node){
	if(strcmp(node->token_name,"Seqs")==0){
		exec_without_print(node->data.binary.left);
		exec_without_print(node->data.binary.right);
	}
	else if(strcmp(node->token_name,"GLOBAL_DECAL")==0){
		setValue(node->data.binary.left->id,"GLOBAL_DECAL","int",no);
		//printf("%%%d = alloca i32, align 4\n",no);
		++no;
		//int thisNo=getValue(node->data.binary.left->id,"GLOBAL_DECAL","int");
		exec_without_print(node->data.binary.right);
		//printf("store i32 %%%d, i32* %%%d, align 4\n",exec(node->data.binary.right),thisNo);

	}else if(strcmp(node->token_name,"ASSIGN")==0){
		//setValue(node->data.binary.left->id,"GLOBAL_DECAL","int",exec(node->data.binary.right));
		//int thisNo=getValue(node->data.binary.left->id,"GLOBAL_DECAL","int");
		exec_without_print(node->data.binary.right);
		//printf("store i32 %%%d, i32* %%%d, align 4\n",exec(node->data.binary.right),thisNo);
	}
	//IF
	else if(strcmp(node->token_name,"IF")==0){
		exec_if_without_print(node);
		return 0;
	}
	else if(strcmp(node->token_name,"WHILE")==0){
		exec_while_without_print(node);
		return 0;
	}
	//print
	else if(strcmp(node->token_name,"PRINT")==0){
		//printf("%d\n",exec(node->data.binary.left));
		int thisNo=exec_without_print(node->data.binary.left);
		//printf("%%%d = load i32, i32* %%%d, align 4\n",no,thisNo);
		//printf("%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%%d)\n",no,thisNo);
		++no;
		
		return 0;
	// + - * /
	}else if(strcmp(node->token_name,"+")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = add nsw i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;
	}else if(strcmp(node->token_name,"-")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = sub nsw i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;
	}else if(strcmp(node->token_name,"*")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = mul nsw i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;
	}else if(strcmp(node->token_name,"/")==0){int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = sdiv i32 %%%d, %%%d\n",no,left,right);
		no++;
		return no-1;return exec_without_print(node->data.binary.left)/exec_without_print(node->data.binary.right);
	}

	else if(strcmp(node->token_name,"OP_GREATER")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = icmp sgt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_GREATEREQUAL")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = icmp sge i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_LESS")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = icmp slt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_LESSEQUAL")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = icmp sle i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_EQUAL")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = icmp eq i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->token_name,"OP_NOTEQUAL")==0){
		int left=exec_without_print(node->data.binary.left);
		int right=exec_without_print(node->data.binary.right);
		//printf("%%%d = icmp ne i32 %%%d, %%%d\n",no,left,right);
	}

	else if(strcmp(node->token_name,"_INT")==0){
		/*printf("%%%d = alloca i32, align 4\n",no);
		printf("store i32 %d, i32* %%%d, align 4\n",node->int_lit,no);
		printf("%%%d = load i32, i32* %%%d, align 4\n",no+1,no);*/
		int returnNo=no+1;
		no++;no++;
		return returnNo;
	}else if(strcmp(node->token_name,"_ID")==0){
		int thisNo= getValue(node->id,"GLOBAL_DECAL","int");
		//printf("%%%d = load i32, i32* %%%d, align 4\n",no,thisNo);
		no++;
		return no-1;
	}
	return 0;
}

int exec_elsif(ast* node){
	if(strcmp(node->token_name,"Seqs")==0){
		//printf("xx\n");
		if(exec_elsif(node->data.binary.left)==1)
			return 1;
		if(exec_elsif(node->data.binary.right)==1)
			return 1;

	}
	else{
		if((strcmp(node->data.binary.left->token_name,"OP_GREATER")==0 && exec(node->data.if_stmt.bool_expr->data.binary.left)>exec(node->data.if_stmt.bool_expr->data.binary.right))
			||(strcmp(node->data.binary.left->token_name,"OP_LESS")==0 && exec(node->data.if_stmt.bool_expr->data.binary.left)<exec(node->data.if_stmt.bool_expr->data.binary.right))
			||(strcmp(node->data.binary.left->token_name,"OP_GREATEREQUAL")==0 && exec(node->data.if_stmt.bool_expr->data.binary.left)>=exec(node->data.if_stmt.bool_expr->data.binary.right))
			||(strcmp(node->data.binary.left->token_name,"OP_LESSEQUAL")==0 && exec(node->data.if_stmt.bool_expr->data.binary.left)<=exec(node->data.if_stmt.bool_expr->data.binary.right))
			||(strcmp(node->data.binary.left->token_name,"OP_EQUAL")==0 && exec(node->data.if_stmt.bool_expr->data.binary.left)==exec(node->data.if_stmt.bool_expr->data.binary.right))
			||(strcmp(node->data.binary.left->token_name,"OP_NOTEQUAL")==0 && exec(node->data.if_stmt.bool_expr->data.binary.left)!=exec(node->data.if_stmt.bool_expr->data.binary.right))
			){
				exec(node->data.binary.right);
				return 1;
		}
	}
	return 0;
}

int exec_if(struct ast* node){
	int label1;//if
	int label2;//else
	int label3;//out
	if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_GREATER")==0){
		int left=exec(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec(node->data.if_stmt.bool_expr->data.binary.right);
		printf("%%%d = icmp sgt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_GREATEREQUAL")==0){
		int left=exec(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec(node->data.if_stmt.bool_expr->data.binary.right);
		printf("%%%d = icmp sge i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_LESS")==0){
		int left=exec(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec(node->data.if_stmt.bool_expr->data.binary.right);
		printf("%%%d = icmp slt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_LESSEQUAL")==0){
		int left=exec(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec(node->data.if_stmt.bool_expr->data.binary.right);
		printf("%%%d = icmp sle i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_EQUAL")==0){
		int left=exec(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec(node->data.if_stmt.bool_expr->data.binary.right);
		printf("%%%d = icmp eq i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_NOTEQUAL")==0){
		int left=exec(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec(node->data.if_stmt.bool_expr->data.binary.right);
		printf("%%%d = icmp ne i32 %%%d, %%%d\n",no,left,right);
	}
	no++;
	label1=no;

	int latestNo=no-1;
	exec_without_print(node->data.if_stmt.stmts);
	no++;
	
	if(node->data.if_stmt.else_stmts!=NULL){
		label2=no;
		exec_without_print(node->data.if_stmt.else_stmts->data.binary.left);
		no++;
		label3=no;
		no=latestNo;
		printf("br i1 %%%d, label %%%d, label %%%d\n",no,label1,label2);
	}
	else{
		label3=no;
		no=latestNo;
		printf("br i1 %%%d, label %%%d, label %%%d\n",no,label1,label3);
	}
	no=no+2;

	printf("\n; <label>:%d:                                      ; preds = %%0\n",label1);
	exec(node->data.if_stmt.stmts);
	printf(" br label %%%d\n",label3);
	++no;
	if(node->data.if_stmt.else_stmts!=NULL){
		printf("\n; <label>:%d:                                      ; preds = %%0\n",label2);
		exec(node->data.if_stmt.else_stmts->data.binary.left);
		printf(" br label %%%d\n\n",label3);
		++no;
	}
	
	printf("\n; <label>:%d:                                      ; preds = %%%d, %%%d\n",label3,label2,label1);
	return 0;
	
}

int exec_if_without_print(ast* node){
	int label1;//if
	int label2;//else
	int label3;//out
	if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_GREATER")==0){
		int left=exec_without_print(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec_without_print(node->data.if_stmt.bool_expr->data.binary.right);
		//printf("%%%d = icmp sgt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_GREATEREQUAL")==0){
		int left=exec_without_print(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec_without_print(node->data.if_stmt.bool_expr->data.binary.right);
		//printf("%%%d = icmp sge i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_LESS")==0){
		int left=exec_without_print(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec_without_print(node->data.if_stmt.bool_expr->data.binary.right);
		//printf("%%%d = icmp slt i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_LESSEQUAL")==0){
		int left=exec_without_print(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec_without_print(node->data.if_stmt.bool_expr->data.binary.right);
		//printf("%%%d = icmp sle i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_EQUAL")==0){
		int left=exec_without_print(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec_without_print(node->data.if_stmt.bool_expr->data.binary.right);
		//printf("%%%d = icmp eq i32 %%%d, %%%d\n",no,left,right);
	}else if(strcmp(node->data.if_stmt.bool_expr->token_name,"OP_NOTEQUAL")==0){
		int left=exec_without_print(node->data.if_stmt.bool_expr->data.binary.left);
		int right=exec_without_print(node->data.if_stmt.bool_expr->data.binary.right);
		//printf("%%%d = icmp ne i32 %%%d, %%%d\n",no,left,right);
	}
	no++;
	label1=no;

	int latestNo=no-1;
	exec_without_print(node->data.if_stmt.stmts);
	no++;
	
	if(node->data.if_stmt.else_stmts!=NULL){
		label2=no;
		exec_without_print(node->data.if_stmt.else_stmts->data.binary.left);
		no++;
		label3=no;
		no=latestNo;
		//printf("br i1 %%%d, label %%%d, label %%%d\n",no,label1,label2);
	}
	else{
		label3=no;
		no=latestNo;
		//printf("br i1 %%%d, label %%%d, label %%%d\n",no,label1,label3);
	}
	no=no+2;

	//printf("\n; <label>:%d:                                      ; preds = %%0\n",label1);
	exec_without_print(node->data.if_stmt.stmts);
	//printf(" br label %%%d\n",label3);
	++no;
	if(node->data.if_stmt.else_stmts!=NULL){
		//printf("\n; <label>:%d:                                      ; preds = %%0\n",label2);
		exec_without_print(node->data.if_stmt.else_stmts->data.binary.left);
		//printf(" br label %%%d\n\n",label3);
		++no;
	}
	
	//printf("\n; <label>:%d:                                      ; preds = %%%d, %%%d\n",label3,label2,label1);
	return 0;
}

int exec_while(ast* node){
	int label1=no;
	int label2;
	int label3;
	printf("br label %%%d\n\n",label1);
	int latestNo=no;
	exec_without_print(node->data.binary.left);
	no=no+2;
	label2=no;
	
	printf("; <label>:%d:                                      ; preds = %%%d, %%0\n",label1,label2);
	no++;
	exec_without_print(node->data.binary.right);
	label3=no;
	no=latestNo;
	no++;
	exec(node->data.binary.left);
	printf("br i1 %%%d, label %%%d, label %%%d\n\n",no,label2,label3);
	no++;
	printf("; <label>:%d:                                      ; preds = %%%d\n",label2,label1);
	no++;
	exec(node->data.binary.right);

	printf("br label %%%d\n\n",label1);
	printf("; <label>:%d:                                     ; preds = %%%d\n",label3,label1);
	no++;
	return 0;
}

int exec_while_without_print(ast* node){
	int label1=no;
	int label2;
	int label3;
	//printf("br label %%%d\n\n",label1);
	int latestNo=no;
	exec_without_print(node->data.binary.left);
	no=no+2;
	label2=no;
	
	//printf("; <label>:%d:                                      ; preds = %%%d, %%0\n",label1,label2);
	no++;
	exec_without_print(node->data.binary.right);
	label3=no;
	no=latestNo;
	no++;
	exec_without_print(node->data.binary.left);
	//printf("br i1 %%%d, label %%%d, label %%%d\n\n",no,label2,label3);
	no++;
	//printf("; <label>:%d:                                      ; preds = %%%d\n",label2,label1);
	no++;
	exec_without_print(node->data.binary.right);

	//printf("br label %%%d\n\n",label1);
	//printf("; <label>:%d:                                     ; preds = %%%d\n",label3,label1);
	no++;
	return 0;
}

int GetErrorFlag(){
	return errorFlag;
}
char* Get_LastText(){
	return lastText;
}
void Set_LastText(char* s){
	//printf("%s ",s);
	lastText=s;
}
char* Get_CurText(){
	return curText;
}
void Set_CurText(char* s){
	curText=s;
}


void Set_CurFunc(char* funcId){
	if(funcId==NULL){
		curFunc=NULL;
		return;
	}
	char* idName=(char*)malloc(sizeof(char*)*20);
	strcpy(idName,funcId);
	curFunc=idName;
	//printf("%s\n",curFunc);
}


//------------------
int hashFun(const char* id){
	int sum=0;
	for(size_t i=0;i<sizeof(id);++i){
		sum=sum+id[i];
	}
	return (sum%100);
}

int find(const char* id){
	//printf("%s\n",id);
	int index=hashFun(id);
	Symbol_node* start=head[index];

	if(start==NULL){
		return 0;
	}
	//id in global scope  
	if(curFunc==NULL){
		while(start!=NULL){
			if(strcmp(start->identifier,id)==0 && start->func==NULL){
				//printf("func:%s\n",start->func);
				//printf("using %s declared on line %d, %s %s\n",start->identifier,start->lineNo,start->scope,start->type);
				return 1;
			}
			start=start->next;
		}
	}
	//id in a function
	else{
		while(start!=NULL){
			
			if(strcmp(start->identifier,id)==0 && start->func==NULL){   //if global
				return 2;
			}
			if(strcmp(start->identifier,id)==0 && start->func!=NULL&&strcmp(start->func,curFunc)==0){   //if local
				//printf("using %s declared on line %d, %s %s\n",start->identifier,start->lineNo,start->scope,start->type);
				return 1;
			}
			start=start->next;
		}
	}
	return 0;
}
//1.int  2.array  3.tuple
int findGetType(const char* id){
	int index=hashFun(id);
	Symbol_node* start=head[index];

	if(start==NULL){
		return 0;
	}
	  
	while(start!=NULL){
		if(strcmp(start->identifier,id)==0){
			//printf("func:%s\n",start->func);
			if(strcmp(start->type,"int")==0){
				return 1;
			}else if(strcmp(start->type,"array")==0){
				return 2;
			}else{
				return 3;
			}
			
		}
		start=start->next;
	}
	
	
	return 0;
}

int insert(char* id,char* scope,char* type,const int lineno){
	//"a": local tuple with 7 elements declared on line 33
	int index=hashFun(id);
	struct Symbol_node* p=(struct Symbol_node*)malloc(sizeof(struct Symbol_node));
	char* typeName=(char*)malloc(sizeof(char*)*20);
	strcpy(typeName,type);
	p->identifier=id;
	p->scope=scope;

	p->type=typeName;
	p->next=NULL;
	p->lineNo=lineno;
	// in which func or global
	if(strcmp(scope,"LOCAL_DECAL")==0){
		char* funcName=(char*)malloc(sizeof(char*)*20);
		if(curFunc!=NULL)
			strcpy(funcName,curFunc);
		p->func=funcName;
		if(strcmp(funcName,"")==0)
			p->func=NULL;
		
	}else{
		p->func=NULL;
	}
	//printf("type:%s\n",p->type);
	if(head[index]==NULL){
		head[index]=p;
		//printf("%s: %s %s on line %d\n",id,scope,type,lineno);
		
		return 1;
	}else{
		Symbol_node* start=head[index];
		while(start->next!=NULL){
			start=start->next;
		}
		start->next=p;
		printf("%s: %s %s on line %d\n",id,scope,type,lineno);

		return 1;
	}
	return 0;
}  

//for array
int modify(char* id,char* type,int lineno){
	int index=hashFun(id);
	Symbol_node* start=head[index];
	if(start==NULL){
		return 0;
	}
	while(start!=NULL){
		if(strcmp(start->identifier,id)==0){
			start->type=type;
			start->lineNo=lineno;
			printf("%s: %s %s on line %d\n",id,start->scope,type,lineno);
			return 1;
		}
		start=start->next;
	}

	return 1;
}
//0 : not defined   1: can do 2: can not 
int checkType(ast* A,ast* B){
	ast* node=(ast*)malloc(sizeof(struct ast));
	int typeA;
	int typeB;
	node=A;
	//printf("s:%s\n",node->token_name);
	if(strcmp(node->token_name,"_ID")==0)
		typeA=findGetType(node->id);
	else
		typeA=1;
	node=B;
	//printf("s:%s\n",node->token_name);
	if(strcmp(node->token_name,"_ID")==0)
		typeB=findGetType(node->id);
	else 
		typeB=1;
	if(typeA==0 || typeB==0){
		return 0;
	}
	if(typeA==typeB){
		return 1;
	}
	return 2;
}



void InitTable(){
	for(size_t i=0;i<table_max;++i){
		head[i]=NULL;
	}
} 

void yyerror(char* message,...){
	
	fprintf(stderr, "ERROR: %s (%s at line:%d, start at:%d, end at:%d)\n", message ,yytext,yylineno,position,nextPosition);
	

	errorFlag=1;
	
}
