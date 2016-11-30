#include "Driver.h"

Driver::Driver(const Conj< Coordenada > & cs)
{
    Mapa map = Mapa();

    typename Conj<Coordenada>::const_Iterador itCs = cs.CrearIt();
    while (itCs.HaySiguiente())
    {
        map.AgregarCoor(itCs.Siguiente());
        itCs.Avanzar();
    }

    this->juego = Juego(map);
}

Driver::~Driver()
{ }

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c)
{
    this->juego.AgregarPokemon(p, c);
}

Jugador Driver::agregarJugador()
{
    return this->juego.AgregarJugador();
}

void Driver::conectarse(const Jugador & j, const Coordenada & c)
{
    this->juego.Conectarse(j, c);
}

void Driver::desconectarse(const Jugador & j)
{
    this->juego.Desconectarse(j);
}

void Driver::moverse(const Jugador & j, const Coordenada & c)
{
    this->juego.Moverse(j, c);
}

Conj< Coordenada > Driver::mapa() const
{
    Conj<Coordenada> res = this->juego.MapaJuego().Coordenadas();
    return res;
}

bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const
{
    return this->juego.MapaJuego().hayCamino(c1, c2);
}

bool Driver::posExistente(const Coordenada & c) const
{
    return this->juego.MapaJuego().posExistente(c);
}

Conj< Jugador > Driver::jugadores() const
{
    Conj<Jugador> cj = Conj<Jugador>();
    typename Juego::ItJugadores itJug = this->juego.Jugadores();

    while (itJug.HayMas())
    {
        cj.AgregarRapido(itJug.Actual());
        itJug.Avanzar();
    }

    return cj;
}

bool Driver::estaConectado(const Jugador & j) const
{
    return this->juego.EstaConectado(j);
}

Nat Driver::sanciones(const Jugador & j) const
{
    return this->juego.Sanciones(j);
}

Coordenada Driver::posicion(const Jugador & j) const
{
    return this->juego.Posicion(j);
}

Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const
{
    Dicc<Pokemon, Nat> capturados = Dicc<Pokemon, Nat>();
    typename DiccString<Nat>::Iterador itPks = this->juego.Pokemos(j);

    while (itPks.HaySiguiente())
    {
        capturados.DefinirRapido(itPks.SiguienteClave(), itPks.SiguienteSignificado());
        itPks.Avanzar();
    }

    return capturados;
}

Conj< Jugador > Driver::expulsados() const
{
    return this->juego.Expulsados();
}

Conj< Coordenada > Driver::posConPokemons() const
{
    return this->juego.PosConPokemons();
}

Pokemon Driver::pokemonEnPos(const Coordenada & c) const
{
    return this->juego.PokemonEnPos(c);
}

Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const
{
    return this->juego.CantMovimientosParaCaptura(c);
}

bool Driver::puedoAgregarPokemon(const Coordenada & c) const
{
    return this->juego.PuedoAgregarPokemon(c);
}

bool Driver::hayPokemonCercano(const Coordenada & c) const
{
    return this->juego.HayPokemonCercano(c);
}

Coordenada Driver::posPokemonCercano(const Coordenada & c) const
{
    return this->juego.PosPokemonCercano(c);
}

Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const
{
    return this->juego.EntrenadoresPosibles(c, Conj<Jugador>());
}

Nat Driver::indiceRareza(const Pokemon & p) const
{
    return this->juego.IndiceRareza(p);
}

Nat Driver::cantPokemonsTotales() const
{
    return this->juego.CantPokemonsTotales();
}

Nat Driver::cantMismaEspecie(const Pokemon & p) const
{
    return this->juego.CantMismaEspecie(p);
}
