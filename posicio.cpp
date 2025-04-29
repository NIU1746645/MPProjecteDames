#include "posicio.hpp"

string Posicio::toString() const
{
    string posicio = "a1";
    posicio[0] = 'a' + m_columna;
    posicio[1] = '1' + (N_FILES - 1) - m_fila;
    return posicio;
}

void Posicio::fromString(const string& pos)
{
    m_fila = (N_FILES - 1) - (pos[1] - '1');
    m_columna = pos[0] - 'a';
}

bool Posicio::operator==(const Posicio& posicio) const 
{
    return m_fila == posicio.m_fila && m_columna == posicio.m_columna;
}

istream& operator>>(istream& input, Posicio& posicio)
{
    string posAux;
    input >> posAux;
    posicio.fromString(posAux);
    return input;
}

ostream& operator<<(ostream& output, Posicio& posicio)
{
    string posAux = posicio.toString();
    output << posAux;
    return output;
}
