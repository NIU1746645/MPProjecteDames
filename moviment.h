#ifndef MOVIMENT_H 
#define MOVIMENT_H

#include "posicio.h"

const int N_MOVIMENTS = 100

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

    Posicio m_movimentsValids [[]];
    Posicio m_movimentActual[];
    Posicio m_posicionValides [[]];
};

#endif // MOVIMENT_H

