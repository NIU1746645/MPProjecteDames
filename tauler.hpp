#ifndef TAULER_HPP
#define TAULER_HPP

#include "posicio.hpp"
#include "fitxa.h"

class Tauler
{
public:
	void inicialitzaTauler(char tauler[N_FILES][N_COLUMNES]);
	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
	void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;
	bool cercaPosicio(Posicio posicio[], Posicio novaPos);

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif // TAULER_HPP
