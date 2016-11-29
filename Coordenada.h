#ifndef COORDENADA_H_
#define COORDENADA_H_

#include "aed2/TiposBasicos.h"

using namespace aed2;

class Coordenada {

	public:

        // Constructor
        Coordenada() : latitud(0), longitud(0) { }
        Coordenada(Nat lat, Nat lon);

        // Observadores
        Nat Latitud() const;
        Nat Longitud() const;

        // Distancia Euclideana
        aed2::Nat Distancia(const Coordenada& otra) const;

        bool operator == (const Coordenada& otra) const;
        bool operator != (const Coordenada& otra) const;

	private:

        Nat latitud;
        Nat longitud;

}; 

#endif // COORDENADA_H_
