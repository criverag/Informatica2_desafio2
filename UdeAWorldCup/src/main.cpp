#include <iostream>
#include <cstring>
#include "Seleccion.h"
#include "LectorCSV.h"

// ============================================================
// Función: mostrarMenu
// Imprime el menú principal del programa.
// ============================================================
void mostrarMenu() {
    std::cout << "\n========================================\n";
    std::cout << "   UdeAWorldCup — Menú Principal\n";
    std::cout << "========================================\n";
    std::cout << "  1. Cargar selecciones desde archivo\n";
    std::cout << "  2. Listar todas las selecciones\n";
    std::cout << "  3. Buscar selección por país\n";
    std::cout << "  0. Salir\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Seleccione una opción: ";
}

// ============================================================
// Función: leerOpcion
// Valida que el usuario ingrese un número en el rango dado.
// Si no lo hace, pide de nuevo.
// ============================================================
int leerOpcion(int min, int max) {
    int opcion;
    std::cin >> opcion;

    // Validación: mientras el valor esté fuera de rango, pedimos de nuevo
    while (opcion < min || opcion > max || std::cin.fail()) {
        std::cin.clear();             // Limpiamos error de cin
        std::cin.ignore(1000, '\n'); // Descartamos la entrada inválida
        std::cout << "[!] Opción inválida. Ingrese un número entre "
                  << min << " y " << max << ": ";
        std::cin >> opcion;
    }
    return opcion;
}

// ============================================================
// Función: buscarPorPais
// Recorre el arreglo de selecciones buscando coincidencia
// parcial en el nombre del país (búsqueda lineal simple).
// ============================================================
void buscarPorPais(Seleccion* selecciones, int cantidad) {
    char buscado[100];
    std::cout << "Ingrese el nombre del pais: ";
    std::cin.ignore();
    std::cin.getline(buscado, 100);

    bool encontrado = false;

    // Búsqueda lineal — O(n)
    for (int i = 0; i < cantidad; i++) {
        // Comparación manual carácter por carácter (sin strstr de STL)
        const char* haystack = selecciones[i].getPais();
        const char* needle   = buscado;

        // Buscamos 'needle' dentro de 'haystack'
        int hLen = strlen(haystack);
        int nLen = strlen(needle);

        for (int j = 0; j <= hLen - nLen; j++) {
            bool coincide = true;
            for (int k = 0; k < nLen && coincide; k++) {
                // Comparación insensible a mayúsculas/minúsculas
                char ch = haystack[j + k];
                char cn = needle[k];
                // Pasar a minúscula si es letra mayúscula
                if (ch >= 'A' && ch <= 'Z') ch += 32;
                if (cn >= 'A' && cn <= 'Z') cn += 32;
                if (ch != cn) coincide = false;
            }
            if (coincide) {
                selecciones[i].mostrar();
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {
        std::cout << "[!] No se encontro ninguna seleccion con ese nombre.\n";
    }
}

// ============================================================
// MAIN
// ============================================================
int main() {
    std::cout << "Bienvenido a UdeAWorldCup v0.2\n";
    std::cout << "Simulador del Mundial de Futbol FIFA 2026\n";

    // Puntero al arreglo dinámico — inicialmente vacío
    Seleccion* selecciones = nullptr;
    int cantidad = 0;
    bool cargado = false;

    int opcion;

    do {
        mostrarMenu();
        opcion = leerOpcion(0, 3);

        switch (opcion) {
            case 1: {
                // Si ya había datos cargados, los liberamos antes
                if (selecciones != nullptr) {
                    delete[] selecciones;
                    selecciones = nullptr;
                    std::cout << "[INFO] Datos anteriores liberados de memoria.\n";
                }

                // Ruta al archivo CSV
                const char* ruta = "data/selecciones_clasificadas_mundial.csv";
                selecciones = LectorCSV::cargarSelecciones(ruta, cantidad);

                if (selecciones != nullptr) cargado = true;
                break;
            }

            case 2: {
                if (!cargado || selecciones == nullptr) {
                    std::cout << "[!] Primero debe cargar los datos (opcion 1).\n";
                    break;
                }
                std::cout << "\n=== SELECCIONES CLASIFICADAS AL MUNDIAL 2026 ===\n";
                std::cout << "Total de equipos: " << cantidad << "\n\n";

                // Usamos el operator<< sobrecargado para imprimir
                for (int i = 0; i < cantidad; i++) {
                    std::cout << selecciones[i] << "\n";
                }
                break;
            }

            case 3: {
                if (!cargado || selecciones == nullptr) {
                    std::cout << "[!] Primero debe cargar los datos (opcion 1).\n";
                    break;
                }
                buscarPorPais(selecciones, cantidad);
                break;
            }

            case 0:
                std::cout << "\nCerrando el programa...\n";
                break;
        }

    } while (opcion != 0);

    // --- Liberar memoria al salir ---
    // Esto es fundamental: todo lo que reservamos con new[]
    // debe liberarse con delete[] para evitar memory leaks.
    if (selecciones != nullptr) {
        delete[] selecciones;
        selecciones = nullptr;
    }

    std::cout << "Memoria liberada. Hasta luego.\n";
    return 0;
}
