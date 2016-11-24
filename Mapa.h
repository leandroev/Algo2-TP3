#ifndef MAPA_H_
#define MAPA_H_

#include "aed2/Conj.h"
#include "aed2/Vector.h"
#include "Coordenada.h"

class Mapa {

	public:

	const Conj<Coordenada> Coordenadas() const;

	Mapa CrearMapa();

	~Mapa();

	void AgregarCoor(const Coordenada & c);

	const bool posExistente(const Coordenada & c) const;

	const bool hayCamino(const Coordenada & c1, const Coordenada & c2) const;
	
	private:
		void redimensionMapa(const Nat x, const Nat y);
		void dimensionarVector(Vector< Vector <bool> > & v, const Nat x1, const Nat y1, const Nat x2, const Nat y2);
		void recorrerCaminos(const Nat x, const Nat y, Vector< Vector <bool> >* p);
		void redimensionarCaminos(const Nat x, const Nat y);
		
		struct infoCoor
		{
			Vector < Vector< bool > > * caminos;
			bool cValida;
		};

		Vector < Vector < infoCoor > > matriz;
		Conj<Coordenada> coordenadas;
		Nat maxLat;
		Nat maxLon;


}; // class Mapa

Conj<Coordenada> Coordenadas(const Mapa mapa) const{
	return mapa.coordenadas;
}

CrearMapa(){
	mapa.matriz = Vacio();
	mapa.coordenadas = Vacio();
	mapa.maxLat = 0;
	mapa.maxLon = 0;
}

void AgregarCoor(const Coordenada c, Mapa mapa){
	if(m.coordenadas.Pertenece(c)){
		bool resize = false;
		Nat nLat = Latitud(c);
		Nat nLon = Longitud(c);
		if (nLat > m.maxLat || nLon > m.maxLon)
		{
			redimensionMapa(m, nLat, nLon);
			resize = true;
		}
		Vector < Vector <bool> > * nuevoCamino = Vacio();
		dimensionarVector(*nuevoCamino, m.maxLat, m.maxLon, nLat, nLon);
		if (nLat > 0 && m.matriz[nLat -1][nLon].cValida)
		{
			recorrerCaminos(m, nLat -1, nLon, nuevoCamino);
		}
		if (nLon > 0 && m.matriz[nLat][nLon -1].cValida && !(*nuevoCamino[nLat][nLon -1]))
		{
			recorrerCaminos(m, nLat, nLon -1, nuevoCamino);
		}
		if (m.matriz[nLat +1][nLon].cValida && !(*nuevoCamino[nLat +1][nLon]))
		{
			recorrerCaminos(m, nLat +1, nLon, nuevoCamino);
		}
		if (m.matriz[nLat][nLon +1].cValida && !(*nuevoCamino[nLat][nLon +1]))
		{
			recorrerCaminos(m, nLat, nLon +1, nuevoCamino);
		}
		m.matriz[nLat][nLon].cValida = true;
		m.matriz[nLat][nLon].caminos = nuevoCamino;
		*nuevoCamino[nLat][nLon] = true;
		nuevoCamino = NULL;
		if (resize)
		{
			redimensionarCaminos(m, nLat, nLon);
		}
		if (nLat > m.maxLat)
		{
			m.maxLat = nLat;
		}
		if (nLon > m.maxLon)
		{
			m.maxLon = nLon;
		}
		AgregarRapido(m.coordenadas, c);
	}
}

bool posExistente(const Coordenada& c, Mapa mapa) const{
	bool res = m.matriz[Latitud(c)][Longitud(c)].cValida;
}

bool hayCamino(const Coordenada & c1, const Coordenada & c2) const{
	bool res = false;
	if (*(m.matriz[Latitud(c1)][Longitud(c1)].caminos)[Latitud(c2)][Longitud(c2)])
	{
		res = true;
	}
	return res;
}

void redimensionMapa(Mapa m, Nat x, Nat y){
	for (int i = m.maxLat; i < x; ++i)
	{
		AgregarAtras(m.matriz, Vacio());
		for (int n = 0; i < y; ++i)
		{
			AgregarAtras(m.matriz[i], <NULL, false>);
		}
	}
	for (int i = 0; i < m.maxLat; ++i)
	{
		for (int i = m.maxLon; i < y; ++i)
		{
			AgregarAtras(m.matriz[n], <NULL, false>);
		}
	}
}

void dimensionarVector(Vector< Vector <bool> > v, Nat x1, Nat y1, Nat x2, Nat y2){
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
		AgregarAtras(v,Vacio());
		for (int l = 0; i < longitud; ++i)
		{
			AgregarAtras(v[i], false);
		}
	}
}

void recorrerCaminos(Mapa m, Nat x, Nat y, Vector< Vector <bool> >* p){
	Vector < Vector <bool> > * camino = m.matriz[x][y].caminos;
	for (int i = 0; i < m.maxLat; ++i)
	{
		for (int i = 0; i < m.maxLon; ++i)
		{
			if (x != i && y != l)
			{
				if *(camino)[i][l]
				{
					*(p)[i][l] = true;
					m.matriz[i][l].caminos = p;
				}
			}
		}
	}
}

void redimensionarCaminos(Mapa m, Nat x, Nat y){
	for (int i = 0; i < m.maxLat; ++i)
	{
		for (int l = 0; i < m.maxLon; ++i)
		{
			if ( m.matriz[i][l].cValida && !(m.matriz[x][y].caminos == m.matriz[i][l]) )
			{
				for (int n = maxLat; i < x; ++i)
				{
					AgregarAtras(*(m.matriz[i][l].caminos), Vacio());
					for (int t = 0; i < y; ++i)
					{
						AgregarAtras(*(m.matriz[i][l].caminos)[n], false);
					}
				}
				for (int b = 0; i < m.maxLat; ++i)
				{
					for (int c = m.maxLon; i < y; ++i)
					{
						AgregarAtras(*(m.matriz[i][l].caminos)[b], false);
					}
				}
			}
		}
	}
}

#endif // MAPA_H_

