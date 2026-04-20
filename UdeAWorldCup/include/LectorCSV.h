#ifndef LECTORCSV_H
#define LECTORCSV_H

#include "Seleccion.h"

// ============================================================
// Clase LectorCSV
// Responsabilidad única: leer el archivo CSV y construir
// el arreglo dinámico de selecciones clasificadas.
//
// Por qué una clase aparte:
// Sepada la lectura de archivos de la lógica del equipo
// hace el código más limpio y fácil de mantener.|
// ============================================================
class LectorCSV {
private:
    // Parsea un campo del CSV, teniendo en cuenta el ';'
    // Llena 'destino' con el texto leído y avanza el puntero.
    static void parsearCampo(const char* linea, int& pos,
                             char* destino, int maxLen);

    // Parsea un número entero desde la línea
    static int parsearEntero(const char* linea, int& pos);

public:
    // Lee el archivo CSV y crea un arreglo dinámico de Seleccion.
    // 'cantidad' se actualiza con el número real de equipos leídos.
    // El llamador es responsable de liberar el arreglo con delete[].
    static Seleccion* cargarSelecciones(const char* rutaArchivo,
                                        int& cantidad);
};

#endif
