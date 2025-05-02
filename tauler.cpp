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
    else //COMPROVACIO D'OBERTURA DE FITXER
    {
        cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }
}

void Tauler::actualitzaMovimentsValids()
{
    //Implementar la logica per actualitzar els moviments valids
}

//falta arreglar els breaks i returns
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    
    bool movimentValid = true;
    Fitxa& fitxaOrigen = m_tauler[origen.getFila()][origen.getColumna()];
    
    if (origen.getFila() < 0 || origen.getFila() >= N_FILES ||
        origen.getColumna() < 0 || origen.getColumna() >= N_COLUMNES ||
        desti.getFila() < 0 || desti.getFila() >= N_FILES ||
        desti.getColumna() < 0 || desti.getColumna() >= N_COLUMNES)
    {
        movimentValid = false;
    }
    else if (fitxaOrigen.esBuida())
    {
        movimentValid = false;
    }
    else
    {
        // Comprovar si el moviment es valid
        int nPosicions;
        Posicio posicionsPossibles[N_MOVIMENTS];
        getPosicionsPossibles(origen, nPosicions, posicionsPossibles);

        int i = 0;
        bool trobat = false;
        while (i <= nPosicions && !trobat)
        {
            if (posicionsPossibles[i] == desti)
            {
                trobat = true;
            }
            i++;
        }
        if (!trobat) // Si no hem trobat la posicio de desti entre les possibles
        {
		    movimentValid = false;
        }
    }

    if (movimentValid)
    {
        // Realitzar el moviment
        Fitxa fitxa = fitxaOrigen;
        fitxaOrigen = Fitxa(); // Buida la posicio d'origen

        // Gestio de captures
        int deltaFila = desti.getFila() - origen.getFila();
        int deltaCol = desti.getColumna() - origen.getColumna();
        int steps = max(abs(deltaFila), abs(deltaCol));

		if (steps > 1) { // Es una captura o no depenent si es dama o normal
            /*if (fitxaOrigen.getTipus() == TIPUS_NORMAL)
            {*/
                int dirFila = deltaFila > 0 ? 1 : -1;
                int dirCol = deltaCol > 0 ? 1 : -1;

                for (int i = 1; i < steps; i++)
                {
                    int fila = origen.getFila() + i * dirFila;
                    int col = origen.getColumna() + i * dirCol;
                    if (!m_tauler[fila][col].esBuida())
                    {
                        m_tauler[fila][col] = Fitxa(); // Elimina la fitxa capturada
                    }
                }
            /*}*/
            
        }

        // Comprovar promocio a dama
        if (fitxa.getTipus() == TIPUS_NORMAL)
        {
            if ((fitxa.getColor() == COLOR_NEGRE && desti.getFila() == N_FILES - 1) ||
                (fitxa.getColor() == COLOR_BLANC && desti.getFila() == 0))
            {
                fitxa.setTipus(TIPUS_DAMA);
            }
        }

        m_tauler[desti.getFila()][desti.getColumna()] = fitxa;
        movimentValid = true;
    
    }
	return movimentValid;
}

//funciona correctament pero s'ha de millorar
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    const Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];
	/*cout << "Posicio origen: " << origen.getFila() << origen.getColumna() << endl;*/
    bool pendents = false;
    Posicio mPendents[N_MOVIMENTS];
    int nPendents = 0;
	Posicio pPossibles[N_MOVIMENTS];
	int nPossibles = 0;

    if (!fitxa.esBuida())
    {
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

						bool fitxaTrobada = false;
                        while (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES && !fitxaTrobada)
                        {
                            if (m_tauler[fila][col].esBuida())
                            {                                
                                posicionsPossibles[nPosicions++] = Posicio(fila, col);
                                fila += deltaFila;
                                col += deltaCol;
                            }
                            else
                                fitxaTrobada = true;
                        }

						pPossibles[nPossibles++] = Posicio(fila - deltaFila, col - deltaCol); //Nomes pot tenir 4 posicions possibles abans
                        //Abans no hagi de saltar o menjar alguna fitxa. Llavors, en aquest array, recopilem les opcions 
                        //de pre possible menjar, pero clar, hauriem de saber cap a quina direccio anira perque no haurem de valorar totes les idreccions, sino una
                        // Llavors la fitxa hauria de ser x amb una unica possible opcio de sat si es -1 -1, o -1 1o etc. 
                        //Es a dir, deixarem les fitxes ja avançades, i nomes haurem de mirar si el salt que han de fer cap
                        // a una unica possibles diagonales pot fer o no
                        // si es pot fer, doncs ha de seguir menjant, i sino doncs no.
                    }
                }
            }
        
        if (fitxa.getTipus() == TIPUS_NORMAL)
        {
            // Comprovem captures per fitxes normals
            int direccio = (fitxa.getColor() == COLOR_NEGRE) ? 1 : -1;

            int fila = origen.getFila();
            int col = origen.getColumna();
            do
            {
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
                            if (!cercaPosicio(posicionsPossibles, Posicio(filaDesti, colDesti)))
							{
								// Afegim la posicio de desti a les possibles captures
								posicionsPossibles[nPosicions++] = Posicio(filaDesti, colDesti);
                                mPendents[nPendents++] = Posicio(filaDesti, colDesti);
                            }
							
                        }
                    }
                }

				if (nPendents > 0)
				{
                    nPendents--;
					fila = mPendents[nPendents].getFila();
					col = mPendents[nPendents].getColumna();
                    pendents = true;
				}
                else
                {
                    pendents = false;
                }
            } while (pendents == true && nPosicions < N_MOVIMENTS); // Comprovem captures seguides

        }
        else
            if (fitxa.getTipus() == TIPUS_DAMA)
            {
                int fila = origen.getFila();
                int col = origen.getColumna();
                
				bool primeraVolta = true; // Variable per controlar si es la primera volta del bucle
                nPossibles = 0; // Reiniciem el contador de possibles captures
                // Comprovem captures per dames 
                do
                {   
                    for (int deltaFila = -1; deltaFila <= 1; deltaFila += 2)
                    {
                        for (int deltaCol = -1; deltaCol <= 1; deltaCol += 2)
                        {
                            if (nPossibles < 4)
                            {
                                fila = pPossibles[nPossibles].getFila();
                                col = pPossibles[nPossibles++].getColumna();
                            }
                            
                            if (fila != -1 && col != -1)
                            {


                                int filaIntermitja = fila + deltaFila; //per aqui hauriem de posar fila[nfila++] per controlar la casella en cada cas i direccio
                                int colIntermitja = col + deltaCol; //de la mateixa manera fariem amb col, pero per aixo hauriem de ferho amb
                                //una variable xterna o amb gettters i setters de la posicio que haurem colocat al array de les 4 possicions avancads en el tauler i preparades per menjar o no

                                int filaDesti = fila + 2 * deltaFila;
                                int colDesti = col + 2 * deltaCol;


                                bool pendents2 = true;/*
                                bool menjant = false;*/
                                while (filaDesti >= 0 && filaDesti < N_FILES && colDesti >= 0 && colDesti < N_COLUMNES && pendents2)
                                {
                                    if (!m_tauler[filaIntermitja][colIntermitja].esBuida() &&
                                        m_tauler[filaIntermitja][colIntermitja].getColor() != fitxa.getColor() &&
                                        m_tauler[filaDesti][colDesti].esBuida())
                                    {/*
                                        menjant = true;*/
                                        if (!cercaPosicio(posicionsPossibles, Posicio(filaDesti, colDesti)))
                                        {
                                            // Afegim la posicio de desti a les possibles captures
                                            posicionsPossibles[nPosicions++] = Posicio(filaDesti, colDesti);
                                            mPendents[nPendents++] = Posicio(filaDesti, colDesti);
                                        }
                                        else
                                            pendents2 = false;
                                    }
                                    else
                                        pendents2 = false;
                                }
                            }
                            else
							{
								// Si la posicio es -1, vol dir que no hi ha mes captures possibles en aquesta direccio
							}
                        }
                    }
                    if (nPendents > 0)
                    {
                        fila = mPendents[--nPendents].getFila();
                        col = mPendents[nPendents].getColumna();
                        pendents = true;
                    }
                    else
                    {
                        pendents = false;
                    }

                } while (pendents == true && nPosicions < N_MOVIMENTS && nPosicions < 4); // Comprovem captures seguides
                
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

bool Tauler::cercaPosicio(Posicio posicio[], Posicio novaPos)
{
    bool trobat = false;
    int i = 0;

    while (!trobat && i < N_MOVIMENTS)
    {
        if (posicio[i] == novaPos)
        {
            trobat = true;
        }
        i++;
    }
    return trobat;
}
