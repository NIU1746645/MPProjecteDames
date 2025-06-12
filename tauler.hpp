#ifndef TAULER_H
#define TAULER_H

#include "fitxa.h"
#include "posicio.hpp"
#include "moviment.h"
#include <vector>
#include <string>

using namespace std;

const int MAX_SALTS = 10;
const int DIRECCIO_DAMES = 0;
const int FILA_BLANCA = 0;
const int FILA_NEGRA = 7;

class Tauler
{
public:
    Tauler();
    void inicialitza(const string& nomFitxer);
    void inicialitzaTauler(char tauler[N_FILES][N_COLUMNES]);
    void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
    void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

    string toString() const;
    bool dinsDimTauler(const Posicio& pos) const;
    bool esBuida(const Posicio& pos) const;
    ColorFitxa getColorContrari(ColorFitxa color) const;
    void afegirMoviment(Fitxa& fitxa, Moviment& mov, Posicio cami);
    void afegirMovimentAmbCaptura(Fitxa& fitxa, Moviment& mov, Posicio cami, Posicio captures);

    void movimentsNormals(Fitxa& fitxa, const Posicio& pos);
    void movimentsDama(Fitxa& fitxa, const Posicio& pos);
    void saltsMultiples(Fitxa& fitxa, Moviment& movimentActual, const Posicio& posActual, int direccio = 0);

    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);

    Fitxa getFitxa(int fila, int columna) const { return m_tauler[fila][columna]; }


private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];



};

#endif
