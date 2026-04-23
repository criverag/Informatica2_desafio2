#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>

// ============================================================
// Clase Jugador
// Representa a un jugador dentro de una selección nacional.
// Aplica encapsulación: todos los atributos son privados
// y se acceden mediante getters y setters.
// ============================================================
class Jugador {
private:
    std::string nombre;
    std::string apellido;
    int numeroCamiseta;

    // Estadísticas históricas del jugador
    int partidosJugados;
    int goles;
    int minutosJugados;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    // Constructor por defecto
    Jugador();

    // Constructor con parámetros (inicializa con datos fabricados)
    Jugador(const std::string& nombre, const std::string& apellido,
            int numCamiseta, int golesIniciales);

    // Constructor de copia
    Jugador(const Jugador& otro);

    // Destructor
    ~Jugador();

    // --- Getters ---
    std::string getNombre() const;
    std::string getApellido() const;
    int getNumeroCamiseta() const;
    int getPartidosJugados() const;
    int getGoles() const;
    int getMinutosJugados() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    // --- Setters ---
    void setGoles(int g);
    void setTarjetasAmarillas(int ta);
    void setTarjetasRojas(int tr);
    void setFaltas(int f);
    void setPartidosJugados(int p);
    void setMinutosJugados(int m);

    // Muestra la información del jugador en consola
    void mostrarInfo() const;

    // Sobrecarga del operador == para comparar jugadores por número de camiseta
    bool operator==(const Jugador& otro) const;
};

#endif // JUGADOR_H
