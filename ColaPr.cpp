
#include <string>
#include <iostream>
#include <stdio.h>
#include <ostream>

#include "aed2.h"
#include "ColaPr.h"


namespace aed2{

///Implementacion de funciones:

//Constructor y destructor:
//*****************************//
//*****************************//
ColaPr::ColaPr()
    :_arbol(NULL), _CantNodos(0){}

ColaPr::ColaPr(const ColaPr& otra_nula)
	:_arbol(NULL),_CantNodos(0){}

ColaPr::~ColaPr()
{
	while(Tamanio() > 0 ){
 		Desencolar();
 	}
 	return;
}

//Vale la pena hacer constructor por copia?


//*****************************//
//*****************************//

//Funciones Privadas:
//*****************************//
//*****************************//
 Lista<Nat> ColaPr::Binario(Nat n){

    Lista<Nat> l;

    while(n!= 1 && n!= 0){
        l.AgregarAdelante(n % 2);
        n = n / 2;
    }
    l.AgregarAdelante(n);
    return l;
}

 ColaPr::Nodo* ColaPr::PadreUltimaHoja(Nat n){

	 Lista<Nat>::Iterador it;
	 Lista<Nat> l(Binario(n));
	 it = l.CrearIt();
	 Nodo* actual = _arbol;
	 Nodo* padre = NULL;
	 it.Avanzar();

	while(it.HaySiguiente()){

		padre = actual;
		if  (it.Siguiente() == 0)
			actual = actual->izq;
		else
			actual = actual->der;
		it.Avanzar();

	}

	return padre;

}
//*****************************//
//*****************************//

//Funciones Del Iterador:
//*****************************//
//*****************************//



ColaPr::Iterador::Iterador()
	:_cola(NULL), _nodo(NULL)
	{}

ColaPr::Iterador::Iterador(ColaPr* c, ColaPr::Nodo* n)
	:_cola(c), _nodo(n)
	{}

ColaPr::Iterador& ColaPr::Iterador::operator = (const typename ColaPr::Iterador& otro){

  _nodo = otro._nodo;
  _cola = otro._cola;

  return *this;

}

bool ColaPr::Iterador::HayMas() const{

    return _nodo != NULL;

}

const ColaPr::Clave& ColaPr::Iterador::Actual() const{

	return _nodo->raiz;

}

ColaPr::Nodo* ColaPr::Iterador::ActualReal() const {

 return _nodo;

}


void ColaPr::Iterador::Agregar(const ColaPr::Clave &k){

	Nodo* nuevo = new Nodo(k);

	if (_cola->_arbol == NULL){ //caso cola vacia

		_cola->_arbol = nuevo;
		_cola->_CantNodos = 1;
		_nodo = nuevo;
	}
	else{

		Nodo* p = _cola->PadreUltimaHoja(_cola->_CantNodos +1);
		nuevo->padre = p;

		if (p->izq == NULL)
				p->izq = nuevo;
		else
				p->der = nuevo;

		Nodo* q = nuevo;

		while( q->padre != NULL && q->raiz < q->padre->raiz ){
			_cola->Swap(q, q->padre);
		}

		_cola->_CantNodos ++;
		_nodo = q;
	}
 }

 void ColaPr::Iterador::eliminar(){


	if (_cola->_CantNodos == 1){
		delete (_nodo);
		_cola->_arbol = NULL;

	}
	

	else{
		Nodo* p = _cola->PadreUltimaHoja(_cola->_CantNodos);
		Nodo*r;
		//Buscamos el ultimo Nodo y lo swapeamos con el acutal del iterado
		if(p->der == NULL){
			r = p->izq; 
			_cola->Swap(ActualReal(),r);
			Nodo * t = _cola->PadreUltimaHoja(_cola->_CantNodos);
			t->izq = NULL;
		}

		else{
			//std::cout<< "11111111111111111111111111111111111111111111111111111"<<std::endl;
				r = p->der;
				//std::cout << r->raiz.prioridad << r->raiz.rur << std::endl;
				//std::cout << ActualReal()->raiz.prioridad << ActualReal()->raiz.rur << std::endl;
				_cola->Swap(ActualReal(),r);
				Nodo * t = _cola->PadreUltimaHoja(_cola->_CantNodos);
				t->der = NULL;

		}

		Nodo* q = r;
		//pregunto si debe subir o bajar

		if ( q->padre != NULL && q->raiz < q->padre->raiz){
			//std::cout<< "22222222222222222222222222222222222222222222222222222"<<std::endl;
			while(q->padre != NULL && q->raiz < q->padre->raiz){
				_cola->Swap(q, q->padre);
			}

		}
		else{
			//std::cout<< "3333333333333333333333333333333333333333333333333333333333"<<std::endl;
			while((q->izq != NULL && q->izq->raiz <  q->raiz) || (q->der != NULL && q->der->raiz < q->raiz)){
				if (q->izq == NULL){
					_cola->Swap(q,q->der);
				}	
				else if(q->der == NULL){
					_cola->Swap(q,q->izq);
				}	
				else{
					if(q->izq->raiz < q->der->raiz){
						_cola->Swap(q, q->izq);
					}
					else{
						_cola->Swap(q,q->der);
					}
				}
			}
		}
		delete(_nodo);
	}
	_cola->_CantNodos --;
	return;
 }

void ColaPr::Desencolar(){

	ColaPr::Iterador it = CrearIt(); //?
	it.eliminar();


}
//*****************************//
//*****************************//

//Funciones De la ColaPrioriridad:
//*****************************//
//*****************************//

void ColaPr::Swap(ColaPr::Nodo* a, ColaPr::Nodo* b){
		/*std::cout << " ///////////////// EL COMIENZO DE UN NUEVO SWAP AMEGO //////////////////*****************" <<std::endl;
		std::cout << *this << std::endl;
		std::cout << " el actual a es (" << a->raiz.prioridad <<"," << a->raiz.rur<<")" <<std::endl;
		std::cout << " el actual b es (" << b->raiz.prioridad <<"," << b->raiz.rur<<")" <<std::endl;
		if(a->izq != NULL){
			std::cout << " el actual a->izq es (" << a->izq->raiz.prioridad <<"," << a->izq->raiz.rur<<")" <<std::endl;
			std::cout << " el actual a->izq->padre es (" << a->izq->padre->raiz.prioridad <<"," << a->izq->padre->raiz.rur<<")" <<std::endl;
		}
		if(a->der != NULL){
			std::cout << " el actual a->der es (" << a->der->raiz.prioridad <<"," << a->der->raiz.rur<<")" <<std::endl;
			std::cout << " el actual a->der->padre es (" << a->der->padre->raiz.prioridad <<"," << a->der->padre->raiz.rur<<")" <<std::endl;
		}
		if(a->padre != NULL){
			std::cout << " el actual a->padre es (" << a->padre->raiz.prioridad <<"," << a->padre->raiz.rur<<")" <<std::endl;
			if(a->padre->izq != NULL){
				std::cout << " el actual a->padre->izq es (" << a->padre->izq->raiz.prioridad <<"," << a->padre->izq->raiz.rur<<")" <<std::endl;
				std::cout << " el actual a->padre->izq->padre es (" << a->padre->izq->padre->raiz.prioridad <<"," << a->padre->izq->padre->raiz.rur<<")" <<std::endl;
			}
			if(a->padre->der != NULL){
				std::cout << " el actual a->padre->der es (" << a->padre->der->raiz.prioridad <<"," << a->padre->der->raiz.rur<<")" <<std::endl;
				std::cout << " el actual a->padre->der->padre es (" << a->padre->der->padre->raiz.prioridad <<"," << a->padre->der->padre->raiz.rur<<")" <<std::endl;
			}
		}
		if(b->izq != NULL){
			std::cout << " el actual b->izq es (" << b->izq->raiz.prioridad <<"," << b->izq->raiz.rur<<")" <<std::endl;
			std::cout << " el actual b->izq->padre es (" << b->izq->padre->raiz.prioridad <<"," << b->izq->padre->raiz.rur<<")" <<std::endl;
		}
		if(b->der != NULL){
			std::cout << " el actual b->der es (" << b->der->raiz.prioridad <<"," << b->der->raiz.rur<<")" <<std::endl;
			std::cout << " el actual b->der->padre es (" << b->der->padre->raiz.prioridad <<"," << b->der->padre->raiz.rur<<")" <<std::endl;
		}
		if(b->padre != NULL){
			std::cout << " el actual b->padre es (" << b->padre->raiz.prioridad <<"," << b->padre->raiz.rur<<")" <<std::endl;
			if(b->padre->izq != NULL){
				std::cout << " el actual b->padre->izq es (" << b->padre->izq->raiz.prioridad <<"," << b->padre->izq->raiz.rur<<")" <<std::endl;
				std::cout << " el actual b->padre->izq->padre es (" << b->padre->izq->padre->raiz.prioridad <<"," << b->padre->izq->padre->raiz.rur<<")" <<std::endl;
			}
			if(b->padre->der != NULL){
				std::cout << " el actual b->padre->der es (" << b->padre->der->raiz.prioridad <<"," << b->padre->der->raiz.rur<<")" <<std::endl;
				std::cout << " el actual b->padre->der->padre es (" << b->padre->der->padre->raiz.prioridad <<"," << b->padre->der->padre->raiz.rur<<")" <<std::endl;
			}
		}
		*/
		if(_arbol == a){
			_arbol = b;
		}
		else if(_arbol == b){
			_arbol = a;
		}
		Nodo* HijoDer;
		Nodo* HijoIzq;
		Nodo* father;

		if(a->izq == b){
			HijoDer = a->der;
			father = a->padre;
			a->izq = b->izq;
			a->der = b->der;
			a->padre = b;
			b->izq = a;
			b->der = HijoDer;
			b->padre = father;

			if(a->izq != NULL){
				a->izq->padre = a;
			}
			if(a->der != NULL){
				a->der->padre = a;
			}

			if(HijoDer != NULL)
				HijoDer->padre = b;

			if(father != NULL){
				if(father->izq == a)
					father->izq = b;
				else
					father->der = b;
			}
		}
			else{
				if(a->der == b){

				HijoIzq = a->izq;
				father = a->padre;
				a->izq = b->izq;
				a->der = b->der;
				a->padre = b;
				b->der = a;
				b->izq = HijoIzq;
				b->padre = father;

				if(a->izq != NULL){
					a->izq->padre = a;
				}
				if(a->der != NULL){
					a->der->padre = a;
				}

				if(HijoIzq != NULL)
					HijoIzq->padre = b;

				if(father != NULL){

					if(father->izq == a)
						father->izq = b;
					else
						father->der = b;
				}
				}
		else{ 
			if (b->izq == a){
			//std::cout << "$&&&/()=**++++++++++++++++++++++++++++##########################################!°°°°°°°°°°°°°°°°°°+)(/&$$&/()¡" <<std::endl;
			HijoDer = b->der;
			father = b->padre;
			b->izq = a->izq;
			b->der = a->der;
			b->padre = a;
			a->izq = b;
			a->der = HijoDer;
			a->padre = father;
			
			if(b->izq != NULL){
				b->izq->padre = b;
			}
			if(b->der != NULL){
				b->der->padre = b;
			}

			if(HijoDer != NULL)
				HijoDer->padre = a;

			if(father != NULL){

					if(father->izq == b)
						father->izq = a;
					else
						father->der = a;
			}
		}
		else{
		 if(b->der == a){

			HijoIzq = b->izq;
			father  = b->padre;
			b->izq = a->izq;
			b->der = a->der;
			b->padre = a;
			a->der = b;
			a->izq = HijoIzq;
			a->padre = father;
			
			if(b->izq != NULL){
				b->izq->padre = b;
			}
			if(b->der != NULL){
				b->der->padre = b;
			}

			if(HijoIzq != NULL)
				HijoIzq->padre = a;

			if(father != NULL){

				if(father->izq == b)
					father->izq = a;
				else
					father->der = a;
			}
		}
		else{
			//std::cout << " *************************************************" <<std::endl;
			HijoIzq = a->izq;
			HijoDer = a->der;
			father = a->padre;
			b->izq = HijoIzq;
			b->der = HijoDer;
			b->padre = father;
			if(father != NULL){
				if(father->izq == a)
					father->izq = b;
				else
					father->der = b;
				}
			if(HijoIzq != NULL)
				HijoIzq->padre = b;
			if(HijoDer != NULL)
				HijoDer->padre = b;
		}
	}
}
}	
		/*std::cout << " //////////////// FINN de UN NUEVO SWAP AMEGO //////////////////*****************" <<std::endl;
		std::cout << " el actual a es (" << a->raiz.prioridad <<"," << a->raiz.rur<<")" <<std::endl;
		std::cout << " el actual b es (" << b->raiz.prioridad <<"," << b->raiz.rur<<")" <<std::endl;
		if(a->izq != NULL){
			std::cout << " el actual a->izq es (" << a->izq->raiz.prioridad <<"," << a->izq->raiz.rur<<")" <<std::endl;
			std::cout << " el actual a->izq->padre es (" << a->izq->padre->raiz.prioridad <<"," << a->izq->padre->raiz.rur<<")" <<std::endl;
		}
		if(a->der != NULL){
			std::cout << " el actual a->der es (" << a->der->raiz.prioridad <<"," << a->der->raiz.rur<<")" <<std::endl;
			std::cout << " el actual a->der->padre es (" << a->der->padre->raiz.prioridad <<"," << a->der->padre->raiz.rur<<")" <<std::endl;
		}
		if(a->padre != NULL){
			std::cout << " el actual a->padre es (" << a->padre->raiz.prioridad <<"," << a->padre->raiz.rur<<")" <<std::endl;
			if(a->padre->izq != NULL){
				std::cout << " el actual a->padre->izq es (" << a->padre->izq->raiz.prioridad <<"," << a->padre->izq->raiz.rur<<")" <<std::endl;
				std::cout << " el actual a->padre->izq->padre es (" << a->padre->izq->padre->raiz.prioridad <<"," << a->padre->izq->padre->raiz.rur<<")" <<std::endl;
			}
			if(a->padre->der != NULL){
				std::cout << " el actual a->padre->der es (" << a->padre->der->raiz.prioridad <<"," << a->padre->der->raiz.rur<<")" <<std::endl;
				std::cout << " el actual a->padre->der->padre es (" << a->padre->der->padre->raiz.prioridad <<"," << a->padre->der->padre->raiz.rur<<")" <<std::endl;
			}
		}
		if(b->izq != NULL){
			std::cout << " el actual b->izq es (" << b->izq->raiz.prioridad <<"," << b->izq->raiz.rur<<")" <<std::endl;
			std::cout << " el actual b->izq->padre es (" << b->izq->padre->raiz.prioridad <<"," << b->izq->padre->raiz.rur<<")" <<std::endl;
		}
		if(b->der != NULL){
			std::cout << " el actual b->der es (" << b->der->raiz.prioridad <<"," << b->der->raiz.rur<<")" <<std::endl;
			std::cout << " el actual b->der->padre es (" << b->der->padre->raiz.prioridad <<"," << b->der->padre->raiz.rur<<")" <<std::endl;
		}
		if(b->padre != NULL){
			std::cout << " el actual b->padre es (" << b->padre->raiz.prioridad <<"," << b->padre->raiz.rur<<")" <<std::endl;
			if(b->padre->izq != NULL){
				std::cout << " el actual b->padre->izq es (" << b->padre->izq->raiz.prioridad <<"," << b->padre->izq->raiz.rur<<")" <<std::endl;
				std::cout << " el actual b->padre->izq->padre es (" << b->padre->izq->padre->raiz.prioridad <<"," << b->padre->izq->padre->raiz.rur<<")" <<std::endl;
			}
			if(b->padre->der != NULL){
				std::cout << " el actual b->padre->der es (" << b->padre->der->raiz.prioridad <<"," << b->padre->der->raiz.rur<<")" <<std::endl;
				std::cout << " el actual b->padre->der->padre es (" << b->padre->der->padre->raiz.prioridad <<"," << b->padre->der->padre->raiz.rur<<")" <<std::endl;
			}
		}
		*/
		return;
}


 ColaPr::Iterador ColaPr::CrearIt(){


	return Iterador(this, _arbol);

 }

 ColaPr::Iterador ColaPr::Encolar(const Clave& k){

	ColaPr::Iterador it = CrearIt();
	it.Agregar(k);
	return it; //referencia a variable local, pero parece funcionar. ??

 }

 bool ColaPr::EsVacio() const{
	return _arbol == NULL;
 }

 const int ColaPr::Tamanio() const{

	return _CantNodos;
 }

 const ColaPr::Clave ColaPr::Proximo() const{

	ColaPr::Clave k(_arbol->raiz.prioridad,_arbol->raiz.num);
	return k;

 }

 std::ostream& operator<<(std::ostream& os, const ColaPr& cp)
{
  return cp.MostrarCola(os);
}

 std::ostream& ColaPr::MostrarCola(std::ostream& os) const{

	 ColaPr::PreOrder(_arbol,os);
 }

 void ColaPr::PreOrder(const ColaPr::Nodo* n, std::ostream& os) const{

	if (n == NULL){
		os << "" ;
		return;
	}
	//visitar nodo
	os << "(" ;
	os << n->raiz.prioridad;
	os << ",";
	os << n->raiz.num;
	os << ")";

	//llamadas recursivas
	ColaPr::PreOrder(n->izq,os);
	ColaPr::PreOrder(n->der,os);
	return;
 }



}
