/**
 * @file Conversion.c
 * @author mgaiteiroharriague (mgaiteiroharriague@frba.utn.edu.ar)
 * @brief Implementacion/Proveedor de Interfaz Conversion.h
 * @version 0.1
 * @date 2022-05-10
 * 
 */

#include <stdio.h>
#include "Conversion.h"

/**
 * @brief Convierte grados fahrenheit a celsius.
 * 
 * @param gradosFahr la medida en grados fahrenheit a convertir
 * @return la medida en grados celsius
 */
double celsius(double gradosFahr) {
    return (5.0/9.0)*(gradosFahr - 32.0);
}

/**
 * @brief Convierte grados celsius a fahrenheit.
 * 
 * @param gradosCelsius la medida en grados celsius a convertir
 * @return la medida en grados fahrenheit
 */
double fahrenheit(double gradosCelsius) {
    return gradosCelsius * (9.0/5.0) + 32.0;
}
