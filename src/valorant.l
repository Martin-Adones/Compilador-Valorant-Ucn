%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ast.h"
#include "valorant.tab.h"

int line_num = 1;

// Funcion para procesar caracteres de escape (tipo \n, \t, etc)
char* process_escape_sequences(const char* str) {
    char* result = malloc(strlen(str) + 1);
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] == '\\') {
            i++;
            switch (str[i]) {
                case 'n': result[j++] = '\n'; break;
                case 't': result[j++] = '\t'; break;
                case 'r': result[j++] = '\r'; break;
                case '\\': result[j++] = '\\'; break;
                case '"': result[j++] = '"'; break;
                default: result[j++] = str[i]; break;
            }
        } else {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

%}

%option noyywrap
%option yylineno

%%

[ \t]+          ; /* Ignora espacios y tabs */
[\n]            { line_num++; }
"//".*          ; /* Ignora comentarios de una linea */

"agent"         { return AGENT; }      /* Palabra clave para funcion */
"plant"         { return PLANT; }      /* Palabra clave para return */
"win"           { return WIN; }        /* Mayor que */
"lose"          { return LOSE; }       /* Menor que */
"headshot"      { return HEADSHOT; }   /* Igual */
"share"         { return SHARE; }      /* Division */
"heal"          { return HEAL; }       /* Suma */
"damage"        { return DAMAGE; }     /* Resta */
"kill"          { return KILL; }       /* Multiplicacion */
"defuse"        { return DEFUSE; }     /* Break */
"rotate"        { return ROTATE; }     /* While */
"rush"          { return RUSH; }       /* For */
"flash"         { return FLASH; }      /* If */
"smoke"         { return SMOKE; }      /* Else */
"sage"          { return SAGE; }       /* Int */
"viper"         { return VIPER; }      /* Float */
"cypher"        { return CYPHER; }     /* String */
"breach"        { return BREACH; }     /* Input */
"sova"          { return SOVA; }       /* Print */
"eco"           { return NOTEQUAL; }     /* != */
"save"          { return LESSEQUAL; }    /* <= */
"fullbuy"       { return GREATEREQUAL; } /* >=*/


[0-9]+          { 
    yylval.int_val = atoi(yytext); 
    return INT_LITERAL;
}

[0-9]+\.[0-9]+  { 
    yylval.float_val = atof(yytext); 
    return FLOAT_LITERAL;
}

\"[^\"]*\"      {
    char* str = strdup(yytext + 1);
    str[strlen(str) - 1] = '\0';
    yylval.string_val = process_escape_sequences(str);
    free(str);
    return STRING_LITERAL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.string_val = strdup(yytext);
    return IDENTIFIER;
}

"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
";"             { return ';'; }
","             { return ','; }
"="             { return '='; }

.               ; /* Ignorar caracteres no reconocidos */

%%
