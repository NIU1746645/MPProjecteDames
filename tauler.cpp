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
    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
            m_tauler[i][j].fromChar(' ');
        }
    }

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

//falta arreglar els breaks i returns
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	bool valid = false;
    if (origen.getFila() < 0 || origen.getFila() >= N_FILES ||
        origen.getColumna() < 0 || origen.getColumna() >= N_COLUMNES ||
        desti.getFila() < 0 || desti.getFila() >= N_FILES ||
        desti.getColumna() < 0 || desti.getColumna() >= N_COLUMNES)
    {
        valid = false;
    }

    Fitxa& fitxaOrigen = m_tauler[origen.getFila()][origen.getColumna()];
    if (fitxaOrigen.esBuida())
    {
        valid = false;
    }

    // Comprovar si el moviment és vàlid
    int nPosicions;
    Posicio posicionsPossibles[N_MOVIMENTS];
    getPosicionsPossibles(origen, nPosicions, posicionsPossibles);

    bool movimentValid = false;
    for (int i = 0; i < nPosicions; i++)
    {
        if (posicionsPossibles[i] == desti)
        {
            movimentValid = true;
            break;
        }
    }
    if (!movimentValid) return false;

    // Realitzar el moviment
    Fitxa fitxa = fitxaOrigen;
    fitxaOrigen = Fitxa(); // Buida la posició d'origen

    // Comprovar si és una captura
    if (abs(desti.getFila() - origen.getFila()) > 1 || abs(desti.getColumna() - origen.getColumna()) > 1) {
        // És una captura, eliminar la fitxa saltada
        int filaCaptura = origen.getFila() + (desti.getFila() - origen.getFila()) / 2;
        int colCaptura = origen.getColumna() + (desti.getColumna() - origen.getColumna()) / 2;
        m_tauler[filaCaptura][colCaptura] = Fitxa();
    }

    // Comprovar promoció a dama
    if (fitxa.getTipus() == TIPUS_NORMAL)
    {
        if ((fitxa.getColor() == COLOR_NEGRE && desti.getFila() == N_FILES - 1) ||
            (fitxa.getColor() == COLOR_BLANC && desti.getFila() == 0)) {
            fitxa.setTipus(TIPUS_DAMA);
        }
    }

    m_tauler[desti.getFila()][desti.getColumna()] = fitxa;
    return true;

    return valid;
}

//funciona correctament pero s'ha de millorar (treure breaks...)
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) {
    nPosicions = 0;
    const Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];

    if (fitxa.esBuida()) return;

    bool hiHaCaptures = false;

    if (fitxa.getTipus() == TIPUS_NORMAL)
    {
        // Comprovem captures per fitxes normals
        int direccio = (fitxa.getColor() == COLOR_NEGRE) ? 1 : -1;
        
        int fila = origen.getFila();
		int col = origen.getColumna();
       /* do
        {*/
             for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
             {
                int filaIntermitja = fila + direccio;
                int colIntermitja = col + deltaCol;

                int filaDesti = fila + 2 * direccio;
                int colDesti = col + 2 * deltaCol;

                if (filaDesti >= 0 && filaDesti < N_FILES && colDesti >= 0 && colDesti < N_COLUMNES)
                {
                    if (!m_tauler[filaIntermitja][colIntermitja].esBuida() &&
                        m_tauler[filaIntermitja][colIntermitja].getColor() != fitxa.getColor() &&
                        m_tauler[filaDesti][colDesti].esBuida())
                    {
                        hiHaCaptures = true;
                        posicionsPossibles[nPosicions++] = Posicio(filaDesti, colDesti);
						//// Comprovem si hi ha més captures possibles
						//fila = filaDesti;
						//col = colDesti;
                    }
                    else
                    {
						hiHaCaptures = false;
                    }
                }
            }
		//} while (hiHaCaptures == true && nPosicions < N_MOVIMENTS); // Comprovem captures seguides
       
    }
    else
        if (fitxa.getTipus() == TIPUS_DAMA)
        {
            // Comprovem captures per dames 
            for (int deltaFila = -1; deltaFila <= 1; deltaFila += 2)
            {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
                {
                    int fila = origen.getFila() + deltaFila;
                    int col = origen.getColumna() + deltaCol;
                    bool trobadaFitxaContraria = false;

                    while (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
                    {
                        if (!m_tauler[fila][col].esBuida())
                        {
                            if (m_tauler[fila][col].getColor() == fitxa.getColor())
                            {
                                break; // Fitxa aliada, no podem saltar
                            }
                            else
                                if (trobadaFitxaContraria)
                                {
                                    break; // Ja hem trobat una fitxa contrària
                                }
                                else
                                {
                                    trobadaFitxaContraria = true;
                                    fila += deltaFila;
                                    col += deltaCol;
                                    continue;
                                }
                        }

                        if (trobadaFitxaContraria && m_tauler[fila][col].esBuida())
                        {
                            hiHaCaptures = true;
                            posicionsPossibles[nPosicions++] = Posicio(fila, col);
                        }

                        fila += deltaFila;
                        col += deltaCol;
                    }
                }
            }
        }

    // Mirem els moviments normals
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
    else
        if (fitxa.getTipus() == TIPUS_DAMA)
        {
            // Moviments normals de dames
            for (int deltaFila = -1; deltaFila <= 1; deltaFila += 2)
            {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
                {
                    int fila = origen.getFila() + deltaFila;
                    int col = origen.getColumna() + deltaCol;

                    while (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
                    {
                        if (!m_tauler[fila][col].esBuida())
                            break;

                        posicionsPossibles[nPosicions++] = Posicio(fila, col);
                        fila += deltaFila;
                        col += deltaCol;
                    }
                }
            }
        }
   
}

//FET
string Tauler::toString() const
{
    string m_taulerString;

    char num = 8;

    for (int i = 0; i < N_FILES; i++)
    {
        m_taulerString += to_string(num);
        m_taulerString += ':';
        m_taulerString += " ";
        num--;

        for (int j = 0; j < N_COLUMNES; j++)
        {

            char c = m_tauler[i][j].toChar();
            if (c == ' ')
                m_taulerString += "_";
            else
                m_taulerString += c;

            m_taulerString += " ";
        }

        m_taulerString += "\n";
    }
    m_taulerString += "  ";
    for (int i = 0; i < N_COLUMNES; i++)
    {
        m_taulerString += " ";
        m_taulerString += 'a' + i;
    }
    return m_taulerString;
}
