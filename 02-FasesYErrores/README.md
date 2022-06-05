## TP N°2 - Fases de la Traducción y Errores

# Objetivos
* Identificar las fases de traducción y errores

# Temas
* Fases de traducción
* Preprocesamiento
* Compilación
* Ensamblado
* Vinculación (Link)
* Errores en cada fase.

# Tareas

**1. Investigar las funcionalidades y opciones que su compilador presenta para limitar el inicio y fin de las fases de traducción.**

El compilador GCC ofrece los siguientes parametros:
* -E para hacer solamente el preprocesado, sin compilar, ensamblar o vincular.
* -S para concluir con el compilado, sin ensamblar o vincular.
* -c para compilar y ensamblar, pero sin vincular.

Si no se aplica ninguno de estos parametros, se realiza la traducción completa incluyendo la vinculación.

**2. Para la siguiente secuencia de pasos:**
* Transcribir en readme.md **cada comando ejecutado** y
* Describir en el readme.md el **resultado o error** obtenidos para cada paso.

# Secuencia de Pasos

Se parte de un archivo fuente que es corregido y refinado en sucesivos pasos. Es importante no saltearse pasos para mantener la correlación, ya que el estado dejado por el paso anterior es necesario para el siguiente.

## Preprocesador

1. Escribir *hello2.c*, una variante de *hello.c*:
   
```c
#include <stdio.h>
int/*medio*/main(void){
int i=42;
 prontf("La respuesta es %d\n");
```

**2. Preprocesar hello2.c, no compilar y generar hello2.i. Analizar su contenido.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc -E hello2.c -o hello2.i
```
**¿Que contiene *hello2.i*?**
* Primordialmente, este lleva el main con su definición y, por encima, todas las declaraciones y definiciones presentes en las librerias incluidas. Como el único import se trata de una parte de la librería estandar, la mayoría son declaraciones de funciones (aunque hay algunas definiciones presentes).

* Ademas, el comentario in-line anterior al main fue reemplazado por un espacio. NO hubo error respecto a los parentesis o la función *prontf*, que no existe.

**3. Escribir hello3.c, una nueva variante:**

```c
int printf(const char *s, ...);
int main(void){
int i=42;
 prontf("La respuesta es %d\n");
```
**4. Investigar la semantica de la primera linea.**
```c
int printf(const char *s, ...);
```
* Retorna un tipo int.
* Declara una función printf.
* Recibe una cantidad indeterminada de parametros, pero el primero se asenta que es un puntero a un char constante. Esto no quiere decir que el puntero (la direccion a memoria) es constante, si no que el valor al que apunta lo es. Se podría asignar una nueva dirección de memoria (otro puntero). De esta manera se pasan Strings, que son cadenas de char.

**1. Preprocesar *hello3.c*, no compilar y generar *hello3.i*. Buscar sus diferencias.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc -E hello3.c -o hello3.i
```
Entre ellos practicamente no existe diferencia. Esto es porque el procesador no encontró ningún comentario a quitar o un include para realizar el traspaso de declaraciones y definiciones por encima del main. La única diferencia presente son los flags del preprocesador, que, por ejemplo, indican el comienzo de un archivo.

## Compilación

**1. Compilar el resultado y generar *hello3.s*, no ensamblar.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc -S hello3.c -o hello3.s
```

Esto devuelve un error y un warning. Primero, un warning avisandome que escribí "prontf" y que esta función no esta declarada. Me sugiere escribir "printf" que es una función de la biblioteca estandar.

Ademas, devuelve un error por no haber cerrado la llave del main.

**2. Corregir solo los errores, no los *warnings*, en el nuevo archivo hello4.c y empezar de nuevo, generar4.s, no ensamblar.**

Para realizar esta tarea, corrijo la llave final y utilizo el siguiente commando.
```
gcc -S hello4.c -o hello4.s
```
Esta vez solo permanece el warning de la función "prontf" que no existe y que es similar a la función printf. Lo particular es que el codigo se compiló sin problemas. 

**3. Leer *hello4.s*, investigar sore lenguaje ensamblador, e indicar de forma sintética cual es el objetivo de ese código.**

El assembler, brevemente, hace lo siguiente:

Primero, el nombre del archivo fuente (que sirve para los debuggers). En segundo lugar se define un dato a partir del literal "La respuesta es %d\n" presente en el codigo fuente. Finalmente, dentro del main se encuentra el llamado a la función "prontf" a partir de un llamado previo a ese dato. 

**4. Ensamblar *hello4.s* en *hello4.o*, no vincular.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc -c hello4.c -o hello4.o
```

Se realiza sin problemas, solo mencionando una vez mas el warning de prontf.

## Vinculación

**1. Vincular *hello4.o* con la biblioteca estándar y generar el ejecutable.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc hello4.o -o hello4.exe
```

Esto últimadamente retorna un error, por "una referencia indefinida a 'prontf'", función que no existe en la biblioteca estandar.

**2. Corregir en *hello5.c* y generar el ejecutable. Solo corregir lo necesario para que vincule.**

Para realizar esta tarea, utilizo los siguientes comandos.
```
gcc -c hello5.c -o hello5.o
gcc hello5.o -o hello5.exe
```
Para lograr vincular solo basta con cambiar la referencia a prontf por printf. Demostrado por lo visto anteriormente, no hay problema con definir printf con los argumentos correctos por encima del main, ni con las asignaciones sin proposito o por llamar a printf sin un parametro numerico. 

**3. Ejecutar y analizar el resultado.**

Al ejecutar el archivo generado anteriormente, el printf funciona correctamente pero, como este esta mostrando el valor de la variable que espera en su segundo parametro (y yo en *hello5.c* no le pasé un valor), la función muestra por pantalla un valor de una celda de memoria siendo utilizada para otros propositos.

## Corrección de Bug

**1. Corregir en *hello6.c* y empezar de nuevo; verificar que funciona como se espera.**

Para eso, corrijo el bug pasando la variable i del main como segundo parametro del printf. Lo hago de la siguiente manera:

```c
printf("La respuesta es %d\n", i);
```
Luego realizo el proceso completo de construcción incluyendo la vinculación.

```
gcc -c hello6.c -o hello6.o
gcc hello6.o -o hello6.exe
```

Esto vincula sin problemas, y la salida es siempre la siguiente:
```
La respuesta es 42
```

## Remoción de Prototipo

1. **Escribir *hello7.c*, una nueva variante:**
```c
int main(void){
 int i=42;
 printf("La respuesta es %d\n", i);
}
```

Luego realizo el proceso de construcción empezando por la compilación.

```
gcc -S hello7.c -o hello7.s
```

```
hello7.c:3:2: warning: incompatible implicit declaration of built-in function 'printf'
hello7.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
  +++ |+#include <stdio.h>
    1 | int main(void){
```

Desde este punto esta presente una warning de declaración implicita de la función printf, y que debo incluir la libreria <stdio.h> de la biblioteca estandar o proveer una declaración de la función printf que utilizo. **La compilación sin embargo se realizó sin problemas**.

Luego compilo y ensamblo con el siguiente comando:

```
gcc -c hello7.c -o hello7.o
```

Se me presenta la misma warning, pero **el proceso finaliza sin problemas**.

Luego vinculo con el siguiente comando para crear un ejecutable:

```
gcc hello7.o -o hello7.exe
```

Se me presenta una última vez la misma warning, pero se crea el ejecutable sin problemas. Su salida es la siguiente:

```
La respuesta es 42
```

2. **¿Por que funciona?**

El funcionamiento es posible (en el caso de mi compilador) gracias a las funciones built-in de GCC. GCC ofrece funciones built-in precompiladas que le permiten reemplazar los llamados a estas funciones por una expresión in-line donde se inserta la definición entera de la función, ahorrando una llamada a una función y mejorando el rendimiento.

El [manual de GCC](https://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/Other-Builtins.html) dice lo siguiente sobre las funciones built-in:

>The ISO C90 functions abort, abs, acos, asin, atan2, atan, calloc, ceil, cosh, cos, exit, exp, fabs, floor, fmod, fprintf, fputs, frexp, fscanf, labs, ldexp, log10, log, malloc, memcmp, memcpy, memset, modf, pow, printf, putchar, puts, scanf, sinh, sin, snprintf, sprintf, sqrt, sscanf, strcat, strchr, strcmp, strcpy, strcspn, strlen, strncat, strncmp, strncpy, strpbrk, strrchr, strspn, strstr, tanh, tan, vfprintf, vprintf and vsprintf are all recognized as built-in functions unless -fno-builtin is specified (or -fno-builtin-function is specified for an individual function). All of these functions have corresponding versions prefixed with __builtin_.

Entre las funciones built-in, existe **printf**, con un prefijo *__builtin_*.

Es posible entonces hacer que nuestro codigo falle impidiendole al compilador utilizar funciones built-in con el siguiente parametro:

```
gcc -fno-builtin -fno-builtin-printf hello7.c -o hello7.o
```

Se ensambla el codigo sin estas funciones built-in, la warning permanece, la salida es la siguiente (identica a lo anterior):

```
hello7.c: In function 'main':
hello7.c:3:2: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]     
    3 |  printf("La respuesta es %d\n", i);
      |  ^~~~~~
hello7.c:1:1: note: 'printf' is defined in header '<stdio.h>'; did you forget to '#include <stdio.h>'? 
  +++ |+#include <stdio.h>
    1 | int main(void){
```

Luego intento vincular con la biblioteca estandar:

```
gcc -fno-builtin -fno-builtin-printf hello7.o -o hello7.exe
```

Finalmente, esto resulta en un **error de vinculación**. La salida es la extensa y dificil de entender como para escribirla aquí, pero el concepto queda demostrado.

## Compilación Separada: Contratos y Módulos


