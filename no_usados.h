
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



/*** Juego ***/

/* Juego::ItJugadores */

ItJugadores(const typename Juego::ItJugadores& otro);

ItJugadores& operator = (const typename Juego::ItJugadores& otro);

bool operator == (const typename Juego::ItJugadores& otro) const;

