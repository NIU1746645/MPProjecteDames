#ifndef TAULER_H
#define TAULER_H

#include "posicio.h"

class Tauler
{
public:
	void inicialitzaTauler(char tauler[N_FILES][N_COLUMNES]);
	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
	void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

	
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(cont Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];

};


#endif // TAULER_H
