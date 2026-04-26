#ifndef LECTOR_ARCHIVO_H
#define LECTOR_ARCHIVO_H

#include "Seleccion.h"

// ============================================================
// Funciones para cargar y gestionar el arreglo dinamico
// de selecciones desde el archivo CSV.
// ============================================================

// Cuenta cuantas selecciones hay en el archivo (filas de datos)
int contarSelecciones(const char* ruta);

// Carga las selecciones del CSV en un arreglo dinamico
// Recibe puntero doble para poder asignar el arreglo desde afuera
// 'cantidad' se llena por referencia
Seleccion* cargarSelecciones(const char* ruta, int& cantidad);

// Libera la memoria del arreglo dinamico
void liberarSelecciones(Seleccion*& arreglo, int cantidad);

// Muestra el encabezado de la tabla en consola
void mostrarEncabezado();

// Muestra todas las selecciones del arreglo
void mostrarTodas(Seleccion* arreglo, int cantidad);

#endif
