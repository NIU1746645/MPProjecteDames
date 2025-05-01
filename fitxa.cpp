#include "fitxa.h"

//FET
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
            tornar = 'O';
        else
            tornar = 'X';
        break;

    case TIPUS_DAMA:
        if (m_color == COLOR_BLANC)
            tornar = 'D';
        else
            tornar = 'R';
        break;
    }

    return tornar;
}

//FET
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
