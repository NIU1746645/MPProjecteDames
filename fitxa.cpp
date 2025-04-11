#include "fitxa.h"

char Fitxa::toChar() const 
{
    char tornar = "";

    if (m_tipus == TIPUS_EMPTY)
        tornar = ' ';
    else 
        if (m_tipus == TIPUS_NORMAL)
        {
            if (m_color == COLOR_BLANC)
                tornar = 'B';
            else
                tornar = 'N';
        }
        else
        {
            if (m_color == COLOR_BLANC)
                tornar = 'D';
            else
                tornar = 'd';
        }
    
    return tornar;
}

void Fitxa::fromChar(char c) 
{
    if (c == ' ') 
    {
        m_tipus = TIPUS_EMPTY;
        m_color = COLOR_BLANC;
    }
    else
        if (c == 'B') 
        {
        m_tipus = TIPUS_NORMAL;
        m_color = COLOR_BLANC;
        }
        else 
            if (c == 'N') 
            {
                m_tipus = TIPUS_NORMAL;
                m_color = COLOR_NEGRE;
            }
            else 
                if (c == 'D') 
                {
                    m_tipus = TIPUS_DAMA;
                    m_color = COLOR_BLANC;
                }
                 else 
                    if (c == 'd') 
                    {
                        m_tipus = TIPUS_DAMA;
                        m_color = COLOR_NEGRE;
                    }
}
