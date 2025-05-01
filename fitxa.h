#ifndef FITXA_H
#define FITXA_H

#include "posicio.hpp"
#include "moviment.h"

typedef enum
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
    COLOR_NEGRE,
    COLOR_BLANC
} ColorFitxa;

class Fitxa
{
public:
    Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BLANC) {};
    Fitxa(TipusFitxa tipus, ColorFitxa color) : m_tipus(tipus), m_color(color) {};

    void setTipus(TipusFitxa tipus) { m_tipus = tipus; }
    void setColor(ColorFitxa color) { m_color = color; } 
    TipusFitxa getTipus() const { return m_tipus; } 
    ColorFitxa getColor() const { return m_color; }
	
    bool esBuida() const { return m_tipus == TIPUS_EMPTY; }
    char toChar() const;
    void fromChar(char c);

    void inicialitzaMovimentsValids(const Moviment& pos);
    void inicialitzaMovimentsPendents(const Moviment& pos);
    void inicialitzaMovimentActual(const Moviment& pos);
    void recuperaPosicionsValides(const Moviment& pos);

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Moviment m_movimentsValids[N_MOVIMENTS];
    Moviment m_movimentsPendents[N_MOVIMENTS];
    Moviment m_movimentActual[N_MOVIMENTS];
    Moviment m_posicionsValides[N_MOVIMENTS];
};

#endif // FITXA_H
