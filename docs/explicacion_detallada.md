# Explicación Detallada del Compilador Valorant

## 1. Visión General del Proyecto

El Compilador Valorant es un intérprete de un lenguaje de programación inspirado en el juego Valorant. El proyecto traduce conceptos de programación a términos del juego, haciendo que el aprendizaje sea más intuitivo para los jugadores.

## 2. Estructura del Proyecto

### 2.1 Componentes Principales
```
Compilador-Valorant/
├── src/               # Código fuente
├── include/           # Archivos de cabecera
├── build/            # Archivos compilados
├── examples/         # Ejemplos de programas
└── docs/             # Documentación
```

### 2.2 Archivos Clave
- `valorant.l`: Analizador léxico
- `valorant.y`: Analizador sintáctico
- `ast.h/c`: Árbol de sintaxis abstracta
- `interpreter.h/c`: Intérprete del lenguaje
- `main.c`: Punto de entrada del programa

## 3. Flujo de Ejecución

### 3.1 Paso 1: Análisis Léxico
1. El archivo fuente (.val) es leído por el analizador léxico (Flex)
2. El texto se divide en tokens (palabras clave, identificadores, números, etc.)
3. Cada token es clasificado según su tipo

### 3.2 Paso 2: Análisis Sintáctico
1. Bison recibe los tokens del analizador léxico
2. Verifica que la estructura del programa sea válida
3. Construye el Árbol de Sintaxis Abstracta (AST)

### 3.3 Paso 3: Interpretación
1. El AST es recorrido por el intérprete
2. Cada nodo es evaluado según su tipo
3. Las operaciones se ejecutan en tiempo real

## 4. Componentes en Detalle

### 4.1 Analizador Léxico (valorant.l)
- Define los patrones para reconocer tokens
- Maneja comentarios y espacios en blanco
- Convierte texto en unidades significativas

### 4.2 Analizador Sintáctico (valorant.y)
- Define la gramática del lenguaje
- Establece reglas de precedencia
- Crea nodos del AST

### 4.3 Árbol de Sintaxis Abstracta (ast.h/c)
```c
typedef enum {
    NODE_NUMBER,      // Números
    NODE_STRING,      // Cadenas
    NODE_IDENTIFIER,  // Variables
    NODE_BINARY_OP,   // Operaciones
    NODE_ASSIGNMENT,  // Asignaciones
    NODE_IF,          // Condicionales
    NODE_WHILE,       // Bucles
    // ...
} NodeType;
```

### 4.4 Intérprete (interpreter.h/c)
- Mantiene el contexto de ejecución
- Maneja variables y sus valores
- Ejecuta operaciones
- Maneja entrada/salida

## 5. Tipos de Datos

### 5.1 Tipos Básicos
- `sage`: Números enteros (int)
- `viper`: Números decimales (float)
- `cypher`: Cadenas de texto (string)

### 5.2 Implementación
```c
typedef enum {
    TYPE_SAGE,    // int
    TYPE_VIPER,   // float
    TYPE_CYPHER   // string
} ValueType;
```

## 6. Operadores

### 6.1 Operadores Aritméticos
- `heal`: Suma (+)
- `damage`: Resta (-)
- `kill`: Multiplicación (*)
- `share`: División (/)

### 6.2 Operadores de Comparación
- `win`: Mayor que (>)
- `lose`: Menor que (<)
- `headshot`: Igual a (==)

## 7. Estructuras de Control

### 7.1 Condicionales
```
flash (condicion) {
    // código si es verdadero
} smoke {
    // código si es falso
}
```

### 7.2 Bucles
```
rotate (condicion) {
    // código a repetir
}
```

## 8. Manejo de Variables

### 8.1 Declaración
```
sage numero = 42;        // Entero
viper decimal = 3.14;    // Decimal
cypher texto = "Hola";   // Texto
```

### 8.2 Estructura en Memoria
```c
typedef struct Variable {
    char* name;
    Value value;
    struct Variable* next;
} Variable;
```

## 9. Manejo de Errores

### 9.1 Tipos de Errores
1. Errores Léxicos
   - Caracteres inválidos
   - Tokens mal formados

2. Errores Sintácticos
   - Estructura incorrecta
   - Paréntesis sin cerrar

3. Errores de Ejecución
   - Variables no declaradas
   - División por cero
   - Tipos incompatibles

### 9.2 Implementación
```c
typedef struct {
    Variable* variables;
    int error_count;
    char error_message[256];
} ExecutionContext;
```

## 10. Ejemplo de Ejecución

### 10.1 Código Fuente
```
agent spike() {
    sage numero = 42;
    sova "El número es: ";
    sova numero;
    plant 0;
}
```

### 10.2 Proceso de Ejecución
1. El analizador léxico identifica tokens:
   - `agent`, `spike`, `sage`, `numero`, etc.

2. El analizador sintáctico construye el AST:
   - Función principal
   - Declaración de variable
   - Dos instrucciones de salida
   - Retorno

3. El intérprete:
   - Crea variable `numero` con valor 42
   - Imprime el texto
   - Imprime el número
   - Retorna 0

## 11. Optimizaciones y Mejoras Posibles

### 11.1 Optimizaciones
- Evaluación de expresiones constantes
- Eliminación de código muerto
- Caché de variables frecuentes

### 11.2 Mejoras Futuras
- Soporte para funciones con parámetros
- Implementación de arreglos
- Más operadores y funciones matemáticas
- Manejo de archivos

## 12. Conclusión

El Compilador Valorant demuestra los conceptos fundamentales de compiladores e intérpretes de una manera accesible y temática. Su diseño modular permite entender cada componente por separado mientras se mantiene la cohesión del sistema completo.

## 13. Glosario de Términos

### 13.1 Términos de Compilador
- **Token**: Unidad básica de significado en el código
- **AST**: Árbol que representa la estructura del programa
- **Parser**: Analizador sintáctico que construye el AST
- **Contexto**: Estado actual de la ejecución

### 13.2 Términos de Valorant
- **Sage**: Tipo entero (por su precisión)
- **Viper**: Tipo decimal (por su versatilidad)
- **Cypher**: Tipo string (por su capacidad de información)
- **Flash**: Condicional if (por su capacidad de control)
- **Rotate**: Bucle while (por su naturaleza repetitiva) 