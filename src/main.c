#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "interpreter.h"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

int main(int argc, char** argv) {
    // Desactivo el buffer para que todo salga al toque
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

    if (argc < 2) {
        printf("Uso: %s archivo.val\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        printf("Error: No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    yyin = input;
    printf("Compilador Valorant v1.0\n");
    
    if (yyparse() != 0) {
        printf("Error durante el analisis sintactico\n");
        return 1;
    }

    // Arranca el contexto y ejecuta el programa
    ExecutionContext* context = create_context();
    printf("\nEjecutando el programa:\n");
    printf("----------------------\n");
    Value result = interpret_node(root, context);

    // Limpia todo
    free_ast(root);
    free_context(context);
    fclose(input);

    if (context->error_count > 0) {
        printf("\nPrograma terminado con errores\n");
        return 1;
    }

    printf("\nPrograma ejecutado exitosamente\n");
    printf("Valor de retorno: %d\n", result.value.sage_val);
    return 0;
}
