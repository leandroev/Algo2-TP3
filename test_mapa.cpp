// Compilar usando:
//	g++ -o tests_mapa tests_mapa.cpp 
//	valgrind --leak-check=full ./tests

#include "Mapa.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_mapa() {
  
}


int main(int argc, char **argv)
{
  RUN_TEST(test_constructor_mapa);
  
  return 0;
}

