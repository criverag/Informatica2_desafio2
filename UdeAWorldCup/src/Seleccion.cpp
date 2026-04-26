#include "Seleccion.h"
#include <iostream>
#include <iomanip>

// -------------------------------------------------------
// Constructor por defecto: inicializa todo en cero o vacio
// -------------------------------------------------------
Seleccion::Seleccion()
    : rankingFIFA(0), pais(""), director(""), confederacion(""),
      golesFavor(0), golesContra(0), ganados(0), empatados(0), perdidos(0) {}

// -------------------------------------------------------
// Constructor con parametros: recibe todos los datos
// -------------------------------------------------------
Seleccion::Seleccion(int ranking, const std::string& p, const std::string& d,
                     const std::string& conf,
                     int gf, int gc, int g, int e, int pe)
    : rankingFIFA(ranking), pais(p), director(d), confederacion(conf),
      golesFavor(gf), golesContra(gc), ganados(g), empatados(e), perdidos(pe) {}

// -------------------------------------------------------
// Getters: cada uno devuelve su atributo correspondiente
// -------------------------------------------------------
int         Seleccion::getRanking()       const { return rankingFIFA; }
std::string Seleccion::getPais()          const { return pais; }
std::string Seleccion::getDirector()      const { return director; }
std::string Seleccion::getConfederacion() const { return confederacion; }
int         Seleccion::getGolesFavor()    const { return golesFavor; }
int         Seleccion::getGolesContra()   const { return golesContra; }
int         Seleccion::getGanados()       const { return ganados; }
int         Seleccion::getEmpatados()     const { return empatados; }
int         Seleccion::getPerdidos()      const { return perdidos; }

// -------------------------------------------------------
// getPuntos: calcula los puntos acumulados
// Cada victoria vale 3, cada empate vale 1
// -------------------------------------------------------
int Seleccion::getPuntos() const {
    return (ganados * 3) + (empatados * 1);
}

// -------------------------------------------------------
// getDiferencia: goles a favor menos goles en contra
// -------------------------------------------------------
int Seleccion::getDiferencia() const {
    return golesFavor - golesContra;
}

// -------------------------------------------------------
// mostrar: imprime la informacion de la seleccion en
// formato tabla legible
// -------------------------------------------------------
void Seleccion::mostrar() const {
    std::cout << std::left
              << std::setw(5)  << rankingFIFA
              << std::setw(22) << pais
              << std::setw(15) << confederacion
              << std::setw(4)  << getPuntos()
              << std::setw(4)  << golesFavor
              << std::setw(4)  << golesContra
              << std::setw(6)  << getDiferencia()
              << "\n";
}

// -------------------------------------------------------
// operator<: compara dos selecciones por ranking FIFA
// Sirve para ordenar de menor a mayor ranking
// -------------------------------------------------------
bool Seleccion::operator<(const Seleccion& otra) const {
    return this->rankingFIFA < otra.rankingFIFA;
}

// -------------------------------------------------------
// operator<<: funcion amiga para imprimir con cout
// -------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Seleccion& s) {
    os << "[" << s.rankingFIFA << "] " << s.pais
       << " (" << s.confederacion << ") - "
       << s.getPuntos() << " pts | DG: " << s.getDiferencia();
    return os;
}
