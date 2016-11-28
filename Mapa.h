#ifndef MAPA_H_
#define MAPA_H_

#include "aed2/Conj.h"
#include "aed2/Vector.h"
#include "Coordenada.h"

using namespace aed2;

class Mapa {

	public:
		// Constructor Mapa
		Mapa();
		// Destructor Mapa
		~Mapa();
		// Observador Coordenadas Validas
		const Conj<Coordenada>& Coordenadas() const;
		// Genera una coodenada valida en mapa
		void AgregarCoor(const Coordenada & c);

		bool posExistente(const Coordenada & c) const;
		// verifica si dos coordenadas estan conectadas
		bool hayCamino(const Coordenada & c1, const Coordenada & c2);
	
	private:
		// Agranda la dimension de la matriz
		void redimensionMapa(Nat x, Nat y);
		// Dimensiona una matriz con el tamaño apropiado
		void dimensionarVector(Vector< Vector <bool> > & v, Nat x1, Nat y1, Nat x2, Nat y2);
		// Recorre la matriz de caminos
		void recorrerCaminos(Nat x, Nat y, Vector< Vector <bool> >* p);
		// Redimensiona todas las matrices de caminos
		void redimensionarCaminos(Nat x, Nat y);
		
		// tupla con informacion de las coordenadas
		struct infoCoor
		{
			Vector < Vector < bool > > * caminos;
			bool cValida;
			//Constructor por defecto
			infoCoor() { 
				caminos = NULL;
				cValida = false;
			}	
			//Constructor para coordenadas validas
			infoCoor(Vector < Vector < bool > > * caminos, bool cValida) : caminos(NULL), cValida(false){}
		};

		Vector < Vector < infoCoor > > matriz;
		Conj< Coordenada > coordenadas;
		Nat maxLat;
		Nat maxLon;


}; // class Mapa


Mapa::Mapa() : matriz(Vector < Vector < Mapa::infoCoor > >()), coordenadas(Conj<Coordenada>()), maxLat(0), maxLon(0){}

Mapa::~Mapa(){

}

const Conj<Coordenada>& Mapa::Coordenadas() const{
	return coordenadas;
}



void Mapa::AgregarCoor(const Coordenada& c){
	if( !(coordenadas.Pertenece(c)) ){
		bool resize = false;
		Nat nLat = c.Latitud();
		Nat nLon = c.Longitud();

		//me fijo si cambia el tamaño del matriz
		if (nLat > maxLat || nLon > maxLon) 
		{
			redimensionMapa(nLat, nLon);
			resize = true;
		}

		// Creo la matriz caminos para la nueva Coordenada y la dimensiono
		Vector < Vector <bool> >* nuevoCamino = new Vector< Vector < bool > >;
		dimensionarVector(*nuevoCamino, maxLat, maxLon, nLat, nLon);

		// Recorro los caminos de las coordenadas adyacentes a la nueva

		//caso coordenada a la izquierda
		if ( nLat > 0 && matriz[nLat -1][nLon].cValida ) 
		{
			recorrerCaminos(nLat -1, nLon, nuevoCamino);
		}

		//caso coordenada abajo
		if ( nLon > 0 && matriz[nLat][nLon -1].cValida && !((*nuevoCamino)[nLat][nLon-1]) )	
		{
			recorrerCaminos(nLat, (nLon-1), nuevoCamino);
		}

		//caso coordenada a la derecha
		if ( matriz[nLat +1][nLon].cValida && !((*nuevoCamino)[nLat +1][nLon]) )
		{
			recorrerCaminos(nLat +1, nLon, nuevoCamino);
		}

		//caso coordenada a arriba
		if ( matriz[nLat][nLon +1].cValida && !((*nuevoCamino)[nLat][nLon +1]) )	
		{
			recorrerCaminos(nLat, nLon +1, nuevoCamino);
		}
		// la coordenada agregada ahora es valida y tiene camino a si misma
		matriz[nLat][nLon].cValida = true;
		matriz[nLat][nLon].caminos = nuevoCamino;
		(*nuevoCamino)[nLat][nLon] = true;
		nuevoCamino = NULL;

		//Redimensiona todos los caminos de las demas coordenadas validas
		if (resize)
		{
			redimensionarCaminos(nLat, nLon);
		}
		
		if (nLat > maxLat)
		{
			maxLat = nLat;
		}
		if (nLon > maxLon)
		{
			maxLon = nLon;
		}
		coordenadas.AgregarRapido(c);
	}
}

bool Mapa::posExistente(const Coordenada& c) const{
	return matriz[c.Latitud()][c.Longitud()].cValida;
}

bool Mapa::hayCamino(const Coordenada & c1, const Coordenada & c2) {
	bool res = false;
	res = (*matriz[c1.Latitud()][c1.Longitud()].caminos)[c2.Latitud()][c2.Longitud()];
	return res;
}


void Mapa::redimensionMapa(Nat x, Nat y){
	for (int i = maxLat; i < x; ++i)
	{
		matriz.AgregarAtras(Vector < Mapa::infoCoor >());
		for (int n = 0; n < y; ++i)
		{
			matriz[i].AgregarAtras(Mapa::infoCoor());
		}
	}
	for (int i = 0; i < maxLat; ++i)
	{
		for (int n = maxLon; n < y; ++i)
		{
			matriz[n].AgregarAtras(Mapa::infoCoor());
		}
	}
}

void Mapa::dimensionarVector(Vector< Vector <bool> >& v, Nat x1, Nat y1, Nat x2, Nat y2){
	Nat latitud = x1;
	Nat longitud = y1;
	if (x1 < x2)
	{
		latitud = x2;
	}
	if (y1 < y2)
	{
		longitud = y2;
	}
	for (int i = 0; i < latitud; ++i)
	{
		v.AgregarAtras(Vector<bool>());
		for (int l = 0; l < longitud; ++i)
		{
			v[i].AgregarAtras(false);
		}
	}
}

void Mapa::recorrerCaminos(Nat x, Nat y, Vector< Vector <bool> >* p){
	Vector < Vector <bool> > * camino = matriz[x][y].caminos;
	for (int i = 0; i < maxLat; ++i)
	{
		for (int l = 0; l < maxLon; ++l)
		{
			if (x != i && y != l)
			{
				if ((*camino)[i][l])
				{
					(*p)[i][l] = true;
					matriz[i][l].caminos = p;
				}
			}
		}
	}
}

void Mapa::redimensionarCaminos(Nat x, Nat y){
	for (int i = 0; i < maxLat; ++i)
	{
		for (int l = 0; l < maxLon; ++l)
		{
			if ( matriz[i][l].cValida && !(matriz[x][y].caminos == matriz[i][l].caminos) )
			{
				for (int n = maxLat; n < x; ++n)
				{
					matriz[i][l].caminos->AgregarAtras(Vector<bool>());
					for (int t = 0; t < y; ++t)
					{
						(*matriz[i][l].caminos)[n].AgregarAtras(false);
					}
				}
				for (int b = 0; b < maxLat; ++b)
				{
					for (int c = maxLon; c < y; ++c)
					{
						(*matriz[i][l].caminos)[b].AgregarAtras(false);
					}
				}
			}
		}
	}
}

#endif // MAPA_H_

