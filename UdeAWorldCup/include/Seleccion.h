#ifndef SELECCION_H
#define SELECCION_H

#include <iostream>
#include <fstream>

// ============================================================
// Clase Seleccion
// Representa a un equipo clasificado al Mundial de Fútbol 2026.
// Almacena los datos históricos leídos desde el archivo CSV.
// ============================================================
class Seleccion {
private:
    // --- Datos de identidad ---
    char* pais;            // Nombre del país (memoria dinámica)
    char* directorTecnico; // Nombre del DT
    char* federacion;      // Federación nacional
    char* confederacion;   // Confederación continental (UEFA, CONMEBOL, etc.)

    // --- Datos de ranking y estadísticas históricas ---
    int rankingFIFA;
    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;

    // Tarjetas y faltas (inicialmente en cero según el enunciado)
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

    // --- Función auxiliar privada ---
    // Copia un string en memoria dinámica
    char* copiarCadena(const char* origen) const;

public:
    // Constructor por defecto
    Seleccion();

    // Constructor con parámetros
    Seleccion(int ranking, const char* pais, const char* dt,
              const char* fed, const char* conf,
              int gf, int gc, int pg, int pe, int pp);

    // Constructor de copia
    Seleccion(const Seleccion& otra);

    // Destructor — libera la memoria dinámica
    ~Seleccion();

    // Operador de asignación
    Seleccion& operator=(const Seleccion& otra);

    // --- Getters ---
    int         getRanking()          const;
    const char* getPais()             const;
    const char* getDT()               const;
    const char* getFederacion()       const;
    const char* getConfederacion()    const;
    int         getGolesAFavor()      const;
    int         getGolesEnContra()    const;
    int         getPartidosGanados()  const;
    int         getPartidosEmpatados()const;
    int         getPartidosPerdidos() const;

    // --- Setters para actualizar estadísticas ---
    void agregarGolAFavor();
    void agregarGolEnContra();
    void registrarPartido(bool gano, bool empato);

    // --- Sobrecarga de operadores ---
    // Compara dos selecciones por ranking FIFA
    bool operator<(const Seleccion& otra) const;
    bool operator==(const Seleccion& otra) const;

    // Imprime los datos por consola
    void mostrar() const;

    // Función amiga: imprime la selección con formato especial
    friend std::ostream& operator<<(std::ostream& out, const Seleccion& s);
};

#endif
