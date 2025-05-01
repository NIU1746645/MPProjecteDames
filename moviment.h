#ifndef MOVIMENT_H 
#define MOVIMENT_H

#include "posicio.hpp"

const int N_MOVIMENTS = 100;

typedef enum
{
    MOV_AVANÇA,
    MOV_MATA,
} TipusMoviment;

class Moviment
{
public:
    Moviment(): m_FitxesMata(0) {}
    Moviment(const Posicio& origen, const Posicio& desti) : m_origen(origen), m_desti(desti), m_FitxesMata(0) {}

    Posicio getOrigen() const { return m_origen; }
    Posicio getDesti() const { return m_desti; }

private:
    Posicio m_origen;
    Posicio m_desti;
	Posicio m_moviment[N_MOVIMENTS];
	TipusMoviment m_tipusMoviment[N_MOVIMENTS]; //Si mata o avança
    int m_FitxesMata;
	//Saber quin tipus de fitxa mata
};

#endif // MOVIMENT_H

