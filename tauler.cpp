#include "tauler.h"	

void inicialitzaTauler(char tauler[N_FILES][N_COLUMNES])
{
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            tauler[i][j] = ' ';
        }
    }
}
void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
{
    inicialitzaTauler(tauler);
    ifstream fitxer;
    fitxer.open(nomFitxer);

    if (fitxer.is_open())
    {
        while (!fitxer.eof())
        {
            char tipusFitxa;
            Posicio posicio;
            fitxer >> tipusFitxa;
            fitxer >> posicio;
            //tractem dades
            tauler[posicio.getFila()][posicio.getColumna()] = tipusFitxa;
        }

        fitxer.close();
    }

}

void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
{
    ofstream fitxer;
    fitxer.open(nomFitxer);

    if (fitxer.is_open())
    {
        for (int i = 0; i < N_FILES; i++)
        {
            for (int j = 0; j < N_COLUMNES; j++)
            {
                if (tauler[i][j] != ' ')
                {
                    //obtenir dades a escriure
                    Posicio posicio(i, j);
                    /*posicio.setPosicio(i, j);*/

                    //escriure dades a fitxer
                    fitxer << tauler[i][j] << " ";
                    fitxer << posicio;
                    fitxer << endl;
                }
            }
        }

        fitxer.close();
    }
}

void inicialitza(const string& nomFitxer)
{

}

void actualitzaMovimentsValids()
{

}

bool mouFitxa(const Posicio& origen, const Posicio& desti)
{

}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    const Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];

    if (fitxa.getTipus() == TIPUS_NORMAL)
    {
        int direccio = (fitxa.getColor() == COLOR_NEGRE) ? 1 : -1;
        int fila = origen.getFila() + direccio;

        for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
        {
            int col = origen.getColumna() + deltaCol;
            if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
            {
                if (m_tauler[fila][col].esBuida())
                {
                    posicionsPossibles[nPosicions++] = Posicio(fila, col);
                }
            }
        }
    }
}

string toString() const
{

}