#ifndef COLAPR_H
#define COLAPR_H
#include "aed2.h"
#include <iostream>
#include <ostream>


namespace aed2{

class ColaPr
{
	
	public:
		struct Clave{
			Clave(const Nat p, const Nat r) : prioridad(p),num(r){};
            Nat prioridad;
            Nat num;
            bool operator<(const Clave& k) const{
			if 	(prioridad < k.prioridad)
				return true;
			else if (prioridad == k.prioridad && num < k.num)
				return true;
			else
				return false;
			}
		};

	private:
		struct Nodo{
			Nodo(const Clave& k) : raiz(k), der(NULL), izq(NULL), padre(NULL) {};
            Nodo* der;
            Nodo* izq;
            Nodo* padre;
            Clave raiz;
		};
		
    public:

		class Iterador;///Definicion abajo    
    

        ///Crea una cola de prioridad Vacia

        ColaPr();
        
        //Constructor que copia COLASVACIAS!??. Serviria para el diccionario.
        
       	ColaPr(const ColaPr& otra_nula);

        ///Destructor Cola de Prioridad

        ~ColaPr();

        ///Devuelve True si y solo si la cola es vacia

        bool EsVacio() const;


        ///Devuelve la primer clave de la cola , i.e la primera ingresada

        const Clave Proximo() const;

        ///Elimina la clave K de la cola de prioridad

    //    void Sacar(Iterador& it);

        ///Elimina al proximo  de la cola de prioridad

        void Desencolar();

		///Indica el tamaño(cantidad de elementos) de una cola. (Esta no estaba, pero bue(?

		const int Tamanio() const;

         ///Agrega la clave K al final de la cola

        const Iterador Encolar(const Clave& k);

        ///Funcion para mostrar el arbol de la cola de prioridad en PreOrder

        std::ostream& MostrarCola(std::ostream& os) const;

		///Crea un iterador al  proximo() de la cola

        Iterador CrearIt();

        ///FIN

        class Iterador{

			public:

			///Funciones del iterador de  Cola de prioridad:

			///Crea un iterador de Cola de prioriridad, de manera que el actual es el elemento de mayor prioridad.

			Iterador();

			///Devuelve el elemento siguiente de iterador
			
			Iterador& operator = (const typename ColaPr::Iterador& otro);

            bool HayMas() const;

            const Clave& Actual() const;

			///Elimina el actual del iterador.

			void eliminar();

			/// agrega la clave en la cola referenciada por el iterador.

			void Agregar(const Clave &k);

			///Lo dejo afuero para probar algo;

			///Fin

        private:

			///Estructura interna:
			ColaPr* _cola;

			typename ColaPr::Nodo* _nodo;
			/// Constructor privado
			Iterador(ColaPr* c, typename ColaPr::Nodo* n);

			friend typename ColaPr::Iterador ColaPr::CrearIt();

			typename ColaPr::Nodo* ActualReal() const ;

        };


		///Estructura interna de ColaPr:

		private:


        Nodo* _arbol;

        Nat _CantNodos;

        ///Funciones privadas de Cola de prioridad:

        ///Convierte un numero a binario. La dejo aca para poder probarla en los test

        Lista<Nat> Binario(Nat n);

        ///Devuelve el nodo padre al que se le insertara la proxima hoja.Idem la de arriba

        Nodo* PadreUltimaHoja(Nat n);

        ///Recorre el arbol del heap en PreOrder.

        void PreOrder(const Nodo* n, std::ostream& os) const;

        ///Swapea dos nodos, reacomodando sus referencias dentro de la cola.

		void Swap(Nodo* a, Nodo* b);//Podrian ser referencias supongo, igual es una funcion interna.

};
 std::ostream& operator<<(std::ostream& os, const ColaPr& cp);
}

#endif // COLAPR_H
