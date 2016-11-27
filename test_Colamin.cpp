// Compilar usando:
//	g++ -o test_Colamin test_Colamin.cpp Colamin.cpp 
//	valgrind --leak-check=full ./tests_Colamin

#include "aed2.h"
#include "Colamin.h"
#include "mini_test.h"

using namespace aed2;


void check_encolar(){

	ColaPr cola;
	ColaPr::Clave t1(1,2);
	cola.Encolar(t1);
	
    ASSERT_EQ(cola.Proximo().prioridad,1);
    ASSERT_EQ(cola.Proximo().num,2)

	ColaPr::Clave t2(5,4);
	cola.Encolar(t2);
	ASSERT_EQ(cola.Proximo().prioridad,1);
    ASSERT_EQ(cola.Proximo().num,2)

	ColaPr::Clave t3(7,2);
	cola.Encolar(t3);
	ASSERT_EQ(cola.Proximo().prioridad,1);
    ASSERT_EQ(cola.Proximo().num,2)

	ColaPr::Clave t4(2,2);
	cola.Encolar(t4);
	ASSERT_EQ(cola.Proximo().prioridad,1);
    ASSERT_EQ(cola.Proximo().num,2)

	ColaPr::Clave t5(1,1);
	cola.Encolar(t5);
	ASSERT_EQ(cola.Proximo().prioridad,1);
    ASSERT_EQ(cola.Proximo().num,1)

	ColaPr::Iterador it = cola.CrearIt();
	// std::cout<<cola<<std::endl;
	return;

}
void check_ConstructorVacio(){

	ColaPr cola;
	ASSERT(cola.EsVacio());
	ColaPr cola2(cola);
	ASSERT(cola2.EsVacio());
	ColaPr::Clave t1 (1,2);
	cola.Encolar(t1);
	ASSERT(cola2.EsVacio());
	ASSERT(!(cola.EsVacio()));
	return;

}
void check_MostrarCola(){

	ColaPr colas;

	ColaPr::Clave t1(1,2);
	colas.Encolar(t1);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)"<<std::endl;

	ColaPr::Clave t2(5,4);
	
	colas.Encolar(t2);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)(5,4)"<<std::endl;

	ColaPr::Clave t3(7,2);
	colas.Encolar(t3);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)(5,4)(7,2)"<<std::endl;

	ColaPr::Clave t4 (2,2);
	colas.Encolar(t4);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)(2,2)(5,4)(7,2)"<<std::endl;

	ColaPr::Clave t5(2,1);
	colas.Encolar(t5);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)(2,1)(5,4)(2,2)(7,2)"<<std::endl;

	ColaPr::Clave t6(10,5);
	colas.Encolar(t6);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)(2,1)(5,4)(2,2)(7,2)(10,5)"<<std::endl;

	ColaPr::Clave t7 (10,3);
	colas.Encolar(t7);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,2)(2,1)(5,4)(2,2)(7,2)(10,5)(10,3)"<<std::endl;

	ColaPr::Clave t8 (1,1);
	colas.Encolar(t8);
	// std::cout<<colas;
	// std::cout << " es Igual a \n" << "(1,1)(1,2)(2,1)(5,4)(2,2)(7,2)(10,5)(10,3)"<<std::endl;
}

void check_Desencolar(){


	ColaPr colas;

	ColaPr::Clave t1(1,2);
	colas.Encolar(t1);

	ColaPr::Clave t2(5,5);
	
	ColaPr::Iterador it5 = colas.Encolar(t2);


	ColaPr::Clave t3(7,2);
	ColaPr::Iterador it7 = colas.Encolar(t3);

	ColaPr::Clave t4 (2,2);
	ColaPr::Iterador it = colas.Encolar(t4);


	ColaPr::Clave t5(2,1);
	colas.Encolar(t5);


	ColaPr::Clave t6(10,5);
	ColaPr::Iterador it6 = colas.Encolar(t6);


	ColaPr::Clave t7 (10,3);
	ColaPr::Iterador it2 = colas.Encolar(t7);



	// std::cout<<colas<<std::endl;
	// std::cout<< "asdasdsmakdasnmdksandksandksandksadksandkasndnsadnsakndksakdnsa SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<std::endl;
	it5.eliminar();
	// std::cout<< "se borro (5,5)"<<std::endl;
	// std::cout<<colas<<std::endl;
	it7.eliminar();
	// std::cout<< "se borro (7,2)"<<std::endl;
	// std::cout<<colas<<std::endl;
	it6.eliminar();;
	// std::cout<< "se borro (10,5)"<<std::endl;
	// std::cout<<colas<<std::endl;
	it.eliminar();
	// std::cout<< "se borro (2,2)"<<std::endl;
	// std::cout<<colas<<std::endl;
	it2.eliminar();
	// std::cout<< "se borro (10,3)"<<std::endl;
	// std::cout<<colas<<std::endl;
	colas.Desencolar();
	// std::cout<< "se borro (1,2)"<<std::endl;
	// std::cout<<colas<<std::endl;
	colas.Desencolar();
	// std::cout<< "se borro (2,1)"<<std::endl;
	// std::cout<<colas<<std::endl;

	return;


}

void check_Desencolar2(){
	
	ColaPr colas;

	ColaPr::Clave t1(3,1);
	ColaPr::Iterador it2 = colas.Encolar(t1);
	// std::cout<< "se agrego (3,1)"<<std::endl;

	ColaPr::Clave t2(2,1);
	
	colas.Encolar(t2);
	// std::cout<< "se agrego (2,1)"<<std::endl;


	ColaPr::Clave t3(7,1);
	ColaPr::Iterador it = colas.Encolar(t3);
	// std::cout<< "se agrego (7,1)"<<std::endl;
	it.eliminar();
	// std::cout<< "se borro (7,1)"<<std::endl;
	// std::cout<< colas<<std::endl;
	
	ColaPr::Clave t4 (2,4);
	ColaPr::Iterador it3 = colas.Encolar(t4);
	// std::cout<< "se agrego (2,4)"<<std::endl;
	// std::cout<< colas <<std::endl;

	ColaPr::Clave t5(2,5);
	colas.Encolar(t5);
	// std::cout<< "se agrego (2,5)"<<std::endl;


	// std::cout<< colas <<std::endl;

	it2.eliminar();
	// std::cout<< "se borro (3,1)"<<std::endl;
	// std::cout<< colas <<std::endl;

	colas.Desencolar();
	// std::cout<< "se borro (2,1)"<<std::endl;
	// std::cout<< colas <<std::endl;

	it3.eliminar();
	// std::cout<< "se borro (2,4)"<<std::endl;
	// std::cout<< colas <<std::endl;


	colas.Encolar(t2);
	// std::cout<< "se agrego (2,1)"<<std::endl;
	// std::cout<< colas <<std::endl;

	return;

}

void check_Desencolar3(){

	ColaPr cola;
	ColaPr::Clave t1(5,2);
	// std::cout << "se encola (5,2)" << std::endl;
	ColaPr::Iterador it1 = cola.Encolar(t1);
	// std::cout<< cola <<std::endl;
	ColaPr::Clave t2 (6,6);
	// std::cout << "se encola (6,6)" << std::endl;
	cola.Encolar(t2);
	// std::cout<< cola <<std::endl;
	ColaPr::Clave t3(6,1);
	// std::cout << "se encola (6,1)" << std::endl;
	ColaPr::Iterador it3 = cola.Encolar(t3);
	// std::cout<< cola <<std::endl;
	ColaPr::Clave t4 (6,7);
	// std::cout << "se encola (6,7)" << std::endl;
	ColaPr::Iterador it4 = cola.Encolar(t4);
	// std::cout<< cola <<std::endl;
	ColaPr::Clave t5 (2,5);
	// std::cout << "se encola (2,5)" << std::endl;
	cola.Encolar(t5);
	// std::cout<< cola <<std::endl;
	
	
	
	// std::cout << "el actual de it4 es (" << it4.Actual().prioridad << "," << it4.Actual().num << ")" << std::endl;
	// std::cout << "el actual de it3 es (" << it3.Actual().prioridad << "," << it3.Actual().num << ")" << std::endl;
	// std::cout << "el actual de it1 es (" << it1.Actual().prioridad << "," << it1.Actual().num << ")" << std::endl;
	
	// std::cout<< "A BORRRRRRRRRRRRRAAAAAAAAAAAAAAAAAR" <<std::endl;
	it4.eliminar();
	// std::cout << "se borro (6,7)" << std::endl;
	// std::cout<< cola <<std::endl;
	
	it3.eliminar();
	// std::cout<< "se borro (6,1)"<<std::endl;
	// std::cout<< cola <<std::endl;

	
	it1.eliminar();
	// std::cout<< "se borro (5,2)"<<std::endl;
	// std::cout<< cola <<std::endl;

	cola.Desencolar();
	// std::cout<< "se borro (2,5)"<<std::endl;
	// std::cout<< cola <<std::endl;

	cola.Desencolar();
	// std::cout<< "se borro (6,6)"<<std::endl;
	// std::cout<< cola <<std::endl;
	
	return;

}


int main() {

 RUN_TEST(check_ConstructorVacio);
 RUN_TEST(check_encolar);
 RUN_TEST(check_MostrarCola);
 RUN_TEST(check_Desencolar);
 RUN_TEST(check_Desencolar2);
 RUN_TEST(check_Desencolar3);	
 std::cout<<"FIN"<<std::endl;

return 0;
}
