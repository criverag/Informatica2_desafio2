#include "lectorArchivo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

// -------------------------------------------------------
// Funcion auxiliar: divide una linea CSV por el separador ';'
// y guarda los campos en un arreglo de strings
// -------------------------------------------------------
static int dividirLinea(const std::string& linea, std::string campos[], int maxCampos) {
    std::stringstream ss(linea);
    std::string token;
    int i = 0;
    while (std::getline(ss, token, ';') && i < maxCampos) {
        campos[i++] = token;
    }
    return i;
}

// -------------------------------------------------------
// contarSelecciones: abre el archivo y cuenta cuantas
// filas de datos validas hay (omite encabezados)
// Devuelve 0 si no se puede abrir el archivo.
// -------------------------------------------------------
int contarSelecciones(const char* ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo: " << ruta << "\n";
        return 0;
    }

    std::string linea;
    int count = 0;

    // Saltar las dos primeras lineas (titulo y encabezado de columnas)
    std::getline(archivo, linea);
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        if (!linea.empty()) count++;
    }

    archivo.close();
    return count;
}

// -------------------------------------------------------
// cargarSelecciones: lee el CSV y construye un arreglo
// dinamico de objetos Seleccion.
// MEMORIA DINAMICA: usamos 'new' porque no sabemos en
// tiempo de compilacion cuantas selecciones hay.
// -------------------------------------------------------
Seleccion* cargarSelecciones(const char* ruta, int& cantidad) {
    cantidad = contarSelecciones(ruta);
    if (cantidad == 0) return nullptr;

    // Reservamos memoria en el heap para 'cantidad' objetos
    Seleccion* arreglo = new Seleccion[cantidad];

    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        delete[] arreglo;
        return nullptr;
    }

    std::string linea;
    // Saltar titulo y encabezado
    std::getline(archivo, linea);
    std::getline(archivo, linea);

    int idx = 0;
    while (std::getline(archivo, linea) && idx < cantidad) {
        if (linea.empty()) continue;

        // Eliminar posible '\r' al final (archivos Windows)
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        std::string campos[10];
        int n = dividirLinea(linea, campos, 10);

        if (n >= 10) {
            int ranking = std::stoi(campos[0]);
            int gf      = std::stoi(campos[5]);
            int gc      = std::stoi(campos[6]);
            int g       = std::stoi(campos[7]);
            int e       = std::stoi(campos[8]);
            int p       = std::stoi(campos[9]);

            arreglo[idx] = Seleccion(ranking, campos[1], campos[2],
                                     campos[4], gf, gc, g, e, p);
            idx++;
        }
    }

    archivo.close();
    cantidad = idx; // ajustar por si alguna fila estaba malformada
    return arreglo;
}

// -------------------------------------------------------
// liberarSelecciones: libera el arreglo del heap
// IMPORTANTE: siempre usamos delete[] cuando usamos new[]
// para evitar fugas de memoria.
// -------------------------------------------------------
void liberarSelecciones(Seleccion*& arreglo, int cantidad) {
    if (arreglo != nullptr) {
        delete[] arreglo;
        arreglo = nullptr; // buena practica: evitar puntero colgante
    }
}

// -------------------------------------------------------
// mostrarEncabezado: imprime la cabecera de la tabla
// -------------------------------------------------------
void mostrarEncabezado() {
    std::cout << "\n";
    std::cout << std::left
              << std::setw(5)  << "FIFA"
              << std::setw(22) << "Pais"
              << std::setw(15) << "Confederacion"
              << std::setw(4)  << "Pts"
              << std::setw(4)  << "GF"
              << std::setw(4)  << "GC"
              << std::setw(6)  << "DG"
              << "\n";
    std::cout << std::string(60, '-') << "\n";
}

// -------------------------------------------------------
// mostrarTodas: recorre el arreglo y muestra cada seleccion
// -------------------------------------------------------
void mostrarTodas(Seleccion* arreglo, int cantidad) {
    mostrarEncabezado();
    for (int i = 0; i < cantidad; i++) {
        arreglo[i].mostrar();
    }
}
