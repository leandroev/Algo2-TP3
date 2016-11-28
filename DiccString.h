#ifndef DICCSTRING_H_
#define DICCSTRING_H_

#include "aed2.h"
#include "TiposJuego.h"

using namespace aed2;

template <typename T>
class DiccString {

    public:

        // forward declarations
        struct Elem;
        class Iterador;

        // Construye un diccionario vacio.
        DiccString();

        // Destruye el diccionario.
        ~DiccString();

        // Define la clave con el significado de tipo T. Si ya estaba definida, la reescribe.
        void Definir(const String& clave, const T& significado);

        // Devuelve un bool, que es true si la clave pasada está definida en el diccionario.
        bool Definido(const String& clave) const;

        // Dada una clave, devuelve su significado.
        // PRE: La clave está definida.
        // Versión modificable y no modificable
        const T& Obtener(const String& clave) const;
        T& Obtener(const String& clave);

        // Devuelve las claves del diccionario.
        Conj<String> Claves() const;

        // Creación del Iterador no modificable
        Iterador CrearIt() const;

        /* Iterador
         *  Itera tupla < clave, significado > representada con la struct Elem
         *  Iterador de tipo const, no se permite modificar el diccionario
         */
        class Iterador {

            public:

                // Constructor default
                Iterador();

                // Indica si hay elementos para iterar
                bool HaySiguiente() const;
                bool HayAnterior() const;

                // Devuelve el siguiente elemento (clave o significado)
                const String& SiguienteClave() const;
                const T& SiguienteSignificado() const;

                // Devuelve el anterior elemento (clave o significado)
                const String& AnteriorClave() const;
                const T& AnteriorSignificado() const;

                // Devuelve el elemento apuntado (clave y significado)
                Elem Siguiente() const;
                Elem Anterior() const;

                // Mueve el iterador
                void Avanzar();
                void Retroceder();

            private:

                // estr
                typename Lista<String>::const_Iterador itClaves;
                typename Lista<T>::const_Iterador itSignificados;

                // Constructor que recibe el diccionario a iterar
                Iterador(const DiccString<T>* d);

                // Funcion CrearIt() es friend (necesita acceder a los miembros privados del iterador)
                friend typename DiccString<T>::Iterador DiccString<T>::CrearIt() const;
        };

        struct Elem {

            // estr
            const String& clave;
            const T& significado;

            // Constructor
            Elem(const String& c, const T& s) : clave(c), significado(s) { }

        };

    private:

        // estr interna
        struct Nodo {

            // estr
            typename Lista<T>::Iterador significado;
            Arreglo<Nodo*> hijos;

            // Constructor
            Nodo() : significado(Lista<T>().CrearIt()), hijos(Arreglo<Nodo*>(256)) { }
        };

        // estr
        Nodo* raiz;
        Lista<String> claves;
        Lista<T> significados;

        // funciones auxiliares
        void borrarNodo(Nodo* n);
};

/*** Implementacion ***/

// Operaciones del Diccionario

template <typename T>
DiccString<T>::DiccString(): raiz(NULL), claves(Lista<String>()), significados(Lista<T>()) { }

template <typename T>
DiccString<T>::~DiccString()
{
    if (this->raiz != NULL)
    {
        borrarNodo(this->raiz);
        this->raiz = NULL;
    }
}

template <typename T>
void DiccString<T>::borrarNodo(Nodo* n)
{
    if (n->significado.HaySiguiente())
    {
        //T* psign = n->significado.Siguiente();
        n->significado.EliminarSiguiente();
        //delete psign;
        n->significado = Lista<T>().CrearIt();
    }

    for (int i = 0; i < 256; i++)
    {
        if (n->hijos.Definido(i))
        {
            borrarNodo(n->hijos[i]);
            n->hijos.Borrar(i);
        }
    }

    delete n;
}

template <typename T>
void DiccString<T>::Definir(const String& clave, const T& significado)
{
    const char* chars = clave.c_str();

    if (this->claves.Longitud() == 0)
        this->raiz = new Nodo();

    Nodo* it = this->raiz;

    for (int i = 0; i < clave.length(); i++)
    {
        if (!it->hijos.Definido((int)chars[i]))
            it->hijos.Definir((int)chars[i], new Nodo());
        it = it->hijos[(int)chars[i]];
    }

    if (it->significado.HaySiguiente())
    {
        //T* psign = it->significado.Siguiente();
        it->significado.EliminarSiguiente();
        //delete psign;
        it->significado = Lista<T>().CrearIt();
    }

    typename Lista<T>::Iterador itSign = this->significados.AgregarAtras(significado);
    it->significado = itSign;

    this->claves.AgregarAtras(clave);
}

template <typename T>
bool DiccString<T>::Definido(const String& clave) const
{
    const char* chars = clave.c_str();

    Nodo* it = this->raiz;
    int i = 0;

    while (i < clave.length() && it != NULL)
    {
        if (it->hijos.Definido((int)chars[i]))
            it = it->hijos[(int)chars[i]];
        else
            it = NULL;
        i++;
    }

    return (i == clave.length()) && (it != NULL && it->significado.HaySiguiente());
}

template <typename T>
T& DiccString<T>::Obtener(const String& clave)
{
    assert( Definido(clave) );

    const char* chars = clave.c_str();

    Nodo* it = this->raiz;
    int i = 0;

    while (i < clave.length() && it != NULL)
    {
        it = it->hijos[(int)chars[i]];
        i++;
    }

    return it->significado.Siguiente();
}

template <typename T>
const T& DiccString<T>::Obtener(const String& clave) const
{
    assert( Definido(clave) );

    const char* chars = clave.c_str();

    Nodo* it = this->raiz;
    int i = 0;

    while (i < clave.length() && it != NULL)
    {
        it = it->hijos[(int)chars[i]];
        i++;
    }

    return it->significado.Siguiente();
}

template <typename T>
Conj<String> DiccString<T>::Claves() const
{
    Conj<String> cjClaves = Conj<String>();

    typename Lista<String>::const_Iterador itClaves = this->claves.CrearIt();
    while (itClaves.HaySiguiente())
    {
        cjClaves.AgregarRapido(itClaves.Siguiente());
        itClaves.Avanzar();
    }

    return cjClaves;
}

template <typename T>
typename DiccString<T>::Iterador DiccString<T>::CrearIt() const
{
  return Iterador(this);
}

// Operaciones del Iterador

template <typename T>
DiccString<T>::Iterador::Iterador(const DiccString<T>* d)
    : itClaves(d->claves.CrearIt()), itSignificados(d->significados.CrearIt())
{ }

template <typename T>
DiccString<T>::Iterador::Iterador()
{ }

template <typename T>
bool DiccString<T>::Iterador::HaySiguiente() const
{
    return this->itClaves.HaySiguiente();
}

template <typename T>
bool DiccString<T>::Iterador::HayAnterior() const
{
    return this->itClaves.HayAnterior();
}

template <typename T>
const String& DiccString<T>::Iterador::SiguienteClave() const
{
    return this->itClaves.Siguiente();
}

template <typename T>
const T& DiccString<T>::Iterador::SiguienteSignificado() const
{
    return this->itSignificados.Siguiente();
}

template <typename T>
const String& DiccString<T>::Iterador::AnteriorClave() const
{
    return this->itClaves.Anterior();
}

template <typename T>
const T& DiccString<T>::Iterador::AnteriorSignificado() const
{
    return this->itSignificados.Anterior();
}

template <typename T>
typename DiccString<T>::Elem DiccString<T>::Iterador::Siguiente() const
{
    return Elem(this->itClaves.Siguiente(), this->itSignificados.Siguiente());
}

template <typename T>
typename DiccString<T>::Elem DiccString<T>::Iterador::Anterior() const
{
    return Elem(this->itClaves.Anterior(), this->itSignificados.Anterior());
}

template <typename T>
void DiccString<T>::Iterador::Avanzar()
{
    this->itClaves.Avanzar();
    this->itSignificados.Avanzar();
}

template <typename T>
void DiccString<T>::Iterador::Retroceder()
{
    this->itClaves.Retroceder();
    this->itSignificados.Retroceder();
}

#endif // DICCSTRING_H_
