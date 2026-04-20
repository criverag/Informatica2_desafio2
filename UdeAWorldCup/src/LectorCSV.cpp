#include "LectorCSV.h"
#include <fstream>
#include <iostream>
#include <cstring>

// ============================================================
// parsearCampo
// Lee caracteres desde 'linea' a partir de la posición 'pos'
// hasta encontrar ';' o fin de línea, y guarda el resultado
// en 'destino'.
// ============================================================
void LectorCSV::parsearCampo(const char* linea, int& pos,
                              char* destino, int maxLen) {
    int i = 0;
    // Leemos hasta encontrar ';', '\n', '\r' o fin de cadena
    while (linea[pos] != ';' && linea[pos] != '\n' &&
           linea[pos] != '\r' && linea[pos] != '\0' &&
           i < maxLen - 1) {
        destino[i++] = linea[pos++];
    }
    destino[i] = '\0'; // Terminador de cadena

    // Avanzamos el separador ';' si existe
    if (linea[pos] == ';') pos++;
}

// ============================================================
// parsearEntero
// Lee dígitos consecutivos y los convierte a int.
// ============================================================
int LectorCSV::parsearEntero(const char* linea, int& pos) {
    int resultado = 0;
    bool negativo = false;

    if (linea[pos] == '-') {
        negativo = true;
        pos++;
    }

    while (linea[pos] >= '0' && linea[pos] <= '9') {
        // Conversión manual: '5' - '0' = 5
        resultado = resultado * 10 + (linea[pos] - '0');
        pos++;
    }

    // Saltamos el ';' si lo hay
    if (linea[pos] == ';') pos++;

    return negativo ? -resultado : resultado;
}

// ============================================================
// cargarSelecciones
// Abre el CSV, salta las 2 primeras líneas (encabezados),
// y lee cada línea como un objeto Seleccion.
// Retorna un arreglo dinámico — el llamador debe hacer delete[].
// ============================================================
Seleccion* LectorCSV::cargarSelecciones(const char* rutaArchivo,
                                         int& cantidad) {
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        std::cout << "[ERROR] No se pudo abrir el archivo: "
                  << rutaArchivo << "\n";
        cantidad = 0;
        return nullptr;
    }

    // --- Paso 1: contar las líneas de datos (saltando los 2 encabezados) ---
    int totalLineas = 0;
    char lineaTemp[512];

    // Saltamos la línea del título y la de los nombres de columnas
    archivo.getline(lineaTemp, 512); // "Selecciones clasificadas..."
    archivo.getline(lineaTemp, 512); // "Ranking FIFA;País;..."

    while (archivo.getline(lineaTemp, 512)) {
        // Solo contamos líneas con contenido real
        if (strlen(lineaTemp) > 2) totalLineas++;
    }

    if (totalLineas == 0) {
        std::cout << "[ERROR] El archivo no contiene datos.\n";
        cantidad = 0;
        archivo.close();
        return nullptr;
    }

    // --- Paso 2: reservar el arreglo dinámico ---
    // Usamos new[] en el heap porque no sabemos el tamaño en tiempo
    // de compilación. Un arreglo en el stack requeriría tamaño fijo.
    Seleccion* selecciones = new Seleccion[totalLineas];

    // --- Paso 3: volver al inicio y releer ---
    archivo.clear();
    archivo.seekg(0, std::ios::beg);

    // Saltamos encabezados de nuevo
    archivo.getline(lineaTemp, 512);
    archivo.getline(lineaTemp, 512);

    int indice = 0;
    char bufTexto[256];

    while (indice < totalLineas && archivo.getline(lineaTemp, 512)) {
        // Ignorar líneas vacías o con solo \r
        if (strlen(lineaTemp) < 2) continue;

        int pos = 0; // posición actual dentro de la línea

        // --- Columna 1: Ranking FIFA (entero) ---
        int ranking = parsearEntero(lineaTemp, pos);

        // --- Columna 2: País ---
        parsearCampo(lineaTemp, pos, bufTexto, 256);
        char pais[256];
        strcpy(pais, bufTexto);

        // --- Columna 3: Director Técnico ---
        parsearCampo(lineaTemp, pos, bufTexto, 256);
        char dt[256];
        strcpy(dt, bufTexto);

        // --- Columna 4: Federación ---
        parsearCampo(lineaTemp, pos, bufTexto, 256);
        char fed[256];
        strcpy(fed, bufTexto);

        // --- Columna 5: Confederación ---
        parsearCampo(lineaTemp, pos, bufTexto, 256);
        char conf[256];
        strcpy(conf, bufTexto);

        // --- Columna 6: Goles a favor ---
        int gf = parsearEntero(lineaTemp, pos);

        // --- Columna 7: Goles en contra ---
        int gc = parsearEntero(lineaTemp, pos);

        // --- Columna 8: Partidos ganados ---
        int pg = parsearEntero(lineaTemp, pos);

        // --- Columna 9: Partidos empatados ---
        int pe = parsearEntero(lineaTemp, pos);

        // --- Columna 10: Partidos perdidos ---
        int pp = parsearEntero(lineaTemp, pos);

        // Construimos la selección usando el constructor con parámetros
        selecciones[indice] = Seleccion(ranking, pais, dt, fed, conf,
                                        gf, gc, pg, pe, pp);
        indice++;
    }

    archivo.close();
    cantidad = indice;

    std::cout << "[OK] Se cargaron " << cantidad
              << " selecciones desde el archivo.\n";

    return selecciones;
}
