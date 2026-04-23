#ifndef CARGADOR_CSV_H
#define CARGADOR_CSV_H

#include "Seleccion.h"

// ============================================================
// Funciones para cargar los datos del archivo CSV
// Se separaron en su propio módulo para mantener el orden
// (principio de responsabilidad única).
// ============================================================

// Elimina espacios al inicio y al final de un string
// Se necesita porque el CSV puede tener espacios raros
std::string limpiarTexto(const std::string& texto);

// Extrae el siguiente campo del CSV separado por ';'
// Usa un índice de posición para ir avanzando en la línea
std::string siguienteCampo(const std::string& linea, int& pos);

// Carga las selecciones desde el CSV y las almacena en el arreglo dinámico.
// Retorna la cantidad de selecciones leídas.
// El arreglo 'selecciones' es pasado por referencia de puntero
// porque necesitamos modificar el puntero original (asignarle memoria).
int cargarSeleccionesCSV(const std::string& rutaArchivo,
                         Seleccion*& selecciones);

#endif // CARGADOR_CSV_H
