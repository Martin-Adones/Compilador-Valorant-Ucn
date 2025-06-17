#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Tipos de valores (los que podes guardar)
typedef enum {
    TYPE_SAGE,    // int
    TYPE_VIPER,   // float
    TYPE_CYPHER   // string
} ValueType;

// Estructura para guardar valores
typedef struct {
    ValueType type;
    union {
        int sage_val;
        float viper_val;
        char* cypher_val;
    } value;
} Value;

// Estructura para variables (nombre, valor y el siguiente)
typedef struct Variable {
    char* name;
    Value value;
    struct Variable* next;
} Variable;

// Contexto de ejecucion (aca van las variables y errores)
typedef struct {
    Variable* variables;
    int error_count;
    char error_message[256];
    int has_return;  // Para saber si hay return
} ExecutionContext;

// Funciones del interprete
ExecutionContext* create_context();
void free_context(ExecutionContext* context);
void set_variable(ExecutionContext* context, const char* name, Value value);
Value* get_variable(ExecutionContext* context, const char* name);
void report_error(ExecutionContext* context, const char* message);
Value interpret_node(void* node, ExecutionContext* context);
Variable* find_variable(ExecutionContext* context, const char* name);
void interpret_program(ASTNode* program);

#endif // INTERPRETER_H