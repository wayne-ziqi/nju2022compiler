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

(({digit}+\.{digit}*)|\.{digit}+)([Ee][+-]?{digit}+)?   {yylval.t_node = new_tnode(yylineno, FLOAT_, yytext); return FLOAT;}
({OCT}|{DEC}|{HEX})                                     {yylval.t_node = new_tnode(yylineno, INT_, yytext); return INT;}
int|float                                               {yylval.t_node = new_tnode(yylineno, TYPE_, yytext); return TYPE;}             /*TYPE : int| char | float | double*/
struct                                                  {yylval.t_node = new_tnode(yylineno, STRUCT_, NULL); return STRUCT;}         /*STRUCT → struct*/
return                                                  {yylval.t_node = new_tnode(yylineno, RETURN_, NULL); return RETURN;}         /*RETURN → return*/
if                                                      {yylval.t_node = new_tnode(yylineno, IF_, NULL); return IF;}                 /*IF → if*/
else                                                    {yylval.t_node = new_tnode(yylineno, ELSE_, NULL); return ELSE;}             /*ELSE → else*/
while                                                   {yylval.t_node = new_tnode(yylineno, WHILE_, NULL); return WHILE;}            /*WHILE → while*/
\/\*(?:[^\*]|\*+[^\/\*])*\*+\/                          /* block comments, do nothing, ref: stackexchange*/
"//"                                                    {char c = input(); while(c!='\n')c = input();}
{letter_}({letter_}|{digit})*                           {yylval.t_node = new_tnode(yylineno, ID_, yytext); return ID;}                 /*ID*/
;                                                       {yylval.t_node = new_tnode(yylineno, SEMI_, NULL); return SEMI;}             /*SEMI: ;*/
,                                                       {yylval.t_node = new_tnode(yylineno, COMMA_, NULL); return COMMA;}            /*COMMA: ,*/
>=|>|<=|<|!=|==                                         {yylval.t_node = new_tnode(yylineno, RELOP_, yytext); return RELOP;}           /*RELOP: > | < | >= | <= | == | !=*/
=                                                       {yylval.t_node = new_tnode(yylineno, ASSIGNOP_, NULL); return ASSIGNOP;}     /*ASSIGNOP =*/
\+                                                      {yylval.t_node = new_tnode(yylineno, PLUS_, NULL); return PLUS;}             /*PLUS: + */
-                                                       {yylval.t_node = new_tnode(yylineno, MINUS_, NULL); return MINUS;}           /*MINUS: - */
\*                                                      {yylval.t_node = new_tnode(yylineno, STAR_, NULL); return STAR;}             /*STAR: * */
\/                                                      {yylval.t_node = new_tnode(yylineno, DIV_, NULL); return DIV;}               /*DIV : / */
&&                                                      {yylval.t_node = new_tnode(yylineno, AND_, NULL); return AND;}               /*AND: &&*/
\|\|                                                    {yylval.t_node = new_tnode(yylineno, OR_, NULL); return OR;}                 /*OR : ||*/
\.                                                      {yylval.t_node = new_tnode(yylineno, DOT_, NULL);return DOT;}                /*DOT : .*/
!                                                       {yylval.t_node = new_tnode(yylineno, NOT_, NULL);return NOT;}               /*NOT : !*/
\(                                                      {yylval.t_node = new_tnode(yylineno, LP_, NULL); return LP;}                 /*LP: (*/
\)                                                      {yylval.t_node = new_tnode(yylineno, RP_, NULL); return RP;}                 /*RP → )*/
\[                                                      {yylval.t_node = new_tnode(yylineno, LB_, NULL); return LB;}                 /*LB → [*/
\]                                                      {yylval.t_node = new_tnode(yylineno, RB_, NULL); return RB;}                 /*RB → ]*/
\{                                                      {yylval.t_node = new_tnode(yylineno, LC_, NULL); return LC;}                 /*LC → {*/
\}                                                      {yylval.t_node = new_tnode(yylineno, RC_, NULL); return RC;}                 /*RC → }*/
[ \t]+                                                  /*ignore white space*/
\n                                                      {/*printf("\n%d ", yylineno);*/yycolumn = 1;/* return CR;*/}
\r                                                      /* ignore CRLF format on windows*/
.                                                       {printf("Error type A at Line %d: Mysterious Character \"%s\"\n",yylineno, yytext); lex_error = 1;}
%%
