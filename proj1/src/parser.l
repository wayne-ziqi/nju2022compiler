%{
    #include <stdlib.h>
    #include "syntex.tab.h"
    void yyerror(char *);
    int yycolumn = 1;
    unsigned int lex_error = 0;
%}
/* definations, e.g. digit: [0-9] */
%option yylineno
digit [0-9]
letter_ [_a-zA-Z]
HEX 0x[0-9a-fA-F]+
OCT 0[0-7]+
DEC 0|([1-9][0-9]*)

%%

(({digit}+\.{digit}*)|\.{digit}+)([Ee][+-]?{digit}+)?   {yylval.t_node = new_tnode(yylineno, _FLOAT, yytext); return FLOAT;}           
({OCT}|{DEC}|{HEX})                                     {yylval.t_node = new_tnode(yylineno, _INT, yytext); return INT;}               
int|float                                               {yylval.t_node = new_tnode(yylineno, _TYPE, yytext); return TYPE;}             /*TYPE : int| char | float | double*/
struct                                                  {yylval.t_node = new_tnode(yylineno, _STRUCT, NULL); return STRUCT;}         /*STRUCT → struct*/
return                                                  {yylval.t_node = new_tnode(yylineno, _RETURN, NULL); return RETURN;}         /*RETURN → return&*/
if                                                      {yylval.t_node = new_tnode(yylineno, _IF, NULL); return IF;}                 /*IF → if*/
else                                                    {yylval.t_node = new_tnode(yylineno, _ELSE, NULL); return ELSE;}             /*ELSE → else*/
while                                                   {yylval.t_node = new_tnode(yylineno, _WHILE, NULL); return WHILE;}            /*WHILE → while*/
\/\*(?:[^\*]|\*+[^\/\*])*\*+\/                          /* block comments, do nothing, ref: stackexchange*/
"//"                                                    {char c = input(); while(c!='\n')c = input();}
{letter_}({letter_}|{digit})*                           {yylval.t_node = new_tnode(yylineno, _ID, yytext); return ID;}                 /*ID*/
;                                                       {yylval.t_node = new_tnode(yylineno, _SEMI, NULL);return SEMI;}             /*SEMI: ;*/
,                                                       {yylval.t_node = new_tnode(yylineno, _COMMA, NULL); return COMMA;}            /*COMMA: ,*/
>=|>|<=|<|!=|==                                         {yylval.t_node = new_tnode(yylineno, _RELOP, NULL); return RELOP;}           /*RELOP: > | < | >= | <= | == | !=*/
=                                                       {yylval.t_node = new_tnode(yylineno, _ASSIGNOP, NULL); return ASSIGNOP;}     /*ASSIGNOP =*/
\+                                                      {yylval.t_node = new_tnode(yylineno, _PLUS, NULL); return PLUS;}             /*PLUS: + */
-                                                       {yylval.t_node = new_tnode(yylineno, _MINUS, NULL); return MINUS;}           /*MINUS: - */
\*                                                      {yylval.t_node = new_tnode(yylineno, _STAR, NULL); return STAR;}             /*STAR: * */
\/                                                      {yylval.t_node = new_tnode(yylineno, _DIV, NULL);return DIV;}               /*DIV : / */
&&                                                      {yylval.t_node = new_tnode(yylineno, _AND, NULL);return AND;}               /*AND: &&*/
\|\|                                                    {yylval.t_node = new_tnode(yylineno, _OR, NULL); return OR;}                 /*OR : ||*/
\.                                                      {yylval.t_node = new_tnode(yylineno, _DOT, NULL);return DOT;}                /*DOT : .*/
!                                                       {yylval.t_node = new_tnode(yylineno, _NOT, NULL);return NOT;}               /*NOT : !*/
\(                                                      {yylval.t_node = new_tnode(yylineno, _LP, NULL); return LP;}                 /*LP: (*/
\)                                                      {yylval.t_node = new_tnode(yylineno, _RP, NULL); return RP;}                 /*RP → )*/
\[                                                      {yylval.t_node = new_tnode(yylineno, _LB, NULL); return LB;}                 /*LB → [*/
\]                                                      {yylval.t_node = new_tnode(yylineno, _RB, NULL); return RB;}                 /*RB → ]*/
\{                                                      {yylval.t_node = new_tnode(yylineno, _LC, NULL); return LC;}                 /*LC → {*/
\}                                                      {yylval.t_node = new_tnode(yylineno, _RC, NULL); return RC;}                 /*RC → }*/
[ \t]+                                                  /*ignore white space*/
\n                                                      {/*printf("\n%d ", yylineno);*/yycolumn = 1;/* return CR;*/}
\r                                                      /* ignore CRLF format on windows*/
.                                                       {printf("Error type A at Line %d: Mysterious Character \"%s\"\n",yylineno, yytext); lex_error = 1;}
%%
