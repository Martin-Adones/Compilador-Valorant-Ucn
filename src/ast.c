#include "../include/ast.h"

// Funcion para crear un nodo nuevo (bien basico)
ASTNode* create_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo AST\n");
        exit(1);
    }
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->parent = NULL;
    node->init = NULL;
    node->increment = NULL;
    return node;
}

ASTNode* create_number_node(int value) {
    ASTNode* node = create_node(NODE_NUMBER);
    node->data_type = TYPE_INT;
    node->value.int_value = value;
    return node;
}

ASTNode* create_float_node(float value) {
    ASTNode* node = create_node(NODE_NUMBER);
    node->data_type = TYPE_FLOAT;
    node->value.float_value = value;
    return node;
}

ASTNode* create_string_node(const char* value) {
    ASTNode* node = create_node(NODE_STRING);
    node->data_type = TYPE_STRING;
    node->value.string_value = strdup(value);
    return node;
}

ASTNode* create_identifier_node(char* name) {
    ASTNode* node = create_node(NODE_IDENTIFIER);
    node->value.identifier = strdup(name);
    return node;
}

// Nodo para operaciones binarias (como suma, resta, etc)
ASTNode* create_binary_op_node(BinaryOp op, ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(NODE_BINARY_OP);
    node->value.op = op;
    node->left = left;
    node->right = right;
    if (left) left->parent = node;
    if (right) right->parent = node;
    return node;
}

// Nodo para asignaciones tipo a = b
ASTNode* create_assignment_node(ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(NODE_ASSIGNMENT);
    node->left = left;
    node->right = right;
    if (left) left->parent = node;
    if (right) right->parent = node;
    return node;
}

// Nodo para if/else (flash/smoke)
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_block, ASTNode* else_block) {
    ASTNode* node = create_node(NODE_IF);
    node->left = condition;
    node->right = then_block;
    if (else_block) {
        then_block->next = else_block;
    }
    if (condition) condition->parent = node;
    if (then_block) then_block->parent = node;
    if (else_block) else_block->parent = node;
    return node;
}

// Nodo para while (rotate)
ASTNode* create_while_node(ASTNode* condition, ASTNode* body) {
    ASTNode* node = create_node(NODE_WHILE);
    node->left = condition;
    node->right = body;
    if (condition) condition->parent = node;
    if (body) body->parent = node;
    return node;
}

// Nodo para for (rush)
ASTNode* create_for_node(ASTNode* init, ASTNode* condition, ASTNode* increment, ASTNode* body) {
    ASTNode* node = create_node(NODE_FOR);
    node->init = init;
    node->left = condition;
    node->increment = increment;
    node->right = body;
    if (init) init->parent = node;
    if (condition) condition->parent = node;
    if (increment) increment->parent = node;
    if (body) body->parent = node;
    return node;
}

// Nodo para un bloque de sentencias
ASTNode* create_block_node(ASTNode* statements) {
    ASTNode* node = create_node(NODE_BLOCK);
    node->left = statements;
    if (statements) statements->parent = node;
    return node;
}

// Nodo para declarar variables
ASTNode* create_declaration_node(DataType type, const char* name, ASTNode* initial_value) {
    ASTNode* node = create_node(NODE_DECLARATION);
    node->data_type = type;
    node->value.string_value = strdup(name);
    if (initial_value) {
        node->right = initial_value;
    } else {
        // Si no hay valor, pone uno por defecto segun el tipo
        switch(type) {
            case TYPE_INT:
                node->right = create_number_node(0);
                break;
            case TYPE_FLOAT:
                node->right = create_float_node(0.0);
                break;
            case TYPE_STRING:
                node->right = create_string_node("");
                break;
            default:
                node->right = NULL;
        }
    }
    if (node->left) node->left->parent = node;
    if (node->right) node->right->parent = node;
    return node;
}

// Nodo para leer input
ASTNode* create_input_node(ASTNode* variable) {
    ASTNode* node = create_node(NODE_INPUT);
    node->left = variable;
    if (variable) variable->parent = node;
    return node;
}

// Nodo para imprimir
ASTNode* create_output_node(ASTNode* expression) {
    ASTNode* node = create_node(NODE_OUTPUT);
    node->left = expression;
    if (expression) expression->parent = node;
    return node;
}

// Nodo para la clase principal (agent)
ASTNode* create_class_node(const char* name, ASTNode* methods) {
    ASTNode* node = create_node(NODE_CLASS);
    node->value.string_value = strdup(name);
    node->left = methods;  // Lista de metodos
    if (methods) methods->parent = node;
    return node;
}

// Nodo para un metodo sin parametros
ASTNode* create_method_node(const char* name, ASTNode* body) {
    ASTNode* node = create_node(NODE_METHOD);
    node->value.string_value = strdup(name);
    node->left = body;  // Cuerpo del metodo
    if (body) body->parent = node;
    return node;
}

// Nodo para un metodo con parametros
ASTNode* create_method_node_with_params(const char* name, ASTNode* params, ASTNode* body) {
    ASTNode* node = create_node(NODE_METHOD);
    node->value.string_value = strdup(name);
    node->params = params; // Lista de parametros
    node->left = body;     // Cuerpo del metodo
    if (body) body->parent = node;
    if (params) params->parent = node;
    return node;
}

// Nodo para llamada a funcion
ASTNode* create_function_call_node(const char* name) {
    ASTNode* node = create_node(NODE_FUNCTION_CALL);
    node->value.string_value = strdup(name);
    return node;
}

// Nodo para llamada a funcion con argumentos
ASTNode* create_function_call_node_with_args(const char* name, ASTNode* args) {
    ASTNode* node = create_node(NODE_FUNCTION_CALL);
    node->value.string_value = strdup(name);
    node->args = args; // Lista de argumentos
    return node;
}

// Nodo para return (plant)
ASTNode* create_return_node(ASTNode* expression) {
    ASTNode* node = create_node(NODE_PLANT);
    node->left = expression;
    if (expression) expression->parent = node;
    return node;
}

// Libera el arbol AST (recursivo)
void free_ast(ASTNode* node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->next);
    free_ast(node->init);
    free_ast(node->increment);
    if (node->type == NODE_STRING || node->type == NODE_IDENTIFIER || 
        node->type == NODE_DECLARATION) {
        free(node->value.string_value);
    }
    free(node);
}

// Imprime el AST (debug, no lo uses en produccion)
void print_ast(ASTNode* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    switch (node->type) {
        case NODE_NUMBER:
            if (node->data_type == TYPE_INT)
                printf("Number(int): %d\n", node->value.int_value);
            else
                printf("Number(float): %f\n", node->value.float_value);
            break;
        case NODE_STRING:
            printf("String: %s\n", node->value.string_value);
            break;
        case NODE_IDENTIFIER:
            printf("Identifier: %s\n", node->value.string_value);
            break;
        case NODE_BINARY_OP:
            printf("BinaryOp: %d\n", node->value.op);
            break;
        case NODE_ASSIGNMENT:
            printf("Assignment\n");
            break;
        case NODE_IF:
            printf("If\n");
            break;
        case NODE_WHILE:
            printf("While\n");
            break;
        case NODE_BLOCK:
            printf("Block\n");
            if (node->left) print_ast(node->left, level + 1);
            if (node->next) print_ast(node->next, level);
            return;
        case NODE_DECLARATION:
            printf("Declaration: %s (type: %d)\n", node->value.string_value, node->data_type);
            break;
        case NODE_INPUT:
            printf("Input\n");
            break;
        case NODE_OUTPUT:
            printf("Output\n");
            break;
        case NODE_CLASS:
            printf("Class: %s\n", node->value.string_value);
            break;
        case NODE_METHOD:
            printf("Method: %s\n", node->value.string_value);
            break;
        case NODE_FUNCTION_CALL:
            printf("Function Call: %s\n", node->value.string_value);
            break;
        case NODE_PLANT:
            printf("Return\n");
            break;
    }
    
    if (node->left) print_ast(node->left, level + 1);
    if (node->right) print_ast(node->right, level + 1);
    if (node->next) print_ast(node->next, level);
}

char* generate_code(ASTNode* node) {
    // Esta funcion se implementara mas adelante
    return NULL;
}