#ifndef SELECCION_H
#define SELECCION_H

#include <string>
#include <iostream>

// ============================================================
// Clase Seleccion
// Representa a una seleccion clasificada al Mundial 2026.
// Aplica encapsulacion: los atributos son privados y se accede
// a ellos mediante metodos publicos (getters y setters).
// ============================================================
class Seleccion {
private:
    int    rankingFIFA;
    std::string pais;
    std::string director;
    std::string confederacion;
    int    golesFavor;
    int    golesContra;
    int    ganados;
    int    empatados;
    int    perdidos;

public:
    // Constructor por defecto
    Seleccion();

    // Constructor con parametros
    Seleccion(int ranking, const std::string& pais, const std::string& director,
              const std::string& confederacion,
              int gf, int gc, int g, int e, int p);

    // Getters
    int         getRanking()       const;
    std::string getPais()          const;
    std::string getDirector()      const;
    std::string getConfederacion() const;
    int         getGolesFavor()    const;
    int         getGolesContra()   const;
    int         getGanados()       const;
    int         getEmpatados()     const;
    int         getPerdidos()      const;

    // Metodos utiles
    int  getPuntos()       const;  // gana=3, empate=1
    int  getDiferencia()   const;  // goles a favor - goles en contra
    void mostrar()         const;  // imprime la info en consola

    // Sobrecarga de operador: compara por ranking FIFA
    bool operator<(const Seleccion& otra) const;

    // Funcion amiga: imprime la seleccion con formato especial
    friend std::ostream& operator<<(std::ostream& os, const Seleccion& s);
};

#endif
