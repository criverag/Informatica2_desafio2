#include "menu.h"
#include "lectorArchivo.h"
#include <iostream>
#include <algorithm>  // solo para tolower
#include <limits>

// -------------------------------------------------------
// toLowerStr: convierte un string a minusculas
// Se usa para comparar sin importar mayusculas
// -------------------------------------------------------
static std::string toLowerStr(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = std::tolower(c);
    return result;
}

// -------------------------------------------------------
// mostrarMenu: imprime las opciones disponibles
// -------------------------------------------------------
int mostrarMenu() {
    std::cout << "\n========================================\n";
    std::cout << "  MUNDIAL 2026 - Selecciones Clasificadas\n";
    std::cout << "========================================\n";
    std::cout << "1. Ver todas las selecciones\n";
    std::cout << "2. Buscar seleccion por pais\n";
    std::cout << "3. Filtrar por confederacion\n";
    std::cout << "4. Top 10 por puntos\n";
    std::cout << "0. Salir\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Elige una opcion: ";

    return pedirOpcionValida(0, 4);
}

// -------------------------------------------------------
// pedirOpcionValida: asegura que el usuario ingrese un
// numero entero dentro del rango permitido.
// Se repite hasta que la entrada sea correcta.
// -------------------------------------------------------
int pedirOpcionValida(int min, int max) {
    int opcion;
    while (true) {
        std::cin >> opcion;

        // Verificar si la lectura fue exitosa
        if (std::cin.fail()) {
            std::cin.clear(); // limpiar estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Ingresa un numero entre "
                      << min << " y " << max << ": ";
        } else if (opcion < min || opcion > max) {
            std::cout << "Opcion fuera de rango. Ingresa entre "
                      << min << " y " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return opcion;
        }
    }
}

// -------------------------------------------------------
// buscarPorPais: recorre el arreglo buscando el pais
// Compara en minusculas para mayor flexibilidad
// -------------------------------------------------------
int buscarPorPais(Seleccion* arreglo, int cantidad, const std::string& nombre) {
    std::string busq = toLowerStr(nombre);
    for (int i = 0; i < cantidad; i++) {
        if (toLowerStr(arreglo[i].getPais()) == busq) {
            return i;
        }
    }
    return -1; // no encontrado
}

// -------------------------------------------------------
// filtrarPorConfederacion: muestra solo las selecciones
// que pertenecen a la confederacion indicada
// -------------------------------------------------------
void filtrarPorConfederacion(Seleccion* arreglo, int cantidad,
                              const std::string& conf) {
    std::string busq = toLowerStr(conf);
    bool encontrado = false;

    mostrarEncabezado();
    for (int i = 0; i < cantidad; i++) {
        if (toLowerStr(arreglo[i].getConfederacion()) == busq) {
            arreglo[i].mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron selecciones para: " << conf << "\n";
    }
}

// -------------------------------------------------------
// ordenarPorPuntos: burbuja simple de mayor a menor puntos
// Si empatan en puntos, se usa diferencia de goles
// -------------------------------------------------------
void ordenarPorPuntos(Seleccion* arreglo, int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            bool intercambiar = false;
            if (arreglo[j].getPuntos() < arreglo[j+1].getPuntos()) {
                intercambiar = true;
            } else if (arreglo[j].getPuntos() == arreglo[j+1].getPuntos() &&
                       arreglo[j].getDiferencia() < arreglo[j+1].getDiferencia()) {
                intercambiar = true;
            }
            if (intercambiar) {
                Seleccion temp = arreglo[j];
                arreglo[j]     = arreglo[j+1];
                arreglo[j+1]   = temp;
            }
        }
    }
}

// -------------------------------------------------------
// mostrarTopN: ordena por puntos y muestra las primeras N
// -------------------------------------------------------
void mostrarTopN(Seleccion* arreglo, int cantidad, int n) {
    // Creamos una copia dinamica para no alterar el orden original
    Seleccion* copia = new Seleccion[cantidad];
    for (int i = 0; i < cantidad; i++) copia[i] = arreglo[i];

    ordenarPorPuntos(copia, cantidad);

    int limite = (n < cantidad) ? n : cantidad;
    std::cout << "\n--- Top " << limite << " por puntos ---\n";
    mostrarEncabezado();
    for (int i = 0; i < limite; i++) {
        copia[i].mostrar();
    }

    // Liberar la copia para no tener fuga de memoria
    delete[] copia;
    copia = nullptr;
}
