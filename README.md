# ⚔️ Valorant Compiler

Un compilador personalizado creado con **Flex**, **Bison** y **C** que implementa un lenguaje inspirado en **Valorant**, utilizando palabras clave relacionadas con el juego para representar tipos de datos, operaciones y estructuras de control típicas en programación.

---

## 📋 Descripción General

Este lenguaje de programación es una mezcla entre la sintaxis tradicional y palabras clave temáticas de Valorant. Permite declarar variables, realizar operaciones aritméticas, controlar flujo de ejecución, manejar funciones (con parámetros y tipo de retorno), y hacer entrada/salida de datos.

---

## 🧠 Estructura del Lenguaje

### Tipos de Datos

| Palabra Clave | Tipo de Dato | Descripción           |
| ------------- | ------------ | --------------------- |
| sage          | int          | Enteros               |
| viper         | float        | Números con decimales |
| cypher        | string       | Cadenas de texto      |

---

### Operadores Aritméticos

| Palabra Clave | Operador | Descripción    |
| ------------- | -------- | -------------- |
| heal          | +        | Suma           |
| damage        | -        | Resta          |
| kill          | \*       | Multiplicación |
| share         | /        | División       |

---

### Operadores Relacionales

| Palabra Clave | Operador | Descripción   |
| ------------- | -------- | ------------- |
| win           | >        | Mayor que     |
| lose          | <        | Menor que     |
| headshot      | ==       | Igualdad      |
| eco           | !=       | Diferente     |
| save          | <=       | Menor o igual |
| fullbuy       | >=       | Mayor o igual |

---

### Operadores Lógicos

| Palabra Clave | Operador | Descripción         |
| ------------- | -------- | ------------------- |
| smoke flash   | else if  | Condicional anidado |

---

### Control de Flujo

| Palabra Clave | Equivalente en C/C++ | Descripción             |
| ------------- | -------------------- | ----------------------- |
| flash         | if                   | Condicional             |
| smoke         | else                 | Condicional alternativa |
| rush          | for                  | Bucle for               |
| rotate        | while                | Bucle while             |
| defuse        | break                | Romper bucle            |

---

### Funciones y Otros

| Palabra Clave | Descripción              |
| ------------- | ------------------------ |
| agent         | Declarar clase/función   |
| plant         | Palabra reservada return |
| breach        | Entrada (input)          |
| sova          | Salida (output)          |

---

## 💡 Variables y Declaración

Las variables se declaran con los tipos `sage`, `viper` o `cypher`.

```valorant
sage kills = 10;
viper accuracy = 95.5;
cypher playerName = "Sova";
```

También se pueden declarar sin inicializar:

```valorant
sage score;
```

---

## 📥 Entrada y Salida

- Para recibir entrada de usuario se usa la palabra clave `breach`.
- Para imprimir en pantalla se usa `sova`.

```valorant
sova "Ingresa tu nombre: ";
breach nombre;
```

---

## 🛠️ Operadores y Sintaxis

Las operaciones aritméticas y lógicas utilizan las palabras clave en lugar de símbolos.

```valorant
sage a = 10;
sage b = 20;
sage c = a heal b;  // c = 30
```

---

## 🔥 Estructura de un Programa

Todo programa debe comenzar con un bloque `agent` y definir un método principal llamado `spike`. Este método será ejecutado automáticamente al iniciar el programa.

```valorant
agent MiPrograma {
    sage spike() {
        // Código principal aquí
        plant 0;
    }
}
```

---

## 🧩 Ejemplo de Print Simple

```valorant
agent PrintHello {
    sage spike() {
        sova "¡Hola Valorant!";
        plant 0;
    }
}
```

---

## 🧮 Ejemplo de Función y Uso

```valorant
agent Matematicas {
    viper suma(viper a, viper b) {
        plant a heal b;
    }
    sage spike() {
        viper resultado = suma(10.5, 5.5);
        sova "La suma es: ";
        sova resultado;
        plant 0;
    }
}
```

---

## 🔁 Ejemplo FizzBuzz

```valorant
agent FizzBuzz{
    sage spike(){
        rush (sage num = 1; num lose 101; num = num heal 1) {
            flash (((num share 15) kill 15) headshot num) {
                sova "FizzBuzz";
            } smoke {
                flash (((num share 3) kill 3) headshot num) {
                    sova "Fizz";
                } smoke {
                    flash (((num share 5) kill 5) headshot num) {
                        sova "Buzz";
                    } smoke {
                        sova num;
                    }
                }
            }
        }
        plant 0;
    }
}
```

---

## 🧠 Sobre el smoke flash (else if)

Puedes anidar condiciones usando `smoke flash` para simular un `else if`:

```valorant
flash (cond1) {
    sova "Es cond1";
} smoke flash (cond2) {
    sova "Es cond2";
} smoke {
    sova "Ninguna";
}
```

---

## 🔬 Estructura del Proyecto

- `src/valorant.y`: Gramática Bison/Yacc del lenguaje
- `src/valorant.l`: Analizador léxico (Flex)
- `src/ast.c` y `include/ast.h`: Definición y manejo del AST (Árbol de Sintaxis Abstracta)
- `src/interpreter.c`: Intérprete que ejecuta el AST
- `src/main.c`: Punto de entrada, inicializa el parser y ejecuta el programa
- `examples/`: Ejemplos de programas en el lenguaje Valorant

---

## 🌳 AST y Ejecución

1. **Parsing:** El parser (Bison) convierte el código fuente en un AST, donde cada nodo representa una construcción del lenguaje (declaración, operación, función, etc).
2. **AST:** El AST es una estructura de nodos enlazados que modela la jerarquía y el flujo del programa. Cada nodo puede representar una operación, declaración, bloque, función, llamada, etc.
3. **Intérprete:** El intérprete recorre el AST y ejecuta cada nodo según su tipo:
   - Ejecuta bloques, evalúa expresiones, resuelve llamadas a funciones, gestiona variables y contexto.
   - El contexto de ejecución permite variables locales y paso de argumentos a funciones.
   - El tipo de retorno de cada función se respeta y se fuerza según la declaración.
   - Entrada y salida se gestionan con `breach` y `sova`.

---

## 🌲 ¿Cómo funciona el AST? (Visual y Breve)

El AST (Árbol de Sintaxis Abstracta) es una estructura en árbol donde cada nodo representa una operación, instrucción o bloque del programa. El intérprete recorre este árbol para ejecutar el código.

### Ejemplo 1: Suma simple

Código Valorant:

```valorant
sage a = 2;
sage b = 3;
sage c = a heal b;
```

Representación visual del AST:

```
   =           =           =
  / \         / \         / \
a   2       b   3       c   heal
                           /   \
                          a     b
```

- Cada `=` es un nodo de asignación.
- El nodo `heal` es la suma, con hijos `a` y `b`.

### Ejemplo 2: Ciclo while (rotate)

Código Valorant:

```valorant
sage i = 0;
rotate (i lose 5) {
    sova i;
    i = i heal 1;
}
```

AST visual:

```
   =
  / \
i   0
   |
 rotate
  /    \
cond   block
 |      |
lose    ;
/  \   / \
i   5 sova  =
         |  / \
         i i 1
```

- El nodo `rotate` tiene como hijos la condición (`i lose 5`) y el bloque de instrucciones.
- El bloque puede tener varios hijos (instrucciones).

**El intérprete recorre el árbol así:**

- Para la suma, evalúa los hijos de `heal` y suma sus valores.
- Para el ciclo, evalúa la condición y ejecuta el bloque mientras sea verdadera.

---

## 📚 Ejemplos

Consulta la carpeta `examples/` para ver programas de prueba, calculadoras, control de flujo, entrada/salida y uso de funciones.

---

### Créditos

Desarrollado como ejercicio académico. Inspirado en Valorant y en la enseñanza de compiladores.
