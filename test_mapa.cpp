// Compilar usando:
//	g++ -o tests_mapa tests_mapa.cpp 
//	valgrind --leak-check=full ./tests
#include "Mapa.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_mapa() {
	Mapa mapa;
	ASSERT(mapa.Coordenadas().EsVacio() == 1);
	ASSERT_EQ(mapa.Coordenadas().EsVacio(),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(1,1)),false);

}

void test_AgregarCoordenada() {

	Mapa mapa;
	ASSERT(mapa.Coordenadas().EsVacio() == 1);
	ASSERT_EQ(mapa.Coordenadas().EsVacio(),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(0,1)),false);

  	mapa.AgregarCoor(Coordenada(0,1));
  	ASSERT_EQ(mapa.posExistente(Coordenada(0,1)),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(0,0)),false);
	
	

	mapa.AgregarCoor(Coordenada(0,0));
	ASSERT_EQ(mapa.posExistente(Coordenada(0,0)),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(0,1)),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(1,0)),false);
	ASSERT_EQ(mapa.posExistente(Coordenada(0,2)),false);
	ASSERT_EQ(mapa.posExistente(Coordenada(1,1)),false);
	mapa.AgregarCoor(Coordenada(1,1));
	ASSERT_EQ(mapa.posExistente(Coordenada(0,0)),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(0,1)),true);
	ASSERT_EQ(mapa.posExistente(Coordenada(1,1)),true);

	ASSERT_EQ(mapa.hayCamino(Coordenada(1,1),Coordenada(1,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,1)),true);
	


	


}

void test_AgregarCoordenada2() {
  
	Mapa mapa;
	
	mapa.AgregarCoor(Coordenada(0,1));
	
	
	mapa.AgregarCoor(Coordenada(0,0));
	
	mapa.AgregarCoor(Coordenada(1,0));
	
	

	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(1,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(0,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(1,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(1,0)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(0,0)),true);

 	
  	mapa.AgregarCoor(Coordenada(3,1));
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(3,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(3,1)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(3,1)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(3,1)),false);
	
	mapa.AgregarCoor(Coordenada(2,1));

	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(2,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(0,0)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(0,1)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(1,0)),false);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(3,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(2,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(2,1)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(2,1)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(2,1)),false);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(2,1)),true);
 
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(1,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(0,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(1,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(1,0)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(0,0)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(3,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(0,0)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(0,1)),false);
	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(1,0)),false);
	
	mapa.AgregarCoor(Coordenada(2,0));


	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(2,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(1,0)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(3,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(2,1),Coordenada(2,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(2,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(2,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(2,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(2,1)),true);
 
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(1,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(0,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(0,1),Coordenada(1,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(0,0),Coordenada(1,0)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(1,0),Coordenada(0,0)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(3,1)),true);
 	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(0,0)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(0,1)),true);
	ASSERT_EQ(mapa.hayCamino(Coordenada(3,1),Coordenada(1,0)),true);
	
}



int main(int argc, char **argv)
{
  RUN_TEST(test_constructor_mapa);
  RUN_TEST(test_AgregarCoordenada);
  RUN_TEST(test_AgregarCoordenada2);

  return 0;
}


