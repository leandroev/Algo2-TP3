// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "Juego.h"
#include "Driver.h"
#include "mini_test.h"

using namespace aed2;

// Conjunto de coordenadas a usar en los tests
Conj<Coordenada> get_coordenadas()
{
    Conj<Coordenada> cs;

    cs.Agregar(Coordenada(0,0));
    cs.Agregar(Coordenada(0,1));
    cs.Agregar(Coordenada(1,0));
    cs.Agregar(Coordenada(1,1));
    cs.Agregar(Coordenada(3,3));
    cs.Agregar(Coordenada(4,4));

    return cs;
}

void test_constructor_con_mapa()
{
    Conj<Coordenada> cs = get_coordenadas();

    Driver d(cs);

    ASSERT( d.mapa() == cs );
}

void test_agregar_jugadores()
{
    Conj<Coordenada> cs = get_coordenadas();
    Driver d(cs);

    Jugador j0 = d.agregarJugador();
    ASSERT( j0 == 0);

    Jugador j1 = d.agregarJugador();
    ASSERT( j1 == 1);

    Conj<Jugador> cj;
    cj.AgregarRapido(0);
    cj.AgregarRapido(1);

    ASSERT( d.jugadores() == cj );
}

void test_conectar_desconectar_jugador()
{
    Conj<Coordenada> cs = get_coordenadas();
    Driver d(cs);

    Coordenada c = Coordenada(0, 0);

    Jugador j0 = d.agregarJugador();
    Jugador j1 = d.agregarJugador();

    ASSERT( !d.estaConectado(j0) );
    ASSERT( !d.estaConectado(j1) );

    d.conectarse(j0, c);

    ASSERT( d.estaConectado(j0) );
    ASSERT( !d.estaConectado(j1) );

    ASSERT( d.posicion(j0) == c );

    d.desconectarse(j0);

    ASSERT( !d.estaConectado(j0) );
}

void test_agregar_pokemons()
{
    Conj<Coordenada> cs = get_coordenadas();
    Driver d(cs);

    Coordenada cc1 = Coordenada(1, 1);
    Coordenada cc2 = Coordenada(3, 3);
    Coordenada c1 = Coordenada(0, 0);
    Coordenada c2 = Coordenada(4, 4);

    Pokemon p1 = "pikachu";
    Pokemon p2 = "charmander";

    Conj<Coordenada> cpks;

    ASSERT( d.posConPokemons().EsVacio());

    ASSERT( d.cantPokemonsTotales() == 0);
    ASSERT( d.cantMismaEspecie(p1) == 0);
    ASSERT( d.cantMismaEspecie(p2) == 0);

    ASSERT( !d.hayPokemonCercano(cc1) );

    ASSERT( d.puedoAgregarPokemon(c1) );

    cpks.AgregarRapido(c1);
    d.agregarPokemon(p1, c1);

    ASSERT( d.posConPokemons() == cpks );
    ASSERT( d.pokemonEnPos(c1) == p1 );

    ASSERT( d.cantPokemonsTotales() == 1);
    ASSERT( d.cantMismaEspecie(p1) == 1);
    ASSERT( d.cantMismaEspecie(p2) == 0);

    ASSERT( d.hayPokemonCercano(cc1) );
    ASSERT( d.posPokemonCercano(cc1) == c1 );
    ASSERT( !d.puedoAgregarPokemon(cc1) );

    ASSERT( !d.puedoAgregarPokemon(c1) );
    ASSERT( d.puedoAgregarPokemon(c2) );

    cpks.AgregarRapido(c2);
    d.agregarPokemon(p2, c2);

    ASSERT( d.posConPokemons() == cpks );
    ASSERT( d.pokemonEnPos(c1) == p1 );
    ASSERT( d.pokemonEnPos(c2) == p2 );

    ASSERT( d.cantPokemonsTotales() == 2);
    ASSERT( d.cantMismaEspecie(p1) == 1);
    ASSERT( d.cantMismaEspecie(p2) == 1);

    ASSERT( d.hayPokemonCercano(cc1) );
    ASSERT( d.posPokemonCercano(cc1) == c1 );
    ASSERT( !d.puedoAgregarPokemon(cc1) );
    ASSERT( d.hayPokemonCercano(cc2) );
    ASSERT( d.posPokemonCercano(cc2) == c2 );
    ASSERT( !d.puedoAgregarPokemon(cc2) );

    ASSERT( !d.puedoAgregarPokemon(c1) );
    ASSERT( !d.puedoAgregarPokemon(c2) );
}

void super_test()
{
    // Declaracion de variables de control
    Conj<Jugador> cj;
    Conj<Coordenada> ccpk;
    Pokemon pikachu = "pikachu";
    Pokemon charmander = "charmander";
    Pokemon squirtle = "squirtle";

    // Creo conjunto de coordenadas del mapa
    Conj<Coordenada> cs;
    {
        cs.AgregarRapido(Coordenada(0,0));
        cs.AgregarRapido(Coordenada(0,1));
        cs.AgregarRapido(Coordenada(1,0));
        cs.AgregarRapido(Coordenada(1,1));
        cs.AgregarRapido(Coordenada(2,0));
        cs.AgregarRapido(Coordenada(3,0));
        cs.AgregarRapido(Coordenada(0,9));
        cs.AgregarRapido(Coordenada(4,4));
        cs.AgregarRapido(Coordenada(5,4));
        cs.AgregarRapido(Coordenada(7,0));
        cs.AgregarRapido(Coordenada(8,0));
        cs.AgregarRapido(Coordenada(9,0));
        cs.AgregarRapido(Coordenada(9,1));
        cs.AgregarRapido(Coordenada(7,9));
    }

    // Creo el driver
    Driver d(cs);
    {
        ASSERT( d.mapa() == cs );
        ASSERT( d.jugadores() == cj);
        ASSERT( d.posConPokemons() == ccpk)
    }

    // Agrego primer jugador
    Jugador j0 = d.agregarJugador();
    {
        cj.AgregarRapido(0);

        ASSERT( j0 == 0);
        ASSERT( d.jugadores() == cj );
    }

    // Agrego 3 jugadores mas
    Jugador j1 = d.agregarJugador();
    Jugador j2 = d.agregarJugador();
    Jugador j3 = d.agregarJugador();
    {
        cj.AgregarRapido(1);
        cj.AgregarRapido(2);
        cj.AgregarRapido(3);

        ASSERT( d.jugadores() == cj);
    }

    // Conecto jugador 0 en coord (1,1)
    d.conectarse(j0, Coordenada(1, 1));
    {
        ASSERT( d.estaConectado(j0) );
        ASSERT( d.posicion(j0) == Coordenada(1, 1));
    }

    // Agrego pokemon 'pikachu' en coord (0,0)
    d.agregarPokemon(pikachu, Coordenada(0, 0));
    {
        Conj<Jugador> cep;
        cep.AgregarRapido(j0);

        Coordenada c = Coordenada(0, 0);
        ccpk.AgregarRapido(c);

        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( d.pokemonEnPos(c) == pikachu );
        ASSERT( d.entrenadoresPosibles(c) == cep );
        ASSERT( d.cantMovimientosParaCaptura(c) == 0 );
    }

    // Conecto jugador 1 en coord (3,0)
    d.conectarse(j1, Coordenada(3, 0));
    {
        Conj<Jugador> cep;
        cep.AgregarRapido(j0);

        ASSERT( d.estaConectado(j1) );
        ASSERT( d.posicion(j1) == Coordenada(3, 0) );

        ASSERT( d.entrenadoresPosibles(Coordenada(0, 0)) == cep );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 0 );
    }

    // Agrego pokemon 'charmander' en coord (4,4)
    d.agregarPokemon(charmander, Coordenada(4, 4));
    {
        Conj<Jugador> cep;

        Coordenada c = Coordenada(4, 4);
        ccpk.AgregarRapido(c);

        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( d.pokemonEnPos(c) == charmander );
        ASSERT( d.entrenadoresPosibles(c) == cep );
        ASSERT( d.cantMovimientosParaCaptura(c) == 0 );

        ASSERT( d.indiceRareza(pikachu) == 50 );
        ASSERT( d.indiceRareza(charmander) == 50 );
    }

    // Agrego pokemon 'squirtle' en coord (0,9)
    d.agregarPokemon(squirtle, Coordenada(0, 9));
    {
        Conj<Jugador> cep;

        Coordenada c = Coordenada(0, 9);
        ccpk.AgregarRapido(c);

        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( d.pokemonEnPos(c) == squirtle );
        ASSERT( d.entrenadoresPosibles(c) == cep );
        ASSERT( d.cantMovimientosParaCaptura(c) == 0 );

        ASSERT( d.cantPokemonsTotales() == 3 );
        ASSERT( d.cantMismaEspecie(pikachu) == 1 );
        ASSERT( d.cantMismaEspecie(charmander) == 1 );
        ASSERT( d.cantMismaEspecie(squirtle) == 1 );

        ASSERT( d.indiceRareza(pikachu) == 67 );
        ASSERT( d.indiceRareza(charmander) == 67 );
        ASSERT( d.indiceRareza(squirtle) == 67 );
    }

    // Agrego pokemon 'pikachu' en coord (7,9)
    d.agregarPokemon(pikachu, Coordenada(7, 9));
    {
        Conj<Jugador> cep;

        Coordenada c = Coordenada(7, 9);
        ccpk.AgregarRapido(c);

        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( d.pokemonEnPos(c) == pikachu );
        ASSERT( d.entrenadoresPosibles(c) == cep );
        ASSERT( d.cantMovimientosParaCaptura(c) == 0 );

        ASSERT( d.cantPokemonsTotales() == 4 );
        ASSERT( d.cantMismaEspecie(pikachu) == 2 );
        ASSERT( d.cantMismaEspecie(charmander) == 1 );
        ASSERT( d.cantMismaEspecie(squirtle) == 1 );

        ASSERT( d.indiceRareza(pikachu) == 50 );
        ASSERT( d.indiceRareza(charmander) == 75 );
        ASSERT( d.indiceRareza(squirtle) == 75 );
    }

    // Agrego pokemon 'charmander' en coord (9,1)
    d.agregarPokemon(charmander, Coordenada(9, 1));
    {
        Conj<Jugador> cep;

        Coordenada c = Coordenada(9, 1);
        ccpk.AgregarRapido(c);

        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( d.pokemonEnPos(c) == charmander );
        ASSERT( d.entrenadoresPosibles(c) == cep );
        ASSERT( d.cantMovimientosParaCaptura(c) == 0 );

        ASSERT( d.cantPokemonsTotales() == 5 );
        ASSERT( d.cantMismaEspecie(pikachu) == 2 );
        ASSERT( d.cantMismaEspecie(charmander) == 2 );
        ASSERT( d.cantMismaEspecie(squirtle) == 1 );

        ASSERT( d.indiceRareza(pikachu) == 60);
        ASSERT( d.indiceRareza(charmander) == 60);
        ASSERT( d.indiceRareza(squirtle) == 80);
    }

    // Conecto jugador 3 en coord (7,0)
    d.conectarse(j3, Coordenada(7, 0));
    {
        Conj<Jugador> cep;

        ASSERT( d.estaConectado(j3) );
        ASSERT( d.posicion(j3) == Coordenada(7, 0) );

        ASSERT( d.entrenadoresPosibles(Coordenada(9, 1)) == cep );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 0 );
    }

    // Muevo jugador 3 a coord (8,0)
    d.moverse(j3, Coordenada(8, 0));
    {
        Dicc<Pokemon, Nat> capt;
        Conj<Jugador> cep;
        cep.AgregarRapido(j3);

        ASSERT( d.estaConectado(j3) );
        ASSERT( d.posicion(j3) == Coordenada(8, 0) );
        ASSERT( d.sanciones(j3) == 0 );
        ASSERT( d.pokemons(j3) == capt );

        ASSERT( d.entrenadoresPosibles(Coordenada(9, 1)) == cep );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 0 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 1 );
    }

    // Muevo jugador 1 a coord (2,0)
    d.moverse(j1, Coordenada(2, 0));
    {
        Dicc<Pokemon, Nat> capt;
        Conj<Jugador> cep;
        cep.AgregarRapido(j0);
        cep.AgregarRapido(j1);

        ASSERT( d.estaConectado(j1) );
        ASSERT( d.posicion(j1) == Coordenada(2, 0) );
        ASSERT( d.sanciones(j1) == 0 );
        ASSERT( d.pokemons(j1) == capt );

        ASSERT( d.entrenadoresPosibles(Coordenada(0, 0)) == cep );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 0 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );
    }

    // Muevo jugador 3 a coord (9,0)
    d.moverse(j3, Coordenada(9, 0));
    {
        ASSERT( d.posicion(j3) == Coordenada(9, 0) );
        ASSERT( d.sanciones(j3) == 0 );

        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 1 );
    }

    // Conecto jugador 2 en coord (5,4)
    d.conectarse(j2, Coordenada(5, 4));
    {
        Conj<Jugador> cep;
        cep.AgregarRapido(j2);

        ASSERT( d.estaConectado(j2) );
        ASSERT( d.posicion(j2) == Coordenada(5, 4) );

        ASSERT( d.entrenadoresPosibles(Coordenada(4, 4)) == cep );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 1 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(4, 4)) == 0 );
    }

    // Muevo jugador 3 entre coords (9,0) <-> (8, 0), 8 veces
    Nat lat = 8;
    for(int i = 1; i <= 8; i++)
    {
        Coordenada c = Coordenada(lat, 0);

        d.moverse(j3, c);

        ASSERT( d.sanciones(j3) == 0 );

        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 0)) == i + 1);
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(4, 4)) == i );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(0, 9)) == 0 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(7, 9)) == 0 );

        lat = (lat == 8) ? 9 : 8;
    }

    // Muevo jugador 3 a coord (8,0)
    d.moverse(j3, Coordenada(8, 0));
    {
        // El jugador 0 tiene que haber capturado el pikachu de la coord (0,0)
        Dicc<Pokemon, Nat> capt;
        capt.DefinirRapido(pikachu, 1);

        ccpk.Eliminar(Coordenada(0, 0));

        ASSERT( d.pokemons(j0) == capt );
        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( !d.hayPokemonCercano(d.posicion(j1)) );
        ASSERT( d.hayPokemonCercano(d.posicion(j2)) );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(4, 4)) == 9 );
        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );
    }

    // Muevo jugador 3 a coord (9,0)
    d.moverse(j3, Coordenada(9, 0));
    {
        // El jugador 2 tiene que haber capturado el charmander de la coord (4,4)
        Dicc<Pokemon, Nat> captJ0;
        captJ0.DefinirRapido(pikachu, 1);

        Dicc<Pokemon, Nat> captJ2;
        captJ2.DefinirRapido(charmander, 1);

        ccpk.Eliminar(Coordenada(4, 4));

        ASSERT( d.pokemons(j0) == captJ0 );
        ASSERT( d.pokemons(j2) == captJ2 );
        ASSERT( d.posConPokemons() == ccpk );
        ASSERT( !d.hayPokemonCercano(d.posicion(j2)) );

        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );

        ASSERT( d.cantPokemonsTotales() == 5 );
        ASSERT( d.cantMismaEspecie(pikachu) == 2 );
        ASSERT( d.cantMismaEspecie(charmander) == 2 );
        ASSERT( d.cantMismaEspecie(squirtle) == 1 );

        ASSERT( d.indiceRareza(pikachu) == 60);
        ASSERT( d.indiceRareza(charmander) == 60);
        ASSERT( d.indiceRareza(squirtle) == 80);
    }

    // Muevo jugador 2 a coord (7,9), 4 veces
    for(int i = 1; i <= 4; i++)
    {
        // No hay camino, mov invalido acumula sancion
        Dicc<Pokemon, Nat> captJ2;
        captJ2.DefinirRapido(charmander, 1);

        d.moverse(j2, Coordenada(7, 9));

        ASSERT( d.sanciones(j2) == i );
        ASSERT( d.posicion(j2) == Coordenada(5, 4) );
        ASSERT( d.pokemons(j2) == captJ2 );

        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );
    }

    // Muevo jugador 2 a coord (7,9)
    d.moverse(j2, Coordenada(7, 9));
    {
        // Jugador 2 llega a la quinta sancion, debe haber sido eliminado y sus pokemons tambien
        Conj<Jugador> exp;
        exp.AgregarRapido(j2);
        cj.Eliminar(j2);

        ASSERT( d.jugadores() == cj );
        ASSERT( d.expulsados() == exp );

        ASSERT( d.cantMovimientosParaCaptura(Coordenada(9, 1)) == 1 );

        ASSERT( d.cantPokemonsTotales() == 4 );
        ASSERT( d.cantMismaEspecie(pikachu) == 2 );
        ASSERT( d.cantMismaEspecie(charmander) == 1 );
        ASSERT( d.cantMismaEspecie(squirtle) == 1 );

        ASSERT( d.indiceRareza(pikachu) == 50);
        ASSERT( d.indiceRareza(charmander) == 75);
        ASSERT( d.indiceRareza(squirtle) == 75);
    }
}

int main()
{
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_conectar_desconectar_jugador);
    RUN_TEST(test_agregar_pokemons);

    RUN_TEST(super_test);

    return 0;
}
