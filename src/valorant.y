%{
#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h"

extern int yylex();
extern int line_num;
extern char* yytext;
extern FILE* yyin;
void yyerror(const char* s);

ASTNode* root = NULL;

// Para debug, si queres ver que pasa
#define YYDEBUG 1
%}

%union {
    int int_val;
    float float_val;
    char* string_val;
    ASTNode* ast_node;
}

/* Tokens (palabras reservadas y simbolos) */
%token AGENT PLANT
%token WIN LOSE HEADSHOT SHARE
%token HEAL DAMAGE KILL
%token DEFUSE ROTATE FLASH SMOKE RUSH
%token SAGE VIPER CYPHER
%token BREACH SOVA

%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL
%token <string_val> STRING_LITERAL
%token <string_val> IDENTIFIER
%token NOTEQUAL LESSEQUAL GREATEREQUAL

/* Tipos de no terminales (para el AST) */
%type <ast_node> program class_definition method_list method
%type <ast_node> statement_list statement
%type <ast_node> expression declaration
%type <ast_node> if_statement while_statement for_statement
%type <ast_node> input_statement output_statement
%type <ast_node> block return_statement assignment
%type <ast_node> function_call for_init for_condition for_increment
%type <ast_node> else_if_chain
%type <ast_node> parameter_list_opt parameter_list parameter
%type <ast_node> argument_list_opt argument_list

/* Precedencia y asociatividad (para que no se rompa todo) */
%right '='
%left WIN LOSE HEADSHOT NOTEQUAL LESSEQUAL GREATEREQUAL
%left HEAL DAMAGE
%left KILL SHARE

%%

program
    : class_definition                { root = $1; }
    ;

class_definition
    : AGENT IDENTIFIER '{' method_list '}'  { 
        $$ = create_class_node($2, $4);
        free($2);
    }
    ;

method_list
    : method                         { $$ = $1; }
    | method_list method            {
        ASTNode* temp = $1;
        while (temp->next) temp = temp->next;
        temp->next = $2;
        $$ = $1;
    }
    ;

method
    : SAGE IDENTIFIER '(' parameter_list_opt ')' block  { 
        $$ = create_method_node_with_params($2, $4, $6);
        $$->data_type = TYPE_INT;
        free($2);
    }
    | VIPER IDENTIFIER '(' parameter_list_opt ')' block  {
        $$ = create_method_node_with_params($2, $4, $6);
        $$->data_type = TYPE_FLOAT;
        free($2);
    }
    | CYPHER IDENTIFIER '(' parameter_list_opt ')' block  {
        $$ = create_method_node_with_params($2, $4, $6);
        $$->data_type = TYPE_STRING;
        free($2);
    }
    ;

parameter_list_opt
    : /* vacío */ { $$ = NULL; }
    | parameter_list { $$ = $1; }
    ;

parameter_list
    : parameter { $$ = $1; }
    | parameter_list ',' parameter { 
        ASTNode* temp = $1;
        while (temp->next) temp = temp->next;
        temp->next = $3;
        $$ = $1;
    }
    ;

parameter
    : SAGE IDENTIFIER { $$ = create_declaration_node(TYPE_INT, $2, NULL); free($2); }
    | VIPER IDENTIFIER { $$ = create_declaration_node(TYPE_FLOAT, $2, NULL); free($2); }
    | CYPHER IDENTIFIER { $$ = create_declaration_node(TYPE_STRING, $2, NULL); free($2); }
    ;

block
    : '{' statement_list '}'         { $$ = create_block_node($2); }
    | '{' '}'                        { $$ = create_block_node(NULL); }
    ;

statement_list
    : statement                      { $$ = $1; }
    | statement_list statement       {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* temp = $1;
            while (temp->next) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        }
    }
    ;

statement
    : declaration ';'                { $$ = $1; }
    | assignment ';'                 { $$ = $1; }
    | if_statement                   { $$ = $1; }
    | while_statement               { $$ = $1; }
    | for_statement                 { $$ = $1; }
    | input_statement ';'           { $$ = $1; }
    | output_statement ';'          { $$ = $1; }
    | return_statement ';'          { $$ = $1; }
    | function_call ';'             { $$ = $1; }
    | DEFUSE ';'                    { 
        $$ = create_node(NODE_DEFUSE);
    }
    ;

for_init
    : declaration                     { $$ = $1; }
    | assignment                      { $$ = $1; }
    ;

for_condition
    : expression                      { $$ = $1; }
    ;

for_increment
    : assignment                      { $$ = $1; }
    | IDENTIFIER '=' expression       {
        ASTNode* node = create_node(NODE_ASSIGNMENT);
        node->left = create_identifier_node($1);
        node->right = $3;
        $$ = node;
        free($1);
    }
    ;

for_statement
    : RUSH '(' for_init ';' for_condition ';' for_increment ')' block {
        // Creamos un nodo especial para el bucle for
        ASTNode* node = create_node(NODE_FOR);
        node->init = $3;      // Inicialización
        node->left = $5;      // Condición
        node->increment = $7; // Incremento
        node->right = $9;     // Cuerpo del bucle
        $$ = node;
    }
    ;

declaration
    : SAGE IDENTIFIER '=' expression  { $$ = create_declaration_node(TYPE_INT, $2, $4); free($2); }
    | VIPER IDENTIFIER '=' expression { $$ = create_declaration_node(TYPE_FLOAT, $2, $4); free($2); }
    | CYPHER IDENTIFIER '=' expression { $$ = create_declaration_node(TYPE_STRING, $2, $4); free($2); }
    | SAGE IDENTIFIER                 { $$ = create_declaration_node(TYPE_INT, $2, NULL); free($2); }
    | VIPER IDENTIFIER               { $$ = create_declaration_node(TYPE_FLOAT, $2, NULL); free($2); }
    | CYPHER IDENTIFIER              { $$ = create_declaration_node(TYPE_STRING, $2, NULL); free($2); }
    ;

expression
    : INT_LITERAL                     { $$ = create_number_node($1); }
    | FLOAT_LITERAL                   { $$ = create_float_node($1); }
    | STRING_LITERAL                  { $$ = create_string_node($1); free($1); }
    | IDENTIFIER                      { $$ = create_identifier_node($1); free($1); }
    | function_call                   { $$ = $1; }
    | expression HEAL expression      { $$ = create_binary_op_node(OP_ADD, $1, $3); }
    | expression DAMAGE expression    { $$ = create_binary_op_node(OP_SUB, $1, $3); }
    | expression KILL expression      { $$ = create_binary_op_node(OP_MUL, $1, $3); }
    | expression SHARE expression     { $$ = create_binary_op_node(OP_DIV, $1, $3); }
    | expression WIN expression       { $$ = create_binary_op_node(OP_WIN, $1, $3); }
    | expression LOSE expression      { $$ = create_binary_op_node(OP_LOSE, $1, $3); }
    | expression HEADSHOT expression  { $$ = create_binary_op_node(OP_HEADSHOT, $1, $3); }
    | '(' expression ')'             { $$ = $2; }
    | expression NOTEQUAL expression       { $$ = create_binary_op_node(OP_NOTEQUAL, $1, $3); }
    | expression LESSEQUAL expression      { $$ = create_binary_op_node(OP_LESSEQUAL, $1, $3); }
    | expression GREATEREQUAL expression   { $$ = create_binary_op_node(OP_GREATEREQUAL, $1, $3); }
    ;

if_statement
    : FLASH '(' expression ')' block                  { 
        $$ = create_if_node($3, $5, NULL); 
    }
    | FLASH '(' expression ')' block else_if_chain    { 
        $$ = create_if_node($3, $5, $6);
    }
    ;

else_if_chain
    : SMOKE block                                     { $$ = $2; }
    | SMOKE FLASH '(' expression ')' block            { $$ = create_if_node($4, $6, NULL); }
    | SMOKE FLASH '(' expression ')' block SMOKE block { $$ = create_if_node($4, $6, $8); }
    | SMOKE FLASH '(' expression ')' block else_if_chain { $$ = create_if_node($4, $6, $7); }
    ;

while_statement
    : ROTATE '(' expression ')' block { $$ = create_while_node($3, $5); }
    ;

input_statement
    : BREACH IDENTIFIER              { 
        $$ = create_input_node(create_identifier_node($2));
        free($2);
    }
    ;

output_statement
    : SOVA expression               { $$ = create_output_node($2); }
    ;

return_statement
    : PLANT expression               { $$ = create_return_node($2); }
    | PLANT                         { $$ = create_return_node(NULL); }
    ;

assignment
    : IDENTIFIER '=' expression      {
        ASTNode* node = create_node(NODE_ASSIGNMENT);
        node->left = create_identifier_node($1);
        node->right = $3;
        $$ = node;
        free($1);
    }
    ;

function_call
    : IDENTIFIER '(' argument_list_opt ')'             {
        $$ = create_function_call_node_with_args($1, $3);
        free($1);
    }
    ;

argument_list_opt
    : /* vacío */ { $$ = NULL; }
    | argument_list { $$ = $1; }
    ;

argument_list
    : expression { $$ = $1; }
    | argument_list ',' expression { 
        ASTNode* temp = $1;
        while (temp->next) temp = temp->next;
        temp->next = $3;
        $$ = $1;
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error de sintaxis en línea %d cerca de '%s': %s\n", 
            line_num, yytext, s);
}
