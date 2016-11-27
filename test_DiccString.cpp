#include <iostream>
#include "mini_test.h"

#include "DiccString.h"

//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio() {
	DiccString<int> d;
    ASSERT(d.Claves().Cardinal() == 0);
}

//Chequea el definir y definido
void test_definir_definido() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );

	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( !d.Definido("casa") );

  	d.Definir("casa",6);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( d.Definido("casa") );

    d.Definir("casas",79);
}

void test_redefinir()
{
    DiccString<int> d;
    d.Definir("hola",42);
    ASSERT( d.Definido("hola") );

    d.Definir("hola",41);
    ASSERT( d.Obtener("hola") == 41 );
}

//cheque el obtener
void test_obtener() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );
}

//cheque el borrar
void test_borrar() {
	//Completar este test para:
	//Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
	//Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
	//Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.
	
	DiccString<int> d;
	d.Definir("hola",42);
    ASSERT( d.Definido("hola") );

    d.Borrar("hola");
    ASSERT( !d.Definido("hola") );
    ASSERT( d.Claves().Cardinal() == 0 );

    d.Definir("hola",41);
    ASSERT( d.Obtener("hola") == 41 );

    d.Definir("casa",22);
    d.Definir("casona",72);
    d.Definir("casas",79);
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("casa") );
    ASSERT( d.Definido("casas") );
    ASSERT( d.Definido("casona") );

    d.Borrar("casa");
    ASSERT( d.Definido("hola") );
    ASSERT( !d.Definido("casa") );
    ASSERT( d.Definido("casas") );
    ASSERT( d.Definido("casona") );

    d.Borrar("casas");
    ASSERT( d.Definido("hola") );
    ASSERT( !d.Definido("casa") );
    ASSERT( !d.Definido("casas") );
    ASSERT( d.Definido("casona") );

    d.Borrar("casona");
    ASSERT( d.Definido("hola") );
    ASSERT( !d.Definido("casa") );
    ASSERT( !d.Definido("casas") );
    ASSERT( !d.Definido("casona") );

    d.Borrar("hola");
    ASSERT( !d.Definido("hola") );
    ASSERT( !d.Definido("casa") );
    ASSERT( !d.Definido("casas") );
    ASSERT( !d.Definido("casona") );
    ASSERT( d.Claves().Cardinal() == 0 );
}

//chequea el iterador
void test_iterador()
{
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);

    int i1 = 42;
    int i2 = 22;

    typename DiccString<int>::Elem e1 = DiccString<int>::Elem("hola", i1);
    typename DiccString<int>::Elem e2 = DiccString<int>::Elem("casa", i2);

    typename DiccString<int>::Iterador itD = d.CrearIt();

    ASSERT( itD.HaySiguiente() );
    ASSERT( itD.SiguienteClave() == "hola");
    ASSERT( itD.SiguienteSignificado() == 42);
    ASSERT( itD.Siguiente().clave == e1.clave);
    ASSERT( itD.Siguiente().significado == 42);

    itD.Avanzar();

    ASSERT( itD.Siguiente().clave == e2.clave);
    ASSERT( itD.Siguiente().significado == e2.significado);

    itD.Avanzar();

    ASSERT( !itD.HaySiguiente() );
}

int main() {
    RUN_TEST(test_claves_dicc_vacio);
    RUN_TEST(test_definir_definido);
    RUN_TEST(test_redefinir);
    RUN_TEST(test_obtener);
    RUN_TEST(test_borrar);
    RUN_TEST(test_iterador);

    return 0;
}
