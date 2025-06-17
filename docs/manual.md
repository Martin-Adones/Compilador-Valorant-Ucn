# Manual de Usuario - Compilador Valorant

## Introducción
El Compilador Valorant es un lenguaje de programación inspirado en el juego Valorant, donde los elementos del juego se convierten en estructuras y comandos de programación.

## Instalación
1. Clona el repositorio
2. Ejecuta `setup.bat` para instalar las dependencias
3. Usa `make` para compilar el proyecto

## Sintaxis Básica

### 1. Tipos de Datos
- `sage`: Números enteros
- `viper`: Números decimales (punto flotante)
- `cypher`: Cadenas de texto

```
sage numero = 42;        // Entero
viper decimal = 3.14;    // Decimal
cypher texto = "Hola";   // Texto
```

### 2. Operadores
#### Operadores Aritméticos
- `heal`: Suma (+)
- `damage`: Resta (-)
- `kill`: Multiplicación (*)
- `share`: División (/)

#### Operadores de Comparación
- `win`: Mayor que (>)
- `lose`: Menor que (<)
- `headshot`: Igual a (==)

```
// Operaciones aritméticas
viper resultado = a heal b;    // Suma
viper resta = x damage y;      // Resta
viper producto = m kill n;     // Multiplicación
viper division = p share q;    // División

// Comparaciones
flash (puntuacion win 90) {    // Mayor que
    sova "Excelente!";
}
```

### 3. Estructuras de Control

#### If-Else (Flash-Smoke)
```
flash (puntuacion win 90) {
    sova "Excelente!";
} smoke flash (puntuacion win 80) {
    sova "Muy bien!";
} smoke {
    sova "Sigue intentando";
}
```

#### While (Rotate)
```
rotate (contador lose 5) {
    sova contador;
    contador = contador heal 1;
}
```

#### Break (Defuse)
```
rotate (i lose 10) {
    flash (i headshot 5) {
        defuse;    // Sale del bucle
    }
}
```

### 4. Entrada/Salida

#### Entrada (Breach)
```
viper numero;
sova "Ingresa un numero: ";
breach numero;
```

#### Salida (Sova)
```
sova "Mensaje directo";
sova variable;
```

### 5. Funciones

#### Función Principal
Cada programa debe tener una función `spike()`:
```
agent spike() {
    // Código principal aquí
    plant 0;    // Retorna 0
}
```

## Ejemplos Completos

### 1. Calculadora Básica
```
agent spike() {
    // Variables para los números
    viper num1;
    viper num2;
    
    sova "Ingresa primer numero: ";
    breach num1;
    sova "Ingresa segundo numero: ";
    breach num2;

    sova "\nSuma: ";
    sova num1 heal num2;
    
    sova "\nResta: ";
    sova num1 damage num2;
    
    sova "\nMultiplicacion: ";
    sova num1 kill num2;
    
    sova "\nDivision: ";
    sova num1 share num2;

    plant 0;
}
```

### 2. Calculadora Avanzada
```
agent spike() {
    viper num1;
    viper num2;
    viper resultado;
    sage opcion;
    cypher continuar = "si";

    rotate (continuar headshot "si") {
        sova "\n=== Calculadora Avanzada ===\n";
        sova "1. Suma (heal)\n";
        sova "2. Resta (damage)\n";
        sova "3. Multiplicacion (kill)\n";
        sova "4. Division (share)\n";
        sova "Elige una opcion (1-4): ";
        breach opcion;

        sova "\nIngresa primer numero: ";
        breach num1;
        sova "Ingresa segundo numero: ";
        breach num2;

        flash (opcion headshot 1) {
            resultado = num1 heal num2;
        } smoke flash (opcion headshot 2) {
            resultado = num1 damage num2;
        } smoke flash (opcion headshot 3) {
            resultado = num1 kill num2;
        } smoke flash (opcion headshot 4) {
            flash (num2 headshot 0) {
                sova "Error: No se puede dividir por cero";
            } smoke {
                resultado = num1 share num2;
            }
        }

        sova "\nResultado: ";
        sova resultado;
        sova "\n";

        sova "Deseas realizar otra operacion? (si/no): ";
        breach continuar;
    }

    plant 0;
}
```

## Manejo de Errores
- Variables no declaradas
- División por cero
- Errores de sintaxis
- Tipos incompatibles
- Operaciones no válidas con strings

## Mejores Prácticas
1. Usa `viper` para números que puedan ser decimales
2. Usa `sage` solo cuando estés seguro de que necesitas enteros
3. Verifica la división por cero
4. Usa saltos de línea (\n) para mejor formato
5. Evita caracteres especiales en los mensajes
6. Valida las entradas del usuario
7. Usa comentarios para documentar tu código

## Limitaciones Actuales
1. No soporta funciones con parámetros
2. No hay soporte para arreglos
3. No hay soporte para operaciones de punto flotante complejas
4. No hay soporte para entrada/salida de archivos

## Solución de Problemas
Si encuentras errores, verifica:
1. Que todas las variables estén declaradas
2. Que los tipos de datos sean compatibles
3. Que no haya divisiones por cero
4. Que todas las llaves y paréntesis estén balanceados
5. Que cada sentencia termine con punto y coma
6. Que no uses caracteres especiales en los mensajes 