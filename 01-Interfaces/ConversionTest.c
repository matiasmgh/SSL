/**
 * @file ConversionTest.c
 * @author mgaiteiroharriague (mgaiteiroharriague@frba.utn.edu.ar)
 * @brief Pruebas unitarias para la implementacion de la interfaz de Conversion.
 * @version 0.1
 * @date 2022-05-14
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "Conversion.h"

/**
 * @brief Evalua si dos doubles son iguales, con un epsilon de diferencia aceptable.
 *
 * @param a un valor double
 * @param b otro valor double
 * @param epsilon la maxima diferencia aceptable.
 * 
 * @return true Si la diferencia entre los dos valores es menor o igual al epsilon.
 * @return false Si la diferencia entre los dos valores es mayor al epsilon.
 */
bool areEqual(double a, double b, double epsilon) {
    bool returnValue;
    double diferencia = fabs(a - b);
    if(diferencia <= epsilon) {
        returnValue = true;
    } else {
        returnValue = false;
    }
    return returnValue;
}

void printSuccessfulMessage(double valorCalculado) {
    printf("%4.1f se calculo correctamente \n", valorCalculado);
}

/**
 * @brief Test de la funcion fahrenheit, que convierte grados celsius a fahrenheit.
 * Se testea para los valores 0°C, -50.0°C y 300.0°C
 */
void testCelsiusToFahrenheit() {
    printf("TESTS DE CONVERSION DE Celsius A Fahrenheit: \n");
    //Epsilon de referencia.
    const double DIFERENCIA_ACEPTABLE = 0.0002;
    double valorEsperado;

    //Valores de prueba.
    const double CERO_CELSIUS = 0.0;
    const double CERO_CELSIUS_A_FAHR = fahrenheit(CERO_CELSIUS);
    valorEsperado = 32.0;

    //Tests.
    assert(areEqual(CERO_CELSIUS_A_FAHR, valorEsperado, DIFERENCIA_ACEPTABLE));
    printSuccessfulMessage(CERO_CELSIUS);

    const double MENOS_CINCUENTA_CELSIUS = -50.0;
    const double MENOS_CINCUENTA_CELSIUS_A_FAHR = fahrenheit(MENOS_CINCUENTA_CELSIUS);
    valorEsperado = -58.0;
    assert(areEqual(MENOS_CINCUENTA_CELSIUS_A_FAHR, valorEsperado, DIFERENCIA_ACEPTABLE));
    printSuccessfulMessage(MENOS_CINCUENTA_CELSIUS);

    const double TRESCIENTOS_CELSIUS = 300.0;
    const double TRESCIENTOS_CELSIUS_A_FAHR = fahrenheit(TRESCIENTOS_CELSIUS);
    valorEsperado = 572.0;
    assert(areEqual(TRESCIENTOS_CELSIUS_A_FAHR, valorEsperado, DIFERENCIA_ACEPTABLE));
    printSuccessfulMessage(TRESCIENTOS_CELSIUS);
}

/**
 * @brief Test de la funcion celsius, que convierte grados fahrenheit a celsius.
 * Se testea para los valores 0°C, -50.0°C y 300.0°C
 */
void testFahrenheitToCelsius() {
    printf("TESTS DE CONVERSION DE Fahrenheit A Celsius: \n");
    
    //Epsilon de referencia.
    const double DIFERENCIA_ACEPTABLE = 0.0002;
    double valorEsperado;

    //Valores de prueba.
    const double CERO_FAHR = 0.0;
    const double CERO_FAHR_A_CELSIUS = celsius(CERO_FAHR);
    valorEsperado = -17.7778;

    //Tests.
    assert(areEqual(CERO_FAHR_A_CELSIUS, valorEsperado, DIFERENCIA_ACEPTABLE));
    printSuccessfulMessage(CERO_FAHR);

    const double MENOS_CINCUENTA_FAHR = -50.0;
    const double MENOS_CINCUENTA_FAHR_A_CELSIUS = celsius(MENOS_CINCUENTA_FAHR);
    valorEsperado = -45.5556;
    assert(areEqual(MENOS_CINCUENTA_FAHR_A_CELSIUS, valorEsperado, DIFERENCIA_ACEPTABLE));
    printSuccessfulMessage(MENOS_CINCUENTA_FAHR);

    const double TRESCIENTOS_FAHR = 300.0;
    const double TRESCIENTOS_FAHR_A_CELSIUS = celsius(TRESCIENTOS_FAHR);
    valorEsperado = 148.889;
    assert(areEqual(TRESCIENTOS_FAHR_A_CELSIUS, valorEsperado, DIFERENCIA_ACEPTABLE));
    printSuccessfulMessage(TRESCIENTOS_FAHR);
}

int main(void) {
    testFahrenheitToCelsius();
    testCelsiusToFahrenheit();
    return 0;
}