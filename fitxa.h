#ifndef FITXA_H
#define FITXA_H

#include "posicio.hpp"
#include "moviment.h"
#include <vector>

using namespace std;

typedef enum
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
    COLOR_NEGRE,
    COLOR_BLANC,
	SENSE_COLOR
} ColorFitxa;

class Fitxa
{
public:
    Fitxa() : m_tipus(TIPUS_EMPTY), m_color(SENSE_COLOR), m_nMovimentsValids(0){};
    Fitxa(TipusFitxa tipus, ColorFitxa color) : m_tipus(tipus), m_color(color) { m_nMovimentsValids = 0; };

    void setTipus(TipusFitxa tipus) { m_tipus = tipus; }
    void setColor(ColorFitxa color) { m_color = color; }
    void afegeixMovimentValid(const Moviment& mov);

    void buidaMoviments();

    TipusFitxa getTipus() const { return m_tipus; }
    ColorFitxa getColor() const { return m_color; }
	int getNMovimentsValids() const { return m_nMovimentsValids; }
    vector<Moviment> getMovimentsValids() const { return m_movimentsValids; }

    void promocioADama();

    char toChar() const;
    void fromChar(char c);

private:
    TipusFitxa m_tipus;                
    ColorFitxa m_color;                
    vector<Moviment> m_movimentsValids;
    int m_nMovimentsValids;
};

#endif
