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

double celsius(double gradosFahr) {
    return (5.0/9.0)*(gradosFahr - 32.0);
}

double fahrenheit(double gradosCelsius) {
    return gradosCelsius * (9.0/5.0) + 32.0;
}
