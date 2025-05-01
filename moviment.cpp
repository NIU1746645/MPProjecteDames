#include "moviment.h"
#include <iostream>

using namespace std;

bool Moviment::esValid() const
{
    bool valid = false;
    if (m_numMoviments > 0)
    {
        valid = true;
    }
    return valid;
}

void Moviment::reinicia()
{
    m_numMoviments = 0;
    m_numCaptures = 0;
    m_FitxesMata = 0;
}

void Moviment::mostra() const
{
    cout << "Moviment des de ";
    m_origen.mostra();
    cout << " fins a ";
    m_desti.mostra();
    cout << endl;

    if (m_numMoviments > 0)
    {
        cout << "Posicions intermèdies: ";
        for (int i = 0; i < m_numMoviments; ++i)
        {
            m_movimentsValids[i].mostra();
            if (i < m_numMoviments - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    if (m_numCaptures > 0)
    {
        cout << "Captures (" << m_numCaptures << "): ";
        for (int i = 0; i < m_numCaptures; ++i)
        {
            m_captures[i].mostra();
            if (i < m_numCaptures - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void Moviment::afegirMoviment(const Posicio& moviment)
{
    bool espaiDisponible = (m_numMoviments < N_MOVIMENTS);
    if (espaiDisponible)
    {
        m_movimentsValids[m_numMoviments] = moviment;
        m_numMoviments++;
    }
}

void Moviment::afegirCaptura(const Posicio& captura)
{
    bool espaiDisponible = (m_numCaptures < N_MOVIMENTS);
    if (espaiDisponible)
    {
        m_captures[m_numCaptures] = captura;
        m_numCaptures++;
        m_FitxesMata++;
    }
}

void Moviment::setTipusMoviment(int index, TipusMoviment tipus)
{
    bool indexValid = (index >= 0 && index < N_MOVIMENTS);
    if (indexValid)
    {
        m_tipusMoviment[index] = tipus;
    }
}

TipusMoviment Moviment::getTipusMoviment(int index) const
{
    TipusMoviment tipus = MOV_EMPTY; //Abans hi havia mov_avança
    bool indexValid = (index >= 0 && index < N_MOVIMENTS);
    if (indexValid)
    {
        tipus = m_tipusMoviment[index];
    }
    return tipus;
}

Posicio Moviment::getMoviment(int index) const
{
    Posicio posicio;
    bool indexValid = (index >= 0 && index < m_numMoviments);
    if (indexValid)
    {
        posicio = m_movimentsValids[index];
    }
    return posicio;
}

Posicio Moviment::getCaptura(int index) const
{
    Posicio posicio;
    bool indexValid = (index >= 0 && index < m_numCaptures);
    if (indexValid)
    {
        posicio = m_captures[index];
    }
    return posicio;
}

