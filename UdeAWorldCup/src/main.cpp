// ============================================================
// Proyecto: Gestor de Selecciones - Mundial de Fútbol 2026
// Autor: Estudiante C++
// Descripción: Programa que carga selecciones desde un archivo
//              CSV y permite consultar estadísticas básicas.
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// ---- Constantes ----
const int MAX_SELECCIONES = 60;  // Máximo de equipos posibles

// ---- Clase Seleccion ----
// Encapsula todos los datos de una selección nacional
class Seleccion {
private:
    int ranking;
    char pais[50];
    char tecnico[60];
    char confederacion[20];
    int golesAFavor;
    int golesEnContra;
    int ganados;
    int empatados;
    int perdidos;

public:
    // Constructor por defecto
    Seleccion() {
        ranking = 0;
        strcpy(pais, "");
        strcpy(tecnico, "");
        strcpy(confederacion, "");
        golesAFavor = 0;
        golesEnContra = 0;
        ganados = 0;
        empatados = 0;
        perdidos = 0;
    }

    // Setters
    void setRanking(int r)           { ranking = r; }
    void setPais(const char* p)      { strncpy(pais, p, 49); pais[49] = '\0'; }
    void setTecnico(const char* t)   { strncpy(tecnico, t, 59); tecnico[59] = '\0'; }
    void setConfederacion(const char* c) { strncpy(confederacion, c, 19); confederacion[19] = '\0'; }
    void setGolesAFavor(int g)       { golesAFavor = g; }
    void setGolesEnContra(int g)     { golesEnContra = g; }
    void setGanados(int g)           { ganados = g; }
    void setEmpatados(int e)         { empatados = e; }
    void setPerdidos(int p)          { perdidos = p; }

    // Getters
    int getRanking()           const { return ranking; }
    const char* getPais()      const { return pais; }
    const char* getTecnico()   const { return tecnico; }
    const char* getConfederacion() const { return confederacion; }
    int getGolesAFavor()       const { return golesAFavor; }
    int getGolesEnContra()     const { return golesEnContra; }
    int getGanados()           const { return ganados; }
    int getEmpatados()         const { return empatados; }
    int getPerdidos()          const { return perdidos; }

    // Calcula puntos (3 por victoria, 1 por empate)
    int calcularPuntos() const {
        return (ganados * 3) + empatados;
    }

    // Calcula diferencia de goles
    int calcularDiferenciaGoles() const {
        return golesAFavor - golesEnContra;
    }

    // Función amiga para imprimir con formato completo
    friend void imprimirSeleccion(const Seleccion& s);
};

// ---- Función amiga ----
void imprimirSeleccion(const Seleccion& s) {
    cout << "--------------------------------------------" << endl;
    cout << "  Ranking FIFA : " << s.ranking << endl;
    cout << "  País         : " << s.pais << endl;
    cout << "  Técnico      : " << s.tecnico << endl;
    cout << "  Confederación: " << s.confederacion << endl;
    cout << "  Goles a favor: " << s.golesAFavor << endl;
    cout << "  Goles en cont: " << s.golesEnContra << endl;
    cout << "  Dif. de goles: " << s.calcularDiferenciaGoles() << endl;
    cout << "  G / E / P    : " << s.ganados << " / "
         << s.empatados << " / " << s.perdidos << endl;
    cout << "  Puntos       : " << s.calcularPuntos() << endl;
    cout << "--------------------------------------------" << endl;
}

// ---- Función: leerCSV ----
// Lee el archivo CSV y llena el arreglo dinámico de selecciones
// Retorna la cantidad de selecciones leídas
// Parámetros:
//   - selecciones: puntero al arreglo dinámico (por referencia)
//   - nombreArchivo: ruta del archivo CSV
int leerCSV(Seleccion*& selecciones, const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << nombreArchivo << endl;
        return 0;
    }

    string linea;
    int contador = 0;

    // Saltar las dos primeras líneas (encabezados)
    getline(archivo, linea); // título
    getline(archivo, linea); // cabeceras de columnas

    // Contar primero cuántas líneas hay para reservar memoria exacta
    // (buena práctica: no desperdiciar memoria)
    int totalLineas = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) totalLineas++;
    }

    // Reservar memoria dinámica exacta
    selecciones = new Seleccion[totalLineas];

    // Volver al inicio y saltar encabezados de nuevo
    archivo.clear();
    archivo.seekg(0);
    getline(archivo, linea);
    getline(archivo, linea);

    // Leer cada fila del CSV
    while (getline(archivo, linea) && contador < totalLineas) {
        if (linea.empty()) continue;

        // Quitar salto de línea en Windows (\r)
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        // Parsear manualmente por punto y coma
        // Columnas: ranking;pais;tecnico;federacion;confederacion;
        //           golesAFavor;golesEnContra;ganados;empatados;perdidos
        char buffer[300];
        strncpy(buffer, linea.c_str(), 299);

        char* token = strtok(buffer, ";");
        int col = 0;
        int ranking = 0;
        char pais[50], tecnico[60], federacion[80], confederacion[20];
        int gf = 0, gc = 0, g = 0, e = 0, p = 0;

        while (token != nullptr) {
            switch (col) {
                case 0: ranking = atoi(token); break;
                case 1: strncpy(pais, token, 49); break;
                case 2: strncpy(tecnico, token, 59); break;
                case 3: strncpy(federacion, token, 79); break;
                case 4: strncpy(confederacion, token, 19); break;
                case 5: gf = atoi(token); break;
                case 6: gc = atoi(token); break;
                case 7: g  = atoi(token); break;
                case 8: e  = atoi(token); break;
                case 9: p  = atoi(token); break;
            }
            col++;
            token = strtok(nullptr, ";");
        }

        // Cargar datos en el objeto
        selecciones[contador].setRanking(ranking);
        selecciones[contador].setPais(pais);
        selecciones[contador].setTecnico(tecnico);
        selecciones[contador].setConfederacion(confederacion);
        selecciones[contador].setGolesAFavor(gf);
        selecciones[contador].setGolesEnContra(gc);
        selecciones[contador].setGanados(g);
        selecciones[contador].setEmpatados(e);
        selecciones[contador].setPerdidos(p);

        contador++;
    }

    archivo.close();
    return contador;
}

// ---- Función: buscarPorPais ----
// Busca una selección por nombre de país (sin distinguir mayúsculas)
// Retorna el índice encontrado o -1 si no existe
int buscarPorPais(Seleccion* selecciones, int total, const char* busqueda) {
    for (int i = 0; i < total; i++) {
        // Comparación simple ignorando mayúsculas
        const char* nombre = selecciones[i].getPais();
        int j = 0;
        bool igual = true;

        if (strlen(nombre) != strlen(busqueda)) continue;

        while (nombre[j] != '\0') {
            char a = (nombre[j] >= 'A' && nombre[j] <= 'Z') ? nombre[j] + 32 : nombre[j];
            char b = (busqueda[j] >= 'A' && busqueda[j] <= 'Z') ? busqueda[j] + 32 : busqueda[j];
            if (a != b) { igual = false; break; }
            j++;
        }

        if (igual) return i;
    }
    return -1;
}

// ---- Función: listarPorConfederacion ----
// Imprime todas las selecciones de una confederación dada
void listarPorConfederacion(Seleccion* selecciones, int total, const char* conf) {
    bool encontrado = false;
    cout << "\n=== Selecciones de la confederacion: " << conf << " ===" << endl;
    for (int i = 0; i < total; i++) {
        // Comparar confederación (simple, case-sensitive)
        if (strcmp(selecciones[i].getConfederacion(), conf) == 0) {
            cout << " - " << selecciones[i].getPais()
                 << " (Ranking: " << selecciones[i].getRanking()
                 << ", Puntos: " << selecciones[i].calcularPuntos() << ")" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << " No se encontraron selecciones para esa confederación." << endl;
    }
}

// ---- Función: mostrarTop ----
// Muestra los N primeros equipos por ranking FIFA
void mostrarTop(Seleccion* selecciones, int total, int n) {
    if (n > total) n = total;
    cout << "\n=== TOP " << n << " Selecciones por Ranking FIFA ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << selecciones[i].getPais()
             << " (Ranking: " << selecciones[i].getRanking()
             << ", Puntos: " << selecciones[i].calcularPuntos() << ")" << endl;
    }
}

// ---- Función: validarOpcionMenu ----
// Valida que la opción del usuario esté en el rango [1, max]
int validarOpcionMenu(int min, int max) {
    int opcion;
    bool valido = false;
    while (!valido) {
        cout << "Ingresa tu opcion: ";
        if (cin >> opcion) {
            if (opcion >= min && opcion <= max) {
                valido = true;
            } else {
                cout << "[!] Opción fuera de rango. Intenta de nuevo." << endl;
            }
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[!] Entrada inválida. Solo números." << endl;
        }
    }
    return opcion;
}

// ---- Función principal: mostrarMenu ----
void mostrarMenu() {
    cout << "\n==============================" << endl;
    cout << "  MUNDIAL DE FUTBOL 2026" << endl;
    cout << "==============================" << endl;
    cout << "1. Ver Top N selecciones" << endl;
    cout << "2. Buscar seleccion por pais" << endl;
    cout << "3. Listar por confederacion" << endl;
    cout << "4. Salir" << endl;
    cout << "------------------------------" << endl;
}

// ---- MAIN ----
int main() {
    const char* archivoCSV = "data/selecciones_clasificadas_mundial.csv";

    // Puntero para arreglo dinámico (heap)
    Seleccion* selecciones = nullptr;

    cout << "Cargando datos del archivo..." << endl;
    int total = leerCSV(selecciones, archivoCSV);

    if (total == 0) {
        cout << "No se cargaron datos. Verifica el archivo CSV." << endl;
        return 1;
    }

    cout << "Se cargaron " << total << " selecciones correctamente." << endl;

    int opcion = 0;
    do {
        mostrarMenu();
        opcion = validarOpcionMenu(1, 4);

        switch (opcion) {
            case 1: {
                int n = 0;
                cout << "¿Cuántas selecciones quieres ver? (1-" << total << "): ";
                cin >> n;
                if (n < 1) n = 1;
                if (n > total) n = total;
                mostrarTop(selecciones, total, n);
                break;
            }
            case 2: {
                char busqueda[50];
                cin.ignore();
                cout << "Ingresa el nombre del pais (en inglés): ";
                cin.getline(busqueda, 50);
                int idx = buscarPorPais(selecciones, total, busqueda);
                if (idx != -1) {
                    imprimirSeleccion(selecciones[idx]);
                } else {
                    cout << "[!] No se encontró la selección: " << busqueda << endl;
                }
                break;
            }
            case 3: {
                cout << "Confederaciones disponibles:" << endl;
                cout << "  UEFA, CONMEBOL, CAF, AFC, Concacaf, OFC" << endl;
                char conf[20];
                cin.ignore();
                cout << "Ingresa la confederacion: ";
                cin.getline(conf, 20);
                listarPorConfederacion(selecciones, total, conf);
                break;
            }
            case 4:
                cout << "\n¡Hasta luego! Mundial 2026 🏆" << endl;
                break;
        }

    } while (opcion != 4);

    // Liberar memoria dinámica
    delete[] selecciones;
    selecciones = nullptr;

    return 0;
}
