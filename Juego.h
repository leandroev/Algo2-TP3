#ifndef JUEGO_H_
#define JUEGO_H_

#include "aed2.h"
#include "TiposJuego.h"
#include "Coordenada.h"
#include "Mapa.h"
#include "DiccString.h"
#include "ColaPr.h"

using namespace aed2;

class Juego {

    public:

        //forward declarations
        class ItJugadores;

        // generadores

        Juego(const Mapa& m);

        ~Juego();

        void AgregarPokemon(const Pokemon p, const Coordenada c);

        Nat AgregarJugador();

        void Conectarse(const Jugador e, const Coordenada c);

        void Desconectarse(const Jugador e);

        void Moverse(const Jugador e, const Coordenada c);

        // observadores

        const Mapa MapaJuego() const;

        ItJugadores Jugadores() const;

        bool EstaConectado(const Jugador e) const;

        Nat Sanciones(const Jugador e) const;

        Coordenada Posicion(const Jugador e) const;

        const typename DiccString<Nat>::Iterador Pokemos(const Jugador e) const;

        Conj<Jugador> Expulsados() const;

        const Conj<Coordenada> PosConPokemons() const;

        Pokemon PokemonEnPos(const Coordenada c) const;

        Nat CantMovimientosParaCaptura(const Coordenada c) const;

        // otras operaciones (exportadas)

        bool PuedoAgregarPokemon(const Coordenada c) const;

        bool HayPokemonCercano(const Coordenada c) const;

        Coordenada PosPokemonCercano(const Coordenada c) const;

        Conj<Jugador> EntrenadoresPosibles(const Coordenada c, const Conj<Jugador> es) const;

        Nat IndiceRareza(const Pokemon p) const;

        Nat CantPokemonsTotales() const;

        Nat CantMismaEspecie(const Pokemon p) const;

        // Creación del Iterador de Jugadores
        ItJugadores CrearItJugadores() const;

        // Iterador de Jugadores, no modificable
        class ItJugadores {

            public:

                ItJugadores();

                bool HayMas() const;

                Jugador Actual() const;

                void Avanzar();

            private:

                Vector<bool> elems;
                Nat pos;

                ItJugadores(const Juego& j);

                friend typename Juego::ItJugadores Juego::CrearItJugadores() const;

        };

    private:

        // otras operaciones (no exportadas)

        bool DebeSancionarse(const Jugador e, const Coordenada c) const;

        Conj<Coordenada> PosCercanas(const Coordenada c) const;

        // estructuras necesarias para la estr de juego
        struct infoJugador {
            bool conectado;
            Nat sanciones;
            Coordenada posicion;
            DiccString<Nat> capturados;
            Nat cantCapturados;
            typename ColaPr::Iterador enRangoDe;
            typename Conj<Nat>::Iterador enPos;

            infoJugador() : conectado(false), sanciones(0), posicion(Coordenada(0, 0)),
                capturados(DiccString<Nat>()), cantCapturados(0),
                enRangoDe(ColaPr().CrearIt()), enPos(Conj<Nat>().CrearIt()) { }
        };

        struct infoPokemon {
            Nat cantSalvajes;
            Nat cantCapturados;

            infoPokemon() : cantSalvajes(0), cantCapturados(0) { }
            infoPokemon(Nat salvajes) : cantSalvajes(salvajes), cantCapturados(0) { }
        };

        struct infoPos {
            bool hayPokemon;
            Pokemon pokemon;
            Conj<Nat> jugadoresEnPos;
            Nat cantMovsEsperando;
            ColaPr jugadoresEsperando;

            infoPos() : hayPokemon(false), pokemon(""),
                jugadoresEnPos(Conj<Nat>()), cantMovsEsperando(0), jugadoresEsperando(ColaPr()) { }
        };

        // estr
        Mapa mapa;
        Vector<infoJugador> jugadores;
        Vector<bool> jugadoresValidos;
        DiccString<infoPokemon> pokemons;
        Conj<Coordenada> posConPokemons;
        Arreglo< Arreglo<infoPos> > infoDePos;
        Nat cantTotalPokemons;
};

#endif // JUEGO_H_
