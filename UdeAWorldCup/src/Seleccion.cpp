#include "Seleccion.h"
#include <cstring>  // strlen, strcpy

// ============================================================
// Función auxiliar privada
// Reserva memoria en el heap y copia la cadena recibida.
// Se usa para que cada objeto tenga su propia copia del string.
// ============================================================
char* Seleccion::copiarCadena(const char* origen) const {
    if (origen == nullptr) return nullptr;
    int longitud = strlen(origen);
    char* nueva = new char[longitud + 1]; // +1 para el '\0'
    strcpy(nueva, origen);
    return nueva;
}

// ============================================================
// Constructor por defecto
// Deja todos los punteros en nullptr y los enteros en 0.
// ============================================================
Seleccion::Seleccion()
    : pais(nullptr), directorTecnico(nullptr),
      federacion(nullptr), confederacion(nullptr),
      rankingFIFA(0), golesAFavor(0), golesEnContra(0),
      partidosGanados(0), partidosEmpatados(0), partidosPerdidos(0),
      tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {
}

// ============================================================
// Constructor con parámetros
// ============================================================
Seleccion::Seleccion(int ranking, const char* p, const char* dt,
                     const char* fed, const char* conf,
                     int gf, int gc, int pg, int pe, int pp)
    : rankingFIFA(ranking),
      golesAFavor(gf), golesEnContra(gc),
      partidosGanados(pg), partidosEmpatados(pe), partidosPerdidos(pp),
      tarjetasAmarillas(0), tarjetasRojas(0), faltas(0)
{
    pais            = copiarCadena(p);
    directorTecnico = copiarCadena(dt);
    federacion      = copiarCadena(fed);
    confederacion   = copiarCadena(conf);
}

// ============================================================
// Constructor de copia
// Crea una copia profunda (deep copy) del objeto.
// Es importante para evitar que dos objetos compartan
// la misma dirección de memoria.
// ============================================================
Seleccion::Seleccion(const Seleccion& otra)
    : rankingFIFA(otra.rankingFIFA),
      golesAFavor(otra.golesAFavor), golesEnContra(otra.golesEnContra),
      partidosGanados(otra.partidosGanados),
      partidosEmpatados(otra.partidosEmpatados),
      partidosPerdidos(otra.partidosPerdidos),
      tarjetasAmarillas(otra.tarjetasAmarillas),
      tarjetasRojas(otra.tarjetasRojas), faltas(otra.faltas)
{
    pais            = copiarCadena(otra.pais);
    directorTecnico = copiarCadena(otra.directorTecnico);
    federacion      = copiarCadena(otra.federacion);
    confederacion   = copiarCadena(otra.confederacion);
}

// ============================================================
// Destructor
// Libera la memoria reservada en el heap con new[].
// Sin esto habría una fuga de memoria (memory leak).
// ============================================================
Seleccion::~Seleccion() {
    delete[] pais;
    delete[] directorTecnico;
    delete[] federacion;
    delete[] confederacion;
    // Los punteros quedan "colgando" pero el objeto ya no existe,
    // así que no hay problema.
}

// ============================================================
// Operador de asignación
// Necesario cuando hacemos: seleccion1 = seleccion2
// ============================================================
Seleccion& Seleccion::operator=(const Seleccion& otra) {
    // Verificamos que no sea auto-asignación: a = a
    if (this == &otra) return *this;

    // Liberamos la memoria anterior
    delete[] pais;
    delete[] directorTecnico;
    delete[] federacion;
    delete[] confederacion;

    // Copiamos los datos
    rankingFIFA       = otra.rankingFIFA;
    golesAFavor       = otra.golesAFavor;
    golesEnContra     = otra.golesEnContra;
    partidosGanados   = otra.partidosGanados;
    partidosEmpatados = otra.partidosEmpatados;
    partidosPerdidos  = otra.partidosPerdidos;
    tarjetasAmarillas = otra.tarjetasAmarillas;
    tarjetasRojas     = otra.tarjetasRojas;
    faltas            = otra.faltas;

    pais            = copiarCadena(otra.pais);
    directorTecnico = copiarCadena(otra.directorTecnico);
    federacion      = copiarCadena(otra.federacion);
    confederacion   = copiarCadena(otra.confederacion);

    return *this;
}

// ============================================================
// Getters
// ============================================================
int         Seleccion::getRanking()           const { return rankingFIFA; }
const char* Seleccion::getPais()              const { return pais; }
const char* Seleccion::getDT()                const { return directorTecnico; }
const char* Seleccion::getFederacion()        const { return federacion; }
const char* Seleccion::getConfederacion()     const { return confederacion; }
int         Seleccion::getGolesAFavor()       const { return golesAFavor; }
int         Seleccion::getGolesEnContra()     const { return golesEnContra; }
int         Seleccion::getPartidosGanados()   const { return partidosGanados; }
int         Seleccion::getPartidosEmpatados() const { return partidosEmpatados; }
int         Seleccion::getPartidosPerdidos()  const { return partidosPerdidos; }

// ============================================================
// Setters / actualizadores de estadísticas
// ============================================================
void Seleccion::agregarGolAFavor()  { golesAFavor++; }
void Seleccion::agregarGolEnContra(){ golesEnContra++; }

void Seleccion::registrarPartido(bool gano, bool empato) {
    if (gano)       partidosGanados++;
    else if (empato) partidosEmpatados++;
    else             partidosPerdidos++;
}

// ============================================================
// Sobrecarga del operador <
// Permite comparar selecciones por ranking FIFA.
// Un ranking menor = mejor posición.
// ============================================================
bool Seleccion::operator<(const Seleccion& otra) const {
    return rankingFIFA < otra.rankingFIFA;
}

bool Seleccion::operator==(const Seleccion& otra) const {
    return rankingFIFA == otra.rankingFIFA;
}

// ============================================================
// Método mostrar()
// Imprime los datos del equipo en consola.
// ============================================================
void Seleccion::mostrar() const {
    std::cout << "--------------------------------------------\n";
    std::cout << "Pais            : " << (pais ? pais : "N/A") << "\n";
    std::cout << "Ranking FIFA    : " << rankingFIFA << "\n";
    std::cout << "Director Tecnico: " << (directorTecnico ? directorTecnico : "N/A") << "\n";
    std::cout << "Confederacion   : " << (confederacion ? confederacion : "N/A") << "\n";
    std::cout << "Goles a favor   : " << golesAFavor
              << " | En contra: " << golesEnContra << "\n";
    std::cout << "Partidos G/E/P  : "
              << partidosGanados << "/"
              << partidosEmpatados << "/"
              << partidosPerdidos << "\n";
}

// ============================================================
// Función amiga: operator<<
// Permite hacer: cout << miSeleccion
// ============================================================
std::ostream& operator<<(std::ostream& out, const Seleccion& s) {
    out << "[" << s.rankingFIFA << "] "
        << (s.pais ? s.pais : "?")
        << " (" << (s.confederacion ? s.confederacion : "?") << ")";
    return out;
}
