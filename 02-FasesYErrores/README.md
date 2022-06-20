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
int printf(const char * restrict s, ...);
```
* Retorna un tipo *int*.
* Declara una función *printf*.
* *restrict* exige que el valor de s sea apuntado únicamente por el puntero.
* Recibe una cantidad indeterminada de parametros, pero el primero se asenta que es un puntero a un *char* constante. Esto no quiere decir que el puntero (la direccion a memoria) es constante, si no que el valor al que apunta lo es. Se podría asignar una nueva dirección de memoria (otro puntero). De esta manera se pasan *Strings*, que son cadenas de *char*.

**1. Preprocesar *hello3.c*, no compilar y generar *hello3.i*. Buscar sus diferencias.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc -E hello3.c -o hello3.i
```
Entre ellos practicamente no existe diferencia. Esto es porque el procesador no encontró ningún comentario a quitar o un include para realizar el traspaso de declaraciones y definiciones por encima del main. La única diferencia presente son los flags del preprocesador, que, por ejemplo, indican el comienzo de un archivo. Sirven para dar información al compilador.

## Compilación

**1. Compilar el resultado y generar *hello3.s*, no ensamblar.**

Para realizar esta tarea, utilizo el siguiente commando.
```
gcc -S hello3.c -o hello3.s
```

Esto devuelve un error y un warning. Primero, un warning avisandome que escribí "prontf" y que esta función no esta declarada. Me sugiere escribir "printf" que es una función de la biblioteca estandar.

Ademas, devuelve un error por no haber cerrado la llave del main. Este es un error sintactico.

**2. Corregir solo los errores, no los *warnings*, en el nuevo archivo hello4.c y empezar de nuevo, generar4.s, no ensamblar.**

Para realizar esta tarea, corrijo la llave final y utilizo el siguiente commando.
```
gcc -S hello4.c -o hello4.s
```
Esta vez solo permanece el warning de la función "prontf" que no existe y que es similar a la función printf. Lo particular es que el codigo se compiló sin problemas. 

**3. Leer *hello4.s*, investigar sore lenguaje ensamblador, e indicar de forma sintética cual es el objetivo de ese código.**

El assembler, brevemente, hace lo siguiente:

Primero, el nombre del archivo fuente (que sirve para los debuggers). En segundo lugar se define un dato a partir del literal "La respuesta es %d\n" presente en el codigo fuente. 

```
	.file	"hello4.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "La respuesta es %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
```
Luego, guarda el valor 42 en una variable luego de preparar la pila y llamar a una función main:

```
	call	__main
	movl	$42, -4(%rbp)
	leaq	.LC0(%rip), %rcx
```

Finalmente, dentro del main se encuentra el llamado a la función "prontf" a partir de un llamado previo a ese dato. Prepara también el cero, para las funciones que retornan cero.

```
	call	prontf
	movl	$0, %eax
```

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

```
C:/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/10.3.0/../../../../x86_64-w64-mingw32/bin/ld.exe: hello4.o:hello4.c:(.text+0x1c): undefined reference to `prontf'
```

**2. Corregir en *hello5.c* y generar el ejecutable. Solo corregir lo necesario para que vincule.**

Para realizar esta tarea, utilizo los siguientes comandos.
```
gcc -c hello5.c -o hello5.o
gcc hello5.o -o hello5.exe
```
Para lograr vincular solo basta con cambiar la referencia a prontf por printf. Demostrado por lo visto anteriormente, no hay problema con declarar un prototipo de printf con los argumentos correctos por encima del main, ni con las asignaciones sin proposito o por llamar a printf sin un parametro numerico. 

**3. Ejecutar y analizar el resultado.**

Al ejecutar el archivo generado anteriormente, el printf funciona correctamente pero, como este esta mostrando el valor de la variable que espera en su segundo parametro (y yo en *hello5.c* no le pasé un valor), la función muestra por pantalla un valor de una celda de memoria siendo utilizada para otros propositos.

Este es un error pragmatico y no sintactico, semantico o lexico, porque superó todas las fases de traducción.

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

>The ISO C90 functions abort, abs, acos, asin, atan2, atan, calloc, ceil, cosh, cos, exit, exp, fabs, floor, fmod, fprintf, fputs, frexp, fscanf, labs, ldexp, log10, log, malloc, memcmp, memcpy, memset, modf, pow, printf, putchar, puts, scanf, sinh, sin, snprintf, sprintf, sqrt, sscanf, strcat, strchr, strcmp, strcpy, strcspn, strlen, strncat, strncmp, strncpy, strpbrk, strrchr, strspn, strstr, tanh, tan, vfprintf, vprintf and vsprintf are all recognized as built-in functions unless -fno-builtin is specified (or -fno-builtin-function is specified for an individual function). All of these functions have corresponding versions prefixed with \_\_builtin_.

Entre las funciones built-in, existe **printf**, con un prefijo *\_\_builtin_*.

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

Finalmente, esto resulta en un **error en la vinculación**. La salida es la extensa y dificil de entender como para escribirla aquí, pero el concepto queda demostrado.

En clase hemos expuesto un documento del estandar C donde se aclara que, a partir del estandar C99, la declaración de funciones de manera implicita fue removida. En mi caso, solamente es posible por GCC, que tiene este agregado propio.

## Compilación Separada: Contratos y Módulos

**1. Escribir *studio1.c* (sí, *studio1*, no *stdio*) y *hello8.c*. La unidad de traducción *studio1.c* tiene una implementación de la función *prontf*, que es solo un wrapper de la función estandar *printf*:**

```C
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}
```

**La unidad de traducción *hello8.c*, muy similar a *hello4.c*, invoca a *prontf*, pero no incluye ningún header.**

```C
int main(void){
int i=42;
 prontf("La respuesta es %d\n", i);
}
```
**2. Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de traducción (i.e., archivos fuente, archivos con extensión .c). Luego generar ese ejecutable y probarlo.**

Existe una manera de realizar la traducción de dos archivos fuente con GCC. El comando, para los *hello8.c* y *studio1.c* anteriores, es el siguiente:

```
gcc -include studio1.c -c hello8.c -o hello8.o
gcc hello8.o -o hello8.exe
```

Con el parametro -include. Esta forma es poco practica a medida los programas aumentan su complejidad y es preferible utilizar headers.

Tambien es posible hacerlo totalmente en una sola linea:
```
gcc studio1.c hello8.c -o hello8.exe
```

```
La respuesta es 42
```

**3. Responder ¿que ocurre si eliminamos o agregamos argumentos a la invocación de *prontf*? Justifique.**

Si agrego parametros, por ejemplo, dos integers:
```C
 prontf("La respuesta es %d\n", i, 42, 88);
```

Resulta en el siguiente **error de compilación**
```
hello8.c: In function 'main':
hello8.c:3:2: error: too many arguments to function 'prontf'
    3 |  prontf("La respuesta es %d\n", i, 42, 88);
      |  ^~~~~~
```

El error es suficientemente descriptivo; se pasaron demasiados parametros a una función como sucedería con cualquier implementación.

Si en cambio paso menos argumentos, por ejemplo, sin la variable:
```C
 prontf("La respuesta es %d\n");
```

Ahora, el error de compilación es el siguiente:

```
hello8.c: In function 'main':
hello8.c:3:2: error: too few arguments to function 'prontf'
    3 |  prontf("La respuesta es %d\n");
      |  ^~~~~~
```

Entonces, en definitiva, la razón de estos errores es que *prontf* es un wrapper que, a su vez, es una función que recibe una cantidad de parametros establecida. Estos son un array de caracteres y un entero. A partir de ellos, este hace una implementación particular de printf.

```C
prontf(const char* s, int i);
```

## Revisitar el punto anterior, esta vez utilizando un contrato de interfaz en un archivo header.

**1. Escribir el contrato en *studio.h***

```C
#ifndef _STUDIO_H_INCULDED_
#define _STUDIO_H_INCULDED_
void prontf(const char*, int);
#endif
```

**2. Escribir *hello9.c*, un cliente que si incluye el contrato.**

```C
#include "studio.h" // Interfaz que importa
int main(void){
int i=42;
 prontf("La respuesta es %d\n", i);
}
```

**3. Escribir *studio2.c*, el proveedor que si incluye el contrato.**
```C
#include "studio.h" // Interfaz que exporta
#include <stdio.h> // Interfaz que importa
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}
```

**4. Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor?**

El beneficio de incluir el contrato en los clientes y en el proveedor es la inclusión de los prototipos del contrato. Esto permite al IDE adelantarme errores incluso antes del momento de compilar.

De esta manera tambien se comprueba que el cliente utiliza las funciones de manera correcta y que el proveedor obedece con los prototipos del contrato.

**Punto extra: Investigue sobre bibliotecas. ¿Qué son? ¿Se pueden distribuir? ¿Son portables? ¿Cuales son sus ventajas y desventajas?**

**Desarrolle y utilice la biblioteca studio.**

Una biblioteca es una unificación de varios archivos objeto, osea, codigo previamente compilado. Contienen al codigo compilado y ensamblado. Los tipos de dato, prototipos, etc. estan incluidos en los archivos header asociados a las bibliotecas (por ejemplo, *stdio.h*).

Su distribución es comun, le permite al programador utilizar codigo escrito por otros programadores. Teniendo en cuenta que son archivos ya ensamblados, no son portables mas alla del tipo de arquitectura (puesto que contienen instrucciones de assembler especificas, generadas al momento de compilarse). Su codigo fuente si es portable, solo es necesario compilarlo.

Para desarrollar la biblioteca studio utilizo lo existente. Declaro en mi header la función:

```C
int randomInt(const int piso, const int techo);
```

y desarrollo su definición en *studio2.c*:

```C
int randomInt(const int piso, const int techo) {
	time_t t;
    srand(time(&t));
    return rand() % (techo + 1 - piso) + piso;
}
```

Ensamblo mi codigo C en un archivo objeto:

```
gcc -c studio2.c -o studioLibrary.o
```

y creo mi libreria con el siguiente comando (a modo de ejemplo no envio a mi carpeta de librerias; ver el Makefile para ver la instalación correcta. Este comando envía la biblioteca a mi directorio actual):

```
ar rcs studioLibrary.a studioLibrary.o
```

Y queda disponible la librería con codigo ensamblado para vincular con nuestros programas. Cabe aclarar que el header studio.h no esta incluido; por lo que habría que incluirlo o bien, si no estuviera disponible, declarar el prototipo de las funciones de la libreria.

Luego utilizo la libreria en *hello10_libreria.c*:
```C
#include "studio.h" // Interfaz que importa
int main(void){
	int i=randomInt(0, 42);
 	prontf("La respuesta es %d\n", i);
}
```

Y genero el ejecutable utilizando mi libreria con el siguiente parametro:

```
gcc hello10_libreria.c -L. -l:studioLibrary.a -o hello10_libreria.exe
```

El parametro "-L." ordena a GCC buscar librerias en el directorio actual, y no es necesario si se instala la librería en directorios que GCC consulta por defecto, como es el caso del Makefile a continuación.

En la entrega incluyo un Makefile que permite instalar la libreria en el directorio de mingw64 y correr el programa de ejemplo (Solo para Windows).


