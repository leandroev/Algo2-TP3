#include "Mapa.h"

Mapa::Mapa() : matriz(Vector < Vector < Mapa::infoCoor > >()), coordenadas(Conj<Coordenada>()), maxLat(0), maxLon(0){}

Mapa::~Mapa(){

    if(Coordenadas().Cardinal() > 0){
        Conj< Vector < Vector < bool > >* > conjCaminos;

        for (int i = 0; i <= maxLat; ++i)
        {
            for (int l = 0; l <= maxLon; ++l)
            {
                if(matriz[i][l].caminos != NULL){
                    Vector < Vector < bool > >* vectorsito = matriz[i][l].caminos;

                    conjCaminos.Agregar(vectorsito);
                    matriz[i][l].caminos = NULL;

                }
            }
        }

        Conj< Vector < Vector < bool > >* >::Iterador it = conjCaminos.CrearIt();

        while (it.HaySiguiente()){

            delete(it.Siguiente());
            it.EliminarSiguiente();
        }

    }
}

const Conj<Coordenada>& Mapa::Coordenadas() const{
    return coordenadas;
}



void Mapa::AgregarCoor(const Coordenada& c){

    if( !(coordenadas.Pertenece(c)) ){
        bool resize = false;
        Nat nLat = c.Latitud();
        Nat nLon = c.Longitud();
        bool posValida = (maxLat > nLat && maxLon > nLon);
        //si la matriz es vacia la inicio
        if(matriz.Longitud() == 0){
            matriz.AgregarAtras( Vector < Mapa::infoCoor >() );
            matriz[0].AgregarAtras(Mapa::infoCoor());
        }
        //miro si cambia el tamaño de la matriz
        if (nLat >= maxLat || nLon >= maxLon)
        {
            redimensionMapa(nLat, nLon);
            resize = !(posValida);
        }

        // Creo la matriz caminos para la nueva Coordenada y la dimensiono
        Vector < Vector <bool> >* nuevoCamino = new Vector< Vector < bool > >;
        dimensionarVector(*nuevoCamino, maxLat, maxLon, nLat, nLon);

        // Recorro los caminos de las coordenadas adyacentes a la nueva

        //caso coordenada a la izquierda

        if ( nLat-1 <= maxLat && nLon <= maxLon && nLat > 0 && matriz[nLat -1][nLon].cValida && !((*nuevoCamino)[nLat-1][nLon]) )
        {

            recorrerCaminos(nLat -1, nLon, nuevoCamino);
        }

        //caso coordenada abajo

        if ( nLat <= maxLat && nLon-1 <= maxLon && nLon > 0 && matriz[nLat][nLon -1].cValida && !((*nuevoCamino)[nLat][nLon-1]) )
        {

            recorrerCaminos(nLat, (nLon-1), nuevoCamino);
        }

        //caso coordenada a la derecha

        if ( nLat+1 <= maxLat && nLon <= maxLon && matriz[nLat +1][nLon].cValida && !((*nuevoCamino)[nLat +1][nLon]) )
        {

            recorrerCaminos(nLat +1, nLon, nuevoCamino);
        }

        //caso coordenada a arriba

        if ( nLat <= maxLat && nLon+1 <= maxLon && matriz[nLat][nLon +1].cValida && !((*nuevoCamino)[nLat][nLon +1]) )
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

        //Actualizo los maximos
        if(maxLat < nLat){
            maxLat = nLat;
        }
        if(maxLon < nLon){
            maxLon = nLon;
        }

        // agrego la coordenada en O(1)
        coordenadas.AgregarRapido(c);

    }
}

bool Mapa::posExistente(const Coordenada& c) const{
    bool res = false;
    if(c.Latitud() <= maxLat && c.Longitud() <= maxLon ){
        return matriz[c.Latitud()][c.Longitud()].cValida;
    }
    return res;
}

bool Mapa::hayCamino(const Coordenada & c1, const Coordenada & c2) const {
    bool res = (*matriz[c1.Latitud()][c1.Longitud()].caminos)[c2.Latitud()][c2.Longitud()];

    return res;
}


void Mapa::redimensionMapa(Nat x, Nat y){


    int nuevoLat = maxLat;
    int nuevoLon = maxLon;
    if (x > maxLat){
        nuevoLat = x;
    }
    if (y > maxLon){
        nuevoLon = y;
    }
    for (int i = maxLat; i < nuevoLat; ++i)
    {

        matriz.AgregarAtras(Vector < Mapa::infoCoor >());
        for (int n = 0; n <= nuevoLon; ++n)
        {


            matriz[i+1].AgregarAtras(Mapa::infoCoor());
        }
    }
    for (int i = 0; i <= maxLat; ++i)
    {

        for (int n = maxLon; n < nuevoLon; ++n)
        {


            matriz[i].AgregarAtras(Mapa::infoCoor());
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
    for (int i = 0; i <= latitud; ++i)
    {
        v.AgregarAtras(Vector<bool>());
        for (int l = 0; l <= longitud; ++l)
        {

            v[i].AgregarAtras(false);
        }
    }

}

void Mapa::recorrerCaminos(Nat x, Nat y, Vector< Vector <bool> >* p){



    Vector < Vector <bool> > * camino = matriz[x][y].caminos;
    for (int i = 0; i <= maxLat; ++i)
    {
        for (int l = 0; l <= maxLon; ++l)
        {
            if ((*camino)[i][l] == true)
            {

                (*p)[i][l] = true;
                if (x != i || y != l)
                {
                    matriz[i][l].caminos = p;
                }
            }
        }
    }
    matriz[x][y].caminos = p;
    delete(camino);
    camino = NULL;

}

void Mapa::redimensionarCaminos(Nat x, Nat y){

    int nuevoLat = maxLat;
    int nuevoLon = maxLon;
    if (x > maxLat){
        nuevoLat = x;
    }
    if (y > maxLon){
        nuevoLon = y;
    }

    Conj< Vector < Vector < bool > >* > conjCaminosnuevos;
    for (int i = 0; i <= maxLat; ++i)
    {
        for (int l = 0; l <= maxLon; ++l)
        {
            if ( matriz[i][l].cValida && !(matriz[x][y].caminos == matriz[i][l].caminos) )
            {
                conjCaminosnuevos.Agregar(matriz[i][l].caminos);
            }
        }
    }
    Conj< Vector < Vector < bool > >* >::Iterador it = conjCaminosnuevos.CrearIt();
    while (it.HaySiguiente()){
            for (int n = maxLat; n < nuevoLat; ++n)
            {
                it.Siguiente()->AgregarAtras(Vector<bool>());
                for (int t = 0; t <= nuevoLon; ++t)
                {
                    (*it.Siguiente())[n+1].AgregarAtras(false);
                }
            }

            for (int b = 0; b <= maxLat; ++b)
            {
                for (int c = maxLon; c < nuevoLon; ++c)
                {
                    (*it.Siguiente())[b].AgregarAtras(false);
                }
            }
            it.EliminarSiguiente();
    }

}
