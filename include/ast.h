#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipos de nodos del AST (cada uno es una cosa del lenguaje)
typedef enum {
    NODE_NUMBER,      // Numeros
    NODE_STRING,      // Strings
    NODE_IDENTIFIER,  // Variables
    NODE_BINARY_OP,   // Operaciones tipo +, -, etc
    NODE_ASSIGNMENT,  // a = b
    NODE_IF,          // flash
    NODE_ELSE,        // smoke
    NODE_WHILE,       // rotate
    NODE_BLOCK,       // Bloque de codigo
    NODE_DECLARATION, // Declaracion de variable
    NODE_INPUT,       // Leer (breach)
    NODE_OUTPUT,      // Imprimir (sova)
    NODE_DEFUSE,      // Break
    NODE_PLANT,       // Return
    NODE_FOR,         // rush
    NODE_CLASS,       // agent
    NODE_METHOD,      // funcion
    NODE_FUNCTION_CALL // llamada a funcion
} NodeType;

// Tipos de datos (los que soporta el lenguaje)
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_VOID
} DataType;

// Operadores binarios (los que podes usar)
typedef enum {
    OP_ADD,           // +
    OP_SUB,           // -
    OP_MUL,           // *
    OP_DIV,           // /
    OP_WIN,           // win (mayor)
    OP_LOSE,          // lose (menor)
    OP_HEADSHOT,      // headshot (igual)
    OP_NOTEQUAL,      // eco (diferente)
    OP_LESSEQUAL,     // save (<=)
    OP_GREATEREQUAL,  // fullbuy (>=)
    OP_SHARE          // share (asignacion)
} BinaryOp;

typedef union {
    int int_value;
    float float_value;
    char* string_value;
    char* identifier;
    BinaryOp op;
    DataType type;
} NodeValue;

// Estructura base para un nodo del AST
typedef struct ASTNode {
    NodeType type;
    DataType data_type;
    NodeValue value;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next;  // Para listas de instrucciones
    struct ASTNode* parent; // Referencia al nodo padre
    struct ASTNode* init;  // For loop initialization
    struct ASTNode* increment; // For loop increment
    // NUEVO: para métodos y llamadas
    struct ASTNode* params; // Lista de parámetros (método)
    struct ASTNode* args;   // Lista de argumentos (llamada)
} ASTNode;

// Funciones de creación de nodos
ASTNode* create_node(NodeType type);
ASTNode* create_number_node(int value);
ASTNode* create_float_node(float value);
ASTNode* create_string_node(const char* value);
ASTNode* create_identifier_node(char* name);
ASTNode* create_binary_op_node(BinaryOp op, ASTNode* left, ASTNode* right);
ASTNode* create_assignment_node(ASTNode* left, ASTNode* right);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_block, ASTNode* else_block);
ASTNode* create_while_node(ASTNode* condition, ASTNode* body);
ASTNode* create_block_node(ASTNode* statements);
ASTNode* create_declaration_node(DataType type, const char* name, ASTNode* initial_value);
ASTNode* create_input_node(ASTNode* variable);
ASTNode* create_output_node(ASTNode* expression);
ASTNode* create_for_node(ASTNode* init, ASTNode* condition, ASTNode* increment, ASTNode* body);
ASTNode* create_class_node(const char* name, ASTNode* methods);
ASTNode* create_method_node(const char* name, ASTNode* body);
ASTNode* create_method_node_with_params(const char* name, ASTNode* params, ASTNode* body);
ASTNode* create_function_call_node(const char* name);
ASTNode* create_function_call_node_with_args(const char* name, ASTNode* args);
ASTNode* create_return_node(ASTNode* expression);

// Funciones de manejo del AST
void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int level);
char* generate_code(ASTNode* node);

#endif // AST_H