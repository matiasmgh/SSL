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
int areEqual(double a, double b, double epsilon) {
    int returnValue;
    double diferencia = fabs(a - b);
    if(diferencia <= epsilon) {
        returnValue = 1;
    } else {
        returnValue = 0;
    }
    return returnValue;
}

void assertEqualFloatValue(double valorCalculado, double valorEsperado, double epsilon) {
    assert(areEqual(valorCalculado, valorEsperado, epsilon));
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

    //Valores de prueba.
    const double CERO_CELSIUS = 0.0;
    const double CERO_CELSIUS_A_FAHR = fahrenheit(CERO_CELSIUS);
    const double MENOS_CINCUENTA_CELSIUS = -50.0;
    const double MENOS_CINCUENTA_CELSIUS_A_FAHR = fahrenheit(MENOS_CINCUENTA_CELSIUS);
    const double TRESCIENTOS_CELSIUS = 300.0;
    const double TRESCIENTOS_CELSIUS_A_FAHR = fahrenheit(TRESCIENTOS_CELSIUS);

    //Tests.
    assertEqualFloatValue(CERO_CELSIUS_A_FAHR, 32.0, DIFERENCIA_ACEPTABLE);
    printSuccessfulMessage(CERO_CELSIUS);
    assertEqualFloatValue(MENOS_CINCUENTA_CELSIUS_A_FAHR, -58.0, DIFERENCIA_ACEPTABLE);
    printSuccessfulMessage(MENOS_CINCUENTA_CELSIUS);
    assertEqualFloatValue(TRESCIENTOS_CELSIUS_A_FAHR, 572.0, DIFERENCIA_ACEPTABLE);
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

    //Valores de prueba.
    const double CERO_FAHR = 0.0;
    const double CERO_FAHR_A_CELSIUS = celsius(CERO_FAHR);
    const double MENOS_CINCUENTA_FAHR = -50.0;
    const double MENOS_CINCUENTA_FAHR_A_CELSIUS = celsius(MENOS_CINCUENTA_FAHR);
    const double TRESCIENTOS_FAHR = 300.0;
    const double TRESCIENTOS_FAHR_A_CELSIUS = celsius(TRESCIENTOS_FAHR);
    
    //Tests.
    assertEqualFloatValue(CERO_FAHR_A_CELSIUS, -17.7778, DIFERENCIA_ACEPTABLE);
    printSuccessfulMessage(CERO_FAHR);
    assertEqualFloatValue(MENOS_CINCUENTA_FAHR_A_CELSIUS, -45.5556, DIFERENCIA_ACEPTABLE);
    printSuccessfulMessage(MENOS_CINCUENTA_FAHR);
    assertEqualFloatValue(TRESCIENTOS_FAHR_A_CELSIUS, 148.889, DIFERENCIA_ACEPTABLE);
    printSuccessfulMessage(TRESCIENTOS_FAHR);
}

int main(void) {
    testFahrenheitToCelsius();
    testCelsiusToFahrenheit();
    return 0;
}