#ifndef POSICIO_H
#define POSICIO_H

#include <string>
#include <fstream>
using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Posicio
{
public:
    Posicio() : m_fila(-1), m_columna(-1) {};
    Posicio(int fila, int columna) { m_fila = fila; m_columna = columna; };
    int getFila() const { return m_fila; };
    int getColumna() const { return m_columna; };
    void setPosicio(int fila, int columna) { m_fila = fila; m_columna = columna; };
    string toString() const;
    void fromString(const string& pos);

    Posicio(const string& posicio) { fromString(posicio); }

    bool operator==(const Posicio& posicio) const;


private:
    int m_fila, m_columna;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);
ofstream& operator<<(ofstream& fitxer, const Posicio& posicio);

#endif // POSICIO_H

