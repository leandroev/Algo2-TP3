
/* No usados
 *
 * Codigo de funciones no utilizadas en el Juego
 * Codigo de operadores no utilizados directamente
 *
 * Pero en caso de que sean necesarios para los tests de la catedra,
 * ya estan codeados ;)
 *
 */

/*** DiccString ***/

// Dada una clave, la borra del diccionario junto a su significado.
// PRE: La clave está definida.
void Borrar(const String& clave);

template <typename T>
void DiccString<T>::Borrar(const String& clave)
{
    assert( Definido(clave) );

    if (this->claves.Longitud() == 1)
    {
        borrarNodo(this->raiz);
        this->raiz = NULL;
        this->claves.Fin();
        return;
    }

    const char* chars = clave.c_str();

    int c = (int)chars[0];
    Nodo* it = this->raiz->hijos[(int)chars[0]];
    Nodo* itAnt = this->raiz;
    Nodo* itAPodar = NULL;
    Nodo* itAPodarPadre = NULL;

    for (int i = 1; i < clave.length(); i++)
    {
        bool esCandidato = !it->significado.HaySiguiente();

        if (esCandidato)
        {
            for (int j = 0; j < 256; j++)
                if (j != (int)chars[i]) esCandidato &= !it->hijos.Definido(j);
        }

        if (esCandidato)
        {
            if (itAPodar == NULL)
            {
                itAPodar = it;
                itAPodarPadre = itAnt;
                c = (int)chars[i-1];
            }
        }
        else
        {
            itAPodar = NULL;
            itAPodarPadre = NULL;
        }

        itAnt = it;
        it = it->hijos[(int)chars[i]];
    }

    if (itAPodar == NULL)
    {
        bool sinHijos = true;
        for (int k = 0; k < 256; k++) sinHijos &= !it->hijos.Definido(k);
        if (sinHijos)
        {
            borrarNodo(it);
            itAnt->hijos.Borrar((int)chars[clave.length()-1]);
        }
        else
        {
            //T* psign = it->significado.Siguiente();
            it->significado.EliminarSiguiente();
            //delete psign;
            it->significado = Lista<T>().CrearIt();
        }
    }
    else
    {
        borrarNodo(itAPodar);
        itAPodarPadre->hijos.Borrar(c);
    }

    typename Lista<String>::Iterador itClaves = this->claves.CrearIt();
    while (itClaves.HaySiguiente() && itClaves.Siguiente() != clave) itClaves.Avanzar();
    itClaves.EliminarSiguiente();
}


/* DiccString::Iterador */

// Constructor por copia
Iterador(const typename DiccString<T>::Iterador& otro);

template <typename T>
DiccString<T>::Iterador::Iterador(const typename DiccString<T>::Iterador& otro)
  : itClaves(otro.itClaves), itSignificados(otro.itSignificados)
{ }

// Operador de asignacion
Iterador& operator = (const typename DiccString<T>::Iterador& otro);

template <typename T>
typename DiccString<T>::Iterador& DiccString<T>::Iterador::operator = (const typename DiccString<T>::Iterador& otro)
{
    this->itClaves = otro.itClaves;
    this->itSignificados = otro.itSignificados;

    return *this;
}

// Operador de comparacion
bool operator == (const typename DiccString<T>::Iterador& otro) const;

template <typename T>
bool DiccString<T>::Iterador::operator == (const typename DiccString<T>::Iterador& otro) const
{
    return this->itClaves == otro.itClaves && this->itSignificados == otro.itSignificados;
}


/* DiccString::Elem */

// Operador de comparacion
bool operator == (const typename DiccString<T>::Elem& otro) const;

template <typename T>
bool DiccString<T>::Elem::operator == (const typename DiccString<T>::Elem& otro) const
{
    return this->clave == otro.clave && this->significado == otro.significado;
}

// Mostrar
friend std::ostream& operator << (std::ostream& os, const DiccString<T>::Elem& e)
{
    return os << "(" << e.clave << ", " << e.significado << ")";
}

