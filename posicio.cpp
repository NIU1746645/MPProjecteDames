#include "posicio.hpp"
#include <string>

//Passem d'un string a una posicio
Posicio::Posicio(const string& pos)
{
    char lletra = pos[0];
    m_columna = lletra - 'a';
    int numFila = pos[1] - '0';
    m_fila = 8 - numFila;
}

//Passa una posicio a un string
string Posicio::toString() const
{
    string posicio = "a1";
    posicio[0] = 'a' + m_columna;
    posicio[1] = '1' + (N_FILES - 1) - m_fila;
    return posicio;
}

//Passa un string a una posicio
void Posicio::fromString(const string& pos)
{
    m_fila = (N_FILES - 1) - (pos[1] - '1');
    m_columna = pos[0] - 'a';

    //Comprova si la posicio es valida
    if (m_fila < 0 || m_fila >= N_FILES || m_columna < 0 || m_columna >= N_COLUMNES)
    {
        m_fila = -1;
        m_columna = -1;
    }
}

//Compara si dues posicions són iguals
bool Posicio::operator==(const Posicio& posicio) const
{
    return m_fila == posicio.m_fila && m_columna == posicio.m_columna;
}

//Sobrecarrega de l'operador >> per llegir una Posicio
istream& operator>>(istream& input, Posicio& posicio)
{
    string posAux;
    input >> posAux;
    posicio.fromString(posAux);
    return input;
}

//Sobrecarrega de l'operador << per mostrar una Posicio
ostream& operator<<(ostream& output, Posicio& posicio)
{
    string posAux = posicio.toString();
    output << posAux;
    return output;
}
