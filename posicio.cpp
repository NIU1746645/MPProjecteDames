#include "posicio.hpp"

/*
Hem de convertir "a1" , "h6" en fila i columna.
exemple: 
  "a1" -> columna = 'a' - 'a' = 0 i fila = (8-1) - (1-1) = 7
*/

string Posicio::toString() const
{
    string posicio = "a1";
    posicio[0] = 'a' + m_columna;
    posicio[1] = '1' + (N_FILES - 1) - m_fila;
    return posicio;
}

//implementacio del exemple de dalt
void Posicio::fromString(const string& pos)
{
    m_fila = (N_FILES - 1) - (pos[1] - '1');
    m_columna = pos[0] - 'a';

	//Comprovar si la posicio es valida
    if (m_fila < 0 || m_fila >= N_FILES || m_columna < 0 || m_columna >= N_COLUMNES)
    {
        m_fila = -1;
        m_columna = -1;
    }
}

//comparem posicions
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
