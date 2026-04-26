#ifndef MENU_H
#define MENU_H

#include "Seleccion.h"

// ============================================================
// Funciones del menu interactivo y busquedas
// ============================================================

// Muestra el menu principal y devuelve la opcion elegida
int mostrarMenu();

// Valida que la opcion este en el rango [min, max]
int pedirOpcionValida(int min, int max);

// Busca una seleccion por nombre de pais (no sensible a mayusculas)
// Devuelve el indice en el arreglo, o -1 si no se encuentra
int buscarPorPais(Seleccion* arreglo, int cantidad, const std::string& nombre);

// Filtra y muestra selecciones por confederacion
void filtrarPorConfederacion(Seleccion* arreglo, int cantidad,
                              const std::string& conf);

// Muestra las top N selecciones por puntos (orden descendente)
void mostrarTopN(Seleccion* arreglo, int cantidad, int n);

// Ordena el arreglo por puntos de mayor a menor (burbuja simple)
void ordenarPorPuntos(Seleccion* arreglo, int cantidad);

#endif
