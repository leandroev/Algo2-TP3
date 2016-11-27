// Compilar usando:
//	g++ -o tests_coordenada tests_coordenada.cpp 
//	valgrind --leak-check=full ./tests_coordenada

#include "Coordenada.h"
#include "aed2/Conj.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_coordenada() {
  // Conj<Coordenada> cc;
  // cc.Agregar(Coordenada(0,0));
  // cc.Agregar(Coordenada(0,1));
  // cc.Agregar(Coordenada(0,2));
  // cc.Agregar(Coordenada(1,2));
  // cc.Agregar(Coordenada(10,0));
  // cc.Agregar(Coordenada(1,4));
  std::cout << "\n" << (Coordenada(0,0) == Coordenada(0,0)) << std::endl;
  std::cout << (Coordenada(0,0) == Coordenada(0,1)) << std::endl;
	std::cout << Coordenada(1,3).Latitud() << std::endl;
	std::cout << Coordenada(1,3).Longitud() << std::endl;
  Nat a = Coordenada(0,0).Distancia(Coordenada(1,1),Coordenada(0,0));
  std::cout << a << std::endl;
  Nat b = Coordenada(0,0).Distancia(Coordenada(2,1),Coordenada(1,1));
  std::cout << b << std::endl;
  Nat c = Coordenada(0,0).Distancia(Coordenada(2,1),Coordenada(1,3));
  std::cout << c << std::endl;


}


int main(int argc, char **argv)
{
  RUN_TEST(test_constructor_coordenada);
  
  return 0;
}

