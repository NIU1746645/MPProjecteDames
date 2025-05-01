#include "tauler.hpp"

//REVISIO
void Tauler::inicialitzaTauler(char tauler[N_FILES][N_COLUMNES])
{
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            tauler[i][j] = ' ';
			//Mirar si cal inicialitzar el valor de fitxes una per una
        }
    }
}

//REVISIO
void Tauler::llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
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
	else //COMPROVACIÓ D'OBERTURA DE FITXER
    {
        cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }

}

//FET
void Tauler::escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
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
	else //COMPROVACIÓ D'OBERTURA DE FITXER
    {
        cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }
}

//Assegurar de que funcioni be
void Tauler::inicialitza(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);

    if (fitxer.is_open())
    {
        while (!fitxer.eof())
        {
            char fitxa;
            string pos;
            Posicio posicio;
            fitxer >> fitxa;
            fitxer >> pos;
            //tractem dades
			posicio.fromString(pos);
			m_tauler[posicio.getFila()][posicio.getColumna()].fromChar(fitxa);
			m_tauler[posicio.getFila()][posicio.getColumna()] = fitxa;
        }
        fitxer.close();
    }
	else //COMPROVACIÓ D'OBERTURA DE FITXER
    {
		cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }
}

void Tauler::actualitzaMovimentsValids()
{
    //Implementar la lògica per actualitzar els moviments vàlids
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	//Comprovar si el moviment es valid

    /*bool mValid = false;
	m_tauler[origen.getColumna()][origen.getColumna()].setFitxa();
    return mValid;*/
    return false;
}

//FET crec
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    const Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];
	
    switch (fitxa.getTipus())
    {
    case TIPUS_NORMAL:
    {
        int direccio = (fitxa.getColor() == COLOR_NEGRE) ? 1 : -1;
        int fila = origen.getFila() + direccio;
        for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
        {
            int col = origen.getColumna() + deltaCol;
            if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
            {
                if (m_tauler[fila][col].esBuida() &&nPosicions < N_MOVIMENTS)
                {
                    posicionsPossibles[nPosicions++] = Posicio(fila, col);
                }
            }
        }
        break;
    }
    case TIPUS_DAMA:
    { 
        for (int deltaDir = -1; deltaDir <= 1; deltaDir += 2)
        {
            int direccio = deltaDir;
            for (int deltaFila = -1; deltaFila <= 1; deltaFila += 2)
            {
                int fila = origen.getFila() + direccio;
                for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
                {
                    int col = origen.getColumna() + deltaCol;
                    if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
                    {
                        if (m_tauler[fila][col].esBuida() && nPosicions < N_MOVIMENTS)
                        {
                            posicionsPossibles[nPosicions++] = Posicio(fila, col);
                        }
                    }
                }
            }
        }
        break;
	}
	default:
		break;
    }
}

//FET
string Tauler::toString() const
{
    return "";
}
