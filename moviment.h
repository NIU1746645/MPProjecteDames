#ifndef MOVIMENT_H 
#define MOVIMENT_H

class Moviment
{
public:
    Moviment() {}
    Moviment(const Posicio& origen, const Posicio& desti) : m_origen(origen), m_desti(desti) {}

    Posicio getOrigen() const { return m_origen; }
    Posicio getDesti() const { return m_desti; }

private:
    Posicio m_origen;
    Posicio m_desti;
};

#endif // MOVIMENT_H
