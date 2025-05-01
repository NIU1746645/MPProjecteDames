#ifndef MOVIMENT_H 
#define MOVIMENT_H

#include "posicio.hpp"

const int N_MOVIMENTS = 100;

typedef enum
{
	MOV_EMPTY, //Per defecte i s'enten que no pot fer cap moviment
    MOV_AVANÇA, //No se si avança portara problemes i seria millor avanca
	MOV_MATA, //
} TipusMoviment;

class Moviment
{
public:
    Moviment() : m_FitxesMata(MOV_EMPTY) {}
    Moviment(const Posicio& origen, const Posicio& desti) : m_origen(origen), m_desti(desti), m_FitxesMata(MOV_EMPTY) {}

    Posicio getOrigen() const { return m_origen; }
    Posicio getDesti() const { return m_desti; }

    bool esValid() const;
    void reinicia();
    void mostra() const;
    void afegirMoviment(const Posicio& moviment);
	void afegirCaptura(const Posicio& captura);
	void setTipusMoviment(int index, TipusMoviment tipus);
	TipusMoviment getTipusMoviment(int index) const;
	Posicio getMoviment(int index) const;
	Posicio getCaptura(int index) const;

    int getNumMoviments() const { return m_numMoviments; }
    int getNumaptures() const { return m_numCaptures; }

private:
    int m_numMoviments;
    int m_numCaptures;

    Posicio m_origen;
    Posicio m_desti;

    Posicio m_movimentsValids[N_MOVIMENTS];
    Posicio m_movimentActual[N_MOVIMENTS];
    TipusMoviment m_tipusMoviment[N_MOVIMENTS]; //Si mata o avança
    int m_FitxesMata;
    //Saber quin tipus de fitxa mata
    Posicio m_posicionValides[N_MOVIMENTS];
    Posicio m_captures[N_MOVIMENTS];
};

#endif // MOVIMENT_H

