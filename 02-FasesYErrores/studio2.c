#include "studio.h" // Interfaz que exporta
#include <stdio.h> // Interfaz que importa
#include <stdlib.h> // Interfaz importada para ejemplo de biblioteca.
#include <time.h> // Interfaz importada para ejemplo de biblioteca.
void prontf(const char* s, int i){
 printf("La respuesta es %d\n", i);
}

/**
 * @brief Funcion de ejemplo para utilizar con la biblioteca "studio".
 * 
 * @param piso el valor minimo al azar.
 * @param techo el valor maximo al azar.
 * @return int Un entero al azar.
 */
int randomInt(const int piso, const int techo) {
    time_t t;
    srand(time(&t));
    return rand() % (techo + 1 - piso) + piso;
}