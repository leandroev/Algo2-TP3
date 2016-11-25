#ifndef COORDENADA_H_
#define COORDENADA_H_

#include "aed2/TiposBasicos.h"

class Coordenada {

	public:
	//	Constructor Coordenada
	Coordenada(aed2::Nat lat, aed2::Nat lon);

	aed2::Nat Latitud() const;

	aed2::Nat Longitud() const;
	//Distancia Euclideana
	aed2::Nat Distancia(const Coordenada & c1, const Coordenada & c2) const;

	bool operator == (const Coordenada& c2) const;

	private:
		aed2::Nat latitud;
		aed2::Nat longitud;
}; 
// class Coordenada

Coordenada::Coordenada(aed2::Nat lat, aed2::Nat lon) : latitud(lat), longitud(lon){}

aed2::Nat Coordenada::Latitud() const{
	return latitud;
}

aed2::Nat Coordenada::Longitud() const{
	return longitud;
}

aed2::Nat Coordenada::Distancia(const Coordenada & c1, const Coordenada & c2) const{
	aed2::Nat n1;
	aed2::Nat n2;
	if (c1.latitud > c2.latitud)
	{
		n1 = (c1.latitud - c2.latitud) * (c1.latitud - c2.latitud);
	}else{
		n1 = (c2.latitud - c1.latitud) * (c2.latitud - c1.latitud);
	}
	if (c1.longitud > c2.longitud)
	{
		n2 = (c1.longitud - c2.longitud) * (c1.longitud - c2.longitud);
	}else{
		n2 = (c2.longitud - c1.longitud) * (c2.longitud - c1.longitud);
	}
	return n1 + n2;

}

bool Coordenada::operator == (const Coordenada& c2) const{
 	return (latitud == c2.latitud) and (longitud == c2.longitud);
}

#endif // COORDENADA_H_

