#include <iostream>
using namespace std;

class ClaseA {
  public:
   ClaseA(int a) : datoA(a) {
      cout << "Constructor de A" << endl;
   }
   ClaseA(const ClaseA& otra) {
       cout << "Constructor por Copia de A" << endl;
       this->datoA = otra.datoA;
   }

   int LeerA() const { return datoA; }

  protected:
   int datoA;
};

class ClaseB {
  public:
   ClaseB(int a, int b) : cA(a), datoB(b) {
      cout << "Constructor de B con int" << endl;
   }
   ClaseB(const ClaseA& a, int b) : cA(a), datoB(b) {
      cout << "Constructor de B con ClaseA" << endl;
   }
   int LeerB() const { return datoB; }
   int LeerA() const { return cA.LeerA(); }

  protected:
   int datoB;
   ClaseA cA;
};

int main() {

   ClaseA objetoA1(5);

   ClaseA objetoA2(objetoA1);

   ClaseB objetoB1(5,15);

   ClaseB objetoB2(objetoA2, 15);

   return 0;
}
