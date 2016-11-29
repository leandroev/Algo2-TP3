#include "Juego.h"

// generadores

Juego::Juego(const Mapa& m)
    : mapa(m),
      jugadores(Vector<infoJugador>()),
      jugadoresValidos(Vector<bool>()),
      pokemons(DiccString<infoPokemon>()),
      posConPokemons(Conj<Coordenada>()),
      cantTotalPokemons(0)
{
    // se utiliza la lista de inicializacion para crear los objetos vacios de cada propiedad,
    // excepto para infoDePos

    // busco maximo valor de latitud y longitud en las coordenadas del mapa
    Nat maxLat, maxLon = 0;
    Coordenada c;
    typename Conj<Coordenada>::const_Iterador itCs = m.Coordenadas().CrearIt();

    while (itCs.HaySiguiente())
    {
        maxLat = (itCs.Siguiente().Latitud() > maxLat) ? itCs.Siguiente().Latitud() : maxLat;
        maxLon = (itCs.Siguiente().Longitud() > maxLon) ? itCs.Siguiente().Longitud() : maxLon;
        itCs.Avanzar();
    }

    // creo arreglo de tamano maxLat
    this->infoDePos = Arreglo< Arreglo<infoPos> >(maxLat);

    // recorro las coordenadas del mapa
    while (itCs.HayAnterior())
    {
        c = itCs.Anterior();

        // si la latitud no esta definida, defino con un arreglo de infoPos de tamano maxLon
        if (!this->infoDePos.Definido(c.Latitud()))
            this->infoDePos.Definir(c.Latitud(), Arreglo<infoPos>(maxLon));

        // defino la longitud
        this->infoDePos[c.Latitud()].Definir(c.Longitud(), infoPos());

        itCs.Retroceder();
    }
}

Juego::~Juego()
{ }

void Juego::AgregarPokemon(const Pokemon p, const Coordenada c)
{
    #ifdef DEBUG
        assert( this->PuedoAgregarPokemon(c) );
    #endif

    Jugador jug;
    Nat cantCapt;
    Conj<Jugador> cj;
    typename Conj<Jugador>::Iterador itCj;
    ColaPr cp;
    typename ColaPr::Iterador itCp;

    // Busco los entrenadores posibles, que son aquellos que quedan en el rango del pokemon p
    cj = this->EntrenadoresPosibles(c, Conj<Jugador>());
    itCj = cj.CrearIt();

    // Agrego cada entrenador posible a la cola de prioridad, y guardo el iterador para el jugador
    while (itCj.HaySiguiente())     // O(EC)
    {
        jug = itCj.Siguiente();
        cantCapt = this->jugadores[jug].cantCapturados;

        itCp = cp.Encolar(ColaPr::Clave(cantCapt, jug));    // O(Log(EC))

        this->jugadores[jug].enRangoDe = itCp;

        itCj.Avanzar();
    }

    // Set en infoDePos para la coordenada c: hayPokemon en true, el pokemon p y su cola de prioridad de jugadores
    this->infoDePos[c.Latitud()][c.Longitud()].hayPokemon = true;
    this->infoDePos[c.Latitud()][c.Longitud()].pokemon = p;
    this->infoDePos[c.Latitud()][c.Longitud()].jugadoresEsperando = cp;

    // Agrego la coordenada c al conjunto de posConPokemons
    this->posConPokemons.AgregarRapido(c);

    // Sumo cantidad de salvajes para el pokemon p en el dicc pokemons
    if (this->pokemons.Definido(p))     // O(|P|)
    {
        this->pokemons.Obtener(p).cantSalvajes++;     // O(|P|)
    }
    else
    {
        this->pokemons.Definir(p, infoPokemon(1));     // O(|P|)
    }

    // Sumo cantidad de pokemons totales
    this->cantTotalPokemons++;
}

Nat Juego::AgregarJugador()
{
    this->jugadores.AgregarAtras(infoJugador());
    this->jugadoresValidos.AgregarAtras(true);

    return this->jugadores.Longitud() - 1;
}

void Juego::Conectarse(const Jugador e, const Coordenada c)
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() && !this->EstaConectado(e) && this->mapa.posExistente(c) );
    #endif

    // Si hay un pokemon cerca, lo agrego a la cola de prioridad del pokemon
    // * se resetea la cantidad de movimientos esperando para capturar
    if (this->HayPokemonCercano(c))
    {
        Coordenada cpk = this->PosPokemonCercano(c);
        Nat lat = cpk.Latitud();
        Nat lon = cpk.Longitud();
        Nat cantCapt = this->jugadores[e].cantCapturados;

        typename ColaPr::Iterador itPk =
                this->infoDePos[lat][lon].jugadoresEsperando.Encolar(ColaPr::Clave(cantCapt, e));    // O(log(EC))

        this->infoDePos[lat][lon].cantMovsEsperando = 0;

        this->jugadores[e].enRangoDe = itPk;
    }

    // Lo agrego al conjunto de jugadores de la coordenada c, guardo el iterador devuelto
    typename Conj<Nat>::Iterador itPos = this->infoDePos[c.Latitud()][c.Longitud()].jugadoresEnPos.AgregarRapido(e);

    // Set iterador enPos, posicion nueva y conectado en true
    this->jugadores[e].enPos = itPos;
    this->jugadores[e].posicion = c;
    this->jugadores[e].conectado = true;
}

void Juego::Desconectarse(const Jugador e)
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() && this->EstaConectado(e) );
    #endif

    // Si estaba en el rango de un pokemon, lo elimino de la cola de prioridad del pokemon
    if (this->jugadores[e].enRangoDe.HayMas())
    {
        this->jugadores[e].enRangoDe.eliminar();    // O(log(EC))
    }

    // Lo elimino del conjunto de jugadores en la posicion actual
    this->jugadores[e].enPos.EliminarSiguiente();

    // Set iteradores a vacio y conectado en false
    this->jugadores[e].enPos = Conj<Nat>().CrearIt();
    this->jugadores[e].enRangoDe = ColaPr().CrearIt();
    this->jugadores[e].conectado = false;
}

void Juego::Moverse(const Jugador e, const Coordenada c)
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() && this->EstaConectado(e) && this->mapa.posExistente(c) );
    #endif


}

bool Juego::DebeSancionarse(const Jugador e, const Coordenada c) const
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() );
    #endif

    Coordenada p = this->jugadores[e].posicion;

    bool hayCamino = this->mapa.hayCamino(p, c);

    bool estaCerca = p.Distancia(c) <= 100;

    return !hayCamino || !estaCerca;
}

// observadores

const Mapa Juego::MapaJuego() const
{
    return this->mapa;
}

Juego::ItJugadores Juego::Jugadores() const
{
    return this->CrearItJugadores();
}

bool Juego::EstaConectado(const Jugador e) const
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() );
    #endif

    return this->jugadores[e].conectado;
}

Nat Juego::Sanciones(const Jugador e) const
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() );
    #endif

    return this->jugadores[e].sanciones;
}

Coordenada Juego::Posicion(const Jugador e) const
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() && this->EstaConectado(e) );
    #endif

    return this->jugadores[e].posicion;
}

const typename DiccString<Nat>::Iterador Juego::Pokemos(const Jugador e) const
{
    #ifdef DEBUG
        assert( e < this->jugadores.Longitud() );
    #endif

    return this->jugadores[e].capturados.CrearIt();
}

Conj<Jugador> Juego::Expulsados() const
{
    Conj<Jugador> eliminados = Conj<Jugador>();
    int tam = this->jugadoresValidos.Longitud();

    for (int i = 0; i < tam; i++)
    {
        if (!this->jugadoresValidos[i])
            eliminados.AgregarRapido(i);
    }

    return eliminados;
}

const Conj<Coordenada> Juego::PosConPokemons() const
{
    return this->posConPokemons;
}

Pokemon Juego::PokemonEnPos(const Coordenada c) const
{
    #ifdef DEBUG
        assert( this->posConPokemons.Pertenece(c) );
    #endif

    return this->infoDePos[c.Latitud()][c.Longitud()].pokemon;
}

Nat Juego::CantMovimientosParaCaptura(const Coordenada c) const
{
    #ifdef DEBUG
        assert( this->posConPokemons.Pertenece(c) );
    #endif

    return this->infoDePos[c.Latitud()][c.Longitud()].cantMovsEsperando;
}

// otras operaciones (exportadas)

bool Juego::PuedoAgregarPokemon(const Coordenada c) const
{
    bool hayPk = false;
    typename Conj<Coordenada>::const_Iterador it = this->posConPokemons.CrearIt();

    while (it.HaySiguiente())
    {
        hayPk |= c.Distancia(it.Siguiente()) <= 25;
        it.Avanzar();
    }

    return !hayPk;
}

bool Juego::HayPokemonCercano(const Coordenada c) const
{
    bool hayPk = false;
    Nat lat, lon = 0;

    Conj<Coordenada> pc = this->PosCercanas(c);
    typename Conj<Coordenada>::const_Iterador it = pc.CrearIt();

    while (it.HaySiguiente() && !hayPk)
    {
        lat = it.Siguiente().Latitud();
        lon = it.Siguiente().Longitud();

        hayPk = this->infoDePos[lat][lon].hayPokemon;

        it.Avanzar();
    }

    return hayPk;
}

Coordenada Juego::PosPokemonCercano(const Coordenada c) const
{
    #ifdef DEBUG
        assert( this->HayPokemonCercano(c) );
    #endif

    bool hayPk = false;
    Nat lat, lon = 0;

    Conj<Coordenada> pc = this->PosCercanas(c);
    typename Conj<Coordenada>::const_Iterador it = pc.CrearIt();

    while (it.HaySiguiente() && !hayPk)
    {
        lat = it.Siguiente().Latitud();
        lon = it.Siguiente().Longitud();

        hayPk = this->infoDePos[lat][lon].hayPokemon;

        it.Avanzar();
    }

    return it.Anterior();
}

Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada c, const Conj<Jugador> es) const
{
    #ifdef DEBUG
        assert( this->HayPokemonCercano(c) );
    #endif

    Conj<Jugador> cj = Conj<Jugador>();

    Nat lat, lon = 0;
    typename Conj<Jugador>::const_Iterador itJug;

    Conj<Coordenada> pc = this->PosCercanas(c);
    typename Conj<Coordenada>::const_Iterador itPos = pc.CrearIt();

    while (itPos.HaySiguiente())
    {
        if (this->mapa.hayCamino(c, itPos.Siguiente()))
        {
            lat = itPos.Siguiente().Latitud();
            lon = itPos.Siguiente().Longitud();
            itJug = this->infoDePos[lat][lon].jugadoresEnPos.CrearIt();

            while (itJug.HaySiguiente())
            {
                if (this->jugadores[itJug.Siguiente()].conectado)
                    cj.AgregarRapido(itJug.Siguiente());
                itJug.Avanzar();
            }
        }

        itPos.Avanzar();
    }

    return cj;
}

Nat Juego::IndiceRareza(const Pokemon p) const
{
    #ifdef DEBUG
        assert( this->pokemons.Definido(p) );
    #endif

    Nat cantMismaEspecie = this->CantMismaEspecie(p);
    Nat cantTotal = this->CantPokemonsTotales();

    return (100 - (100 * (cantMismaEspecie / cantTotal)));
}

Nat Juego::CantPokemonsTotales() const
{
    return this->cantTotalPokemons;
}

Nat Juego::CantMismaEspecie(const Pokemon p) const
{
    Nat cantSalvajes, cantCapturados = 0;

    if (this->pokemons.Definido(p))
    {
        cantSalvajes = this->pokemons.Obtener(p).cantSalvajes;
        cantCapturados = this->pokemons.Obtener(p).cantCapturados;
    }

    return cantSalvajes + cantCapturados;
}

// otras operaciones (no exportadas)

Conj<Coordenada> Juego::PosCercanas(const Coordenada c) const
{
    Conj<Coordenada> cs = Conj<Coordenada>();

    Nat lat = c.Latitud();
    Nat lon = c.Longitud();

    {
        Coordenada n = Coordenada(lat - 2, lon);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat - 1, lon);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat + 1, lon);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat + 2, lon);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat, lon - 2);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat, lon - 1);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat, lon + 1);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat, lon + 2);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat - 1, lon - 1);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat - 1, lon + 1);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat + 1, lon - 1);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat + 1, lon + 1);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }
    {
        Coordenada n = Coordenada(lat, lon);
        if (this->mapa.posExistente(n))
            cs.AgregarRapido(n);
    }

    return cs;
}

/*** ItJugadores ***/

typename Juego::ItJugadores Juego::CrearItJugadores() const
{
    return ItJugadores(*this);
}

Juego::ItJugadores::ItJugadores() { }

Juego::ItJugadores::ItJugadores(const Juego& j)
{
    this->elems = j.jugadoresValidos;
    this->pos = 0;
}

bool Juego::ItJugadores::HayMas() const
{
    Nat i = this->pos;
    Nat tam = this->elems.Longitud();

    while (i < tam && !this->elems[i]) i++;

    return i < tam;
}

Jugador Juego::ItJugadores::Actual() const
{
    assert(this->HayMas());

    Nat i = this->pos;

    while (!this->elems[i]) i++;

    return i;
}

void Juego::ItJugadores::Avanzar()
{
    assert(this->HayMas());

    Nat i = this->pos;

    while (!this->elems[i]) i++;

    this->pos = i + 1;
}