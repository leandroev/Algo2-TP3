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
        bool hayCamino(const Coordenada & c1, const Coordenada & c2) const;
	
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


};

#endif // MAPA_H_
