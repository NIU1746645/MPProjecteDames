#include "fitxa.h"

// Fem la promocio d'una fitxa normal a dama
void Fitxa::promocioADama()
{
    if (m_tipus == TIPUS_NORMAL)
    {
        m_tipus = TIPUS_DAMA;
    }
}

//Afegim un moviment valid a la fitxa
void Fitxa::afegeixMovimentValid(const Moviment& mov)
{
    if (mov.esValid())
    {
        m_movimentsValids.push_back(mov);
		m_nMovimentsValids++;
    }
}

//Neteja tots els moviments
void Fitxa::buidaMoviments() 
{ 
    m_movimentsValids.clear(); 
    m_nMovimentsValids = 0; 
}

//Per passar del codi a caracters per fer el tauler
char Fitxa::toChar() const
{
    char tornar = ' ';

    switch (m_tipus)
    {
    case TIPUS_EMPTY:
        tornar = ' ';
        break;

    case TIPUS_NORMAL:
        if (m_color == COLOR_BLANC)
            tornar = 'O'; //color blanc
        else
            tornar = 'X'; //color negre
        break;

    case TIPUS_DAMA:
        if (m_color == COLOR_BLANC)
            tornar = 'D'; //dama blanca
        else
            tornar = 'R'; //dama negra
        break;
    }

    return tornar;
}

//Per pasar els caracters del tauler a codi
void Fitxa::fromChar(char c)
{
    switch (c)
    {
    case ' ':
        m_tipus = TIPUS_EMPTY;
        m_color = COLOR_BLANC;
        break;

    case 'O':
        m_tipus = TIPUS_NORMAL;
        m_color = COLOR_BLANC;
        break;

    case 'X':
        m_tipus = TIPUS_NORMAL;
        m_color = COLOR_NEGRE;
        break;

    case 'D':
        m_tipus = TIPUS_DAMA;
        m_color = COLOR_BLANC;
        break;

    case 'R':
        m_tipus = TIPUS_DAMA;
        m_color = COLOR_NEGRE;
        break;

    default:
        m_tipus = TIPUS_EMPTY;
        m_color = COLOR_BLANC;
        break;
    }
}
