#ifndef SELECCION_H
#define SELECCION_H

#include <iostream>
#include <string>
#include "Jugador.h"

// ============================================================
// Clase Seleccion
// Representa una selección nacional clasificada al Mundial 2026.
// Usa memoria dinámica para gestionar el arreglo de jugadores
// (en el heap con new/delete[]).
// ============================================================
class Seleccion {
private:
    // Datos generales del equipo
    int    rankingFIFA;
    std::string pais;
    std::string directorTecnico;
    std::string federacion;
    std::string confederacion;

    // Estadísticas históricas del equipo
    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;

    // Estadísticas que empiezan en cero
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

    // Plantilla de jugadores (memoria dinámica)
    // Se usa un arreglo dinámico porque el número de jugadores
    // no se conoce en tiempo de compilación (podría cambiar).
    Jugador* jugadores;
    int cantidadJugadores;

    // Número máximo de jugadores por equipo
    static const int MAX_JUGADORES = 26;

public:
    // Constructor por defecto
    Seleccion();

    // Constructor con parámetros: recibe datos leídos del CSV
    Seleccion(int ranking, const std::string& pais,
              const std::string& dt, const std::string& fed,
              const std::string& conf,
              int gf, int gc, int pg, int pe, int pp);

    // Constructor de copia (necesario porque usamos memoria dinámica)
    Seleccion(const Seleccion& otra);

    // Destructor: libera la memoria dinámica del arreglo de jugadores
    ~Seleccion();

    // Operador de asignación (para evitar fugas de memoria en copias)
    Seleccion& operator=(const Seleccion& otra);

    // Fabrica artificialmente la plantilla de 26 jugadores
    // y reparte los goles históricos de forma uniforme
    void fabricarJugadores();

    // --- Getters ---
    int getRankingFIFA() const;
    std::string getPais() const;
    std::string getDirectorTecnico() const;
    std::string getFederacion() const;
    std::string getConfederacion() const;
    int getGolesAFavor() const;
    int getGolesEnContra() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getCantidadJugadores() const;

    // Retorna una referencia al jugador en la posición dada
    // (permite modificarlo directamente)
    Jugador& getJugador(int indice);
    const Jugador& getJugador(int indice) const;

    // Muestra los datos generales de la selección
    void mostrarInfo() const;

    // Muestra la plantilla completa de jugadores
    void mostrarPlantilla() const;

    // Sobrecarga del operador < para comparar por ranking FIFA
    bool operator<(const Seleccion& otra) const;

    // Sobrecarga del operador << (función amiga) para imprimir fácil
    friend std::ostream& operator<<(std::ostream& os, const Seleccion& s);
};

#endif // SELECCION_H
