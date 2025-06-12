#ifndef POSICIO_H
#define POSICIO_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Posicio
{
public:
    Posicio() : m_fila(-1), m_columna(-1) {}
    Posicio(int fila, int columna) { m_fila = fila; m_columna = columna; };
    Posicio(const string& pos);

    int getFila() const { return m_fila; };
    int getColumna() const { return m_columna; };

    bool operator==(const Posicio& other) const;

    string toString() const;
    void fromString(const string& pos);

private:
    int m_fila;
    int m_columna;
};
istream& operator>>(istream& input, Posicio& posicio);
ostream& operator<<(ostream& output, Posicio& posicio);
#endif
