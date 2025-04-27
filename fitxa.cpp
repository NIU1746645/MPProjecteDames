#include "fitxa.h"

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
            tornar = 'B';
        else
            tornar = 'N';
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

void Fitxa::fromChar(char c)
{
    switch (c)
    {

    case ' ':
        m_tipus = TIPUS_EMPTY;
        m_color = COLOR_BLANC;
        break;

    case 'B':
        m_tipus = TIPUS_NORMAL;
        m_color = COLOR_BLANC;
        break;

    case 'N':
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
