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
    double diferenciaAceptable = 0.0002;

    //Valores de prueba.
    double celsiusACalcular = 0.0;
    double celsiusToFahr = fahrenheit(celsiusACalcular);
    double valorEsperado = 32.0;

    //Tests.
    assert(areEqual(celsiusToFahr, valorEsperado, diferenciaAceptable));
    printSuccessfulMessage(celsiusACalcular);

    celsiusACalcular = -50.0;
    celsiusToFahr = fahrenheit(celsiusACalcular);
    valorEsperado = -58.0;
    assert(areEqual(celsiusToFahr, valorEsperado, diferenciaAceptable));
    printSuccessfulMessage(celsiusACalcular);

    celsiusACalcular = 300.0;
    celsiusToFahr = fahrenheit(celsiusACalcular);
    valorEsperado = 572.0;
    assert(areEqual(celsiusToFahr, valorEsperado, diferenciaAceptable));
    printSuccessfulMessage(celsiusACalcular);
}

/**
 * @brief Test de la funcion celsius, que convierte grados fahrenheit a celsius.
 * Se testea para los valores 0°C, -50.0°C y 300.0°C
 */
void testFahrenheitToCelsius() {
    printf("TESTS DE CONVERSION DE Fahrenheit A Celsius: \n");
    
    //Epsilon de referencia.
    double diferenciaAceptable = 0.0002;

    //Valores de prueba.
    double fahrACalcular = 0.0;
    double fahrToCelsius = celsius(fahrACalcular);
    double valorEsperado = -17.7778;

    //Tests.
    assert(areEqual(fahrToCelsius, valorEsperado, diferenciaAceptable));
    printSuccessfulMessage(fahrACalcular);

    fahrACalcular = -50.0;
    fahrToCelsius = celsius(fahrACalcular);
    valorEsperado = -45.5556;
    assert(areEqual(fahrToCelsius, valorEsperado, diferenciaAceptable));
    printSuccessfulMessage(fahrACalcular);

    fahrACalcular = 300.0;
    fahrToCelsius = celsius(fahrACalcular);
    valorEsperado = 148.889;
    assert(areEqual(fahrToCelsius, valorEsperado, diferenciaAceptable));
    printSuccessfulMessage(fahrACalcular);
}

int main(void) {
    testFahrenheitToCelsius();
    testCelsiusToFahrenheit();
    return 0;
}