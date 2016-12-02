#include "Coordenada.h"

Coordenada::Coordenada(Nat lat, Nat lon) : latitud(lat), longitud(lon) { }

Nat Coordenada::Latitud() const
{
    return this->latitud;
}

Nat Coordenada::Longitud() const
{
    return this->longitud;
}

Nat Coordenada::Distancia(const Coordenada & otra) const
{
    Nat n1;
    Nat n2;

    if (this->latitud > otra.latitud)
    {
        n1 = (this->latitud - otra.latitud) * (this->latitud - otra.latitud);
    }
    else
    {
        n1 = (otra.latitud - this->latitud) * (otra.latitud - this->latitud);
    }

    if (this->longitud > otra.longitud)
    {
        n2 = (this->longitud - otra.longitud) * (this->longitud - otra.longitud);
    }
    else
    {
        n2 = (otra.longitud - this->longitud) * (otra.longitud - this->longitud);
    }

    return n1 + n2;
}

bool Coordenada::operator == (const Coordenada& otra) const
{
    return (this->latitud == otra.latitud) && (this->longitud == otra.longitud);
}

bool Coordenada::operator != (const Coordenada& otra) const{
    return (this->latitud != otra.latitud) || (this->longitud != otra.longitud);
}
