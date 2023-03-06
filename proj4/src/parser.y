%locations
%{
#include <stdio.h>
#include <string.h>
#include "./dataset.h"
#include "lex.yy.c"
// #define YYDEBUG 1

//  #define YY_USER_ACTION                                  \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn;                  \
        yylloc.last_column = yycolumn + yyleng - 1;      \
        yycolumn += yyleng;


int yylex(void);
void yyerror(char *);

TNode* AST__ = NULL;
unsigned syn_error = 0;

// .y文件进行语法分析，通过产生式匹配，如果当前行匹配成功执行后面的函数
%}


%union{
  TNode* t_node;
}
%token <t_node> TYPE STRUCT RETURN IF ELSE WHILE ID SEMI COMMA RELOP
%token <t_node> ASSIGNOP PLUS MINUS STAR DIV AND OR DOT NOT LP RP LB RB LC RC
%token <t_node> INT
%token <t_node> FLOAT

// Precedence and combination rule
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left MINUS PLUS
%left DIV STAR
%right NOT
%left UMINUS
%left DOT LB RB LP RP

/*declare non-terminals*/
%type <t_node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec
%type <t_node> CompSt StmtList Stmt DefList DecList Def Dec Exp Args


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE



/* %type  <inum> expression term single */

%%
        // High-level Definations
        Program: ExtDefList                 { $$ = new_tnode($1?($1)->no_line:0, Program_, NULL); add_child($$, $1); if(lex_error == 0 && syn_error == 0) AST__ = $$; }
        ;
        ExtDefList: ExtDef ExtDefList       { $$ = new_tnode(($1)->no_line, ExtDefList_, NULL); add_child($$, $1); add_child( $$,  $2);}
        |                                   { $$ = NULL;}
        ;
        ExtDef: Specifier ExtDecList SEMI   { $$ = new_tnode(($1)->no_line, ExtDef_, NULL); add_child($$,  $1);add_child($$,  $2);add_child($$,  $3);}//global variables, like: int global1, global2;
        | Specifier SEMI                    { $$ = new_tnode(($1)->no_line, ExtDef_, NULL); add_child($$,  $1);add_child($$,  $2);}// for struct, like: struct{};
        | Specifier FunDec CompSt           { $$ = new_tnode(($1)->no_line, ExtDef_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}// for functions, like: int main(){}
        | Specifier FunDec SEMI             { $$ = new_tnode(($1)->no_line, ExtDef_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}// function declaration in proj2
        | Specifier error CompSt            {syn_error = 1;}
        | Specifier FunDec error            {syn_error = 1;}
        | error SEMI                        {syn_error = 1;}
        ;
        ExtDecList: VarDec                  { $$ = new_tnode(($1)->no_line, ExtDecList_, NULL); add_child($$,  $1);}
        | VarDec COMMA ExtDecList           { $$ = new_tnode(($1)->no_line, ExtDecList_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        ;

        // Specifiers
        Specifier: TYPE                     { $$ = new_tnode(($1)->no_line, Specifier_, NULL); add_child($$,  $1);}// basic types, like: int float
        | StructSpecifier                   { $$ = new_tnode(($1)->no_line, Specifier_, NULL); add_child($$,  $1);}// struct shape
        ;
        StructSpecifier: STRUCT OptTag LC DefList RC    { $$ = new_tnode(($1)->no_line, StructSpecifier_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);add_child($$,  $5);}// struct Complex{int real, image}/ struct{int real, int image}
        | STRUCT Tag                        { $$ = new_tnode(($1)->no_line, StructSpecifier_, NULL); add_child($$,  $1);add_child($$,  $2);}// struct Complex in (struct Complex a,b)
        ;
        OptTag: ID                          { $$ = new_tnode(($1)->no_line, OptTag_, NULL); add_child($$,  $1);}
        |                                   { $$ = NULL;}// optinal tag: exists or not
        ;
        Tag: ID                             { $$ = new_tnode(($1)->no_line, Tag_, NULL); add_child($$,  $1);}
        ;

        //Declarators
        VarDec: ID                          { $$ = new_tnode(($1)->no_line, VarDec_, NULL); add_child($$,  $1);}// declarator of variable, like: int a, a[3]
        | VarDec LB INT RB                  { $$ = new_tnode(($1)->no_line, VarDec_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);}
        /* | error RB                          {syn_error = 1;} */
        ;
        FunDec: ID LP VarList RP            { $$ = new_tnode(($1)->no_line, FunDec_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);}// declarator of funtion, like: main(int argc, ...), main()
        | ID LP RP                          { $$ = new_tnode(($1)->no_line, FunDec_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | error RP                          {syn_error = 1;}
        ;
        VarList: ParamDec COMMA VarList     { $$ = new_tnode(($1)->no_line, VarList_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}// list of parameters: int a, int b
        | ParamDec                          { $$ = new_tnode(($1)->no_line, VarList_, NULL); add_child($$,  $1);}
        ;
        ParamDec: Specifier VarDec          { $$ = new_tnode(($1)->no_line, ParamDec_, NULL); add_child($$,  $1);add_child($$,  $2);}
        ;

        // Statements
        CompSt: LC DefList StmtList RC      { $$ = new_tnode(($1)->no_line, CompSt_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);}// Statements blocks rounded by{}
        | error RC                          {syn_error = 1;}
        ;
        StmtList: Stmt StmtList             { $$ = new_tnode(($1)->no_line, StmtList_, NULL); add_child($$,  $1);add_child($$,  $2);}
        |                                   { $$ = NULL;}
        ;
        Stmt: Exp SEMI                      { $$ = new_tnode(($1)->no_line, Stmt_, NULL); add_child($$,  $1);add_child($$,  $2);}// statement: an expression
        | CompSt                            { $$ = new_tnode(($1)->no_line, Stmt_, NULL); add_child($$,  $1);}// a {}
        | RETURN Exp SEMI                   { $$ = new_tnode(($1)->no_line, Stmt_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}// return statement
        | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE  { $$ = new_tnode(($1)->no_line, Stmt_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4); add_child($$,  $5);}// if statement, should remove conflict
        | IF LP Exp RP Stmt ELSE Stmt       { $$ = new_tnode(($1)->no_line, Stmt_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);add_child($$,  $5);add_child($$,  $6);add_child($$,  $7);}// if else statement
        | WHILE LP Exp RP Stmt              { $$ = new_tnode(($1)->no_line, Stmt_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);add_child($$,  $5);}// while statement
        /* | error RP                          { syn_error = 1;} */
        | error SEMI                        { syn_error = 1;}
        | IF error ELSE Stmt                { syn_error = 1;}
        | WHILE error Stmt                  { syn_error = 1;}
        ;

        // Local definations
        DefList: Def DefList                { $$ = new_tnode(($1)->no_line, DefList_, NULL); add_child($$,  $1);add_child($$,  $2);}// consequence of definations like: int a; float b, c; int d[10];
        |                                   { $$ = NULL;}
        ;
        Def: Specifier DecList SEMI         { $$ = new_tnode(($1)->no_line, Def_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Specifier error SEMI              {syn_error = 1;}
        ;
        DecList: Dec                        { $$ = new_tnode(($1)->no_line, DecList_, NULL); add_child($$,  $1);}
        | Dec COMMA DecList                 { $$ = new_tnode(($1)->no_line, DecList_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        ;
        Dec: VarDec                         { $$ = new_tnode(($1)->no_line, Dec_, NULL); add_child($$,  $1);}
        | VarDec ASSIGNOP Exp               { $$ = new_tnode(($1)->no_line, Dec_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        ;

        // Expressions
        Exp: Exp ASSIGNOP Exp               { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp AND Exp                       { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp OR Exp                        { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp RELOP Exp                     { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp PLUS Exp                      { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp MINUS Exp                     { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp STAR Exp                      { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp DIV Exp                       { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | LP Exp RP                         { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | MINUS Exp %prec UMINUS            { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2);}// uminus ref: https://www.gnu.org/software/bison/manual/html_node/Contextual-Precedence.html
        | NOT Exp                           { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2);}
        | ID LP Args RP                     { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);}
        | ID LP RP                          { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | Exp LB Exp RB                     { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);add_child($$,  $4);}
        | Exp DOT ID                        { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);add_child($$,  $2); add_child($$,  $3);}
        | ID                                { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);}
        | INT                               { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);}
        | FLOAT                             { $$ = new_tnode(($1)->no_line, Exp_, NULL); add_child($$,  $1);}
        /* | error RP                          {syn_error = 1;} */
        ;
        Args: Exp COMMA Args                { $$ = new_tnode(($1)->no_line, Args_, NULL); add_child( $$,  $1);add_child( $$,  $2); add_child( $$,  $3);}
        | Exp                               { $$ = new_tnode(($1)->no_line, Args_, NULL); add_child( $$,  $1);}
        ;
%%
void yyerror(char *str){
    // should add error message using ($1)->no_line, yycolumn
    printf("Error type B at Line %d: error around \"%s\"\n", yylineno, yytext);
}

int yywrap(){
    return 1;
}
