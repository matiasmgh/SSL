/**
 * @file TablasDeConversion.c
 * @author mgaiteiroharriague (mgaiteiroharriague@frba.utn.edu.ar)
 * @brief Impresor de tablas de conversion de unidades.
 * @version 0.1
 * @date 2022-05-10
 * 
 */

#include "Conversion.h"
#include <stdio.h>

/**
 * @brief Imprime una fila de conversion de unidades.
 * 
 * @param converter Función de conversion de unidad
 * @param gradoBase El grado a mostrar junto con su valor convertido
 */
void printFila(int gradoBase, double (*converter)(double)) {
    printf("| %3d | %6.1f |\n", gradoBase, (*converter)(gradoBase));
}

/**
 * @brief Imprime las filas de una tabla de conversion de unidades.
 * 
 * @param PISO_TABLA Grados iniciales de la tabla
 * @param TECHO_TABLA Grados maximos de la tabla
 * @param INCREMENTO Incremento de grados por fila
 * @param converter Funcion de conversion de unidad
 */
void printFilas(int PISO_TABLA, int TECHO_TABLA, int INCREMENTO, double (*converter)(double)) {
    printf("----------------\n");
    for (int gradoBase = PISO_TABLA; gradoBase <= TECHO_TABLA; gradoBase = gradoBase + INCREMENTO) {
        printFila(gradoBase, (*converter));
    }
    printf("================\n");
    printf("\n");
}

void printTablaCelsius(int PISO_TABLA, int TECHO_TABLA, int INCREMENTO) {
    printf("================\n");
    printf("|   CELSIUS    |\n");
    printf("| A FAHRENHEIT |\n");
    printFilas(PISO_TABLA, TECHO_TABLA, INCREMENTO, fahrenheit);
}

void printTablaFahrenheit(int PISO_TABLA, int TECHO_TABLA, int INCREMENTO) {
    printf("================\n");
    printf("|  FAHRENHEIT  |\n");
    printf("|  A  CELSIUS  |\n");
    printFilas(PISO_TABLA, TECHO_TABLA, INCREMENTO, celsius);
}

void printTablas() {
    const int PISO_TABLA = 0;    // Grados iniciales de la tabla
    const int TECHO_TABLA = 300; // Grados maximos de la tabla
    const int INCREMENTO = 20;   // Incremento de grados por fila
    printTablaCelsius(PISO_TABLA, TECHO_TABLA, INCREMENTO);
    printTablaFahrenheit(PISO_TABLA, TECHO_TABLA, INCREMENTO);
}

int main(void) {
    printTablas();
    return 0;
}