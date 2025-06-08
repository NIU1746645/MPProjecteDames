#include "tauler.hpp"
#include <fstream>
#include <sstream>

//Inicialitza totes les caselles com a buides
Tauler::Tauler()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            m_tauler[i][j] = Fitxa();
        }
    }
}

//Inicialitza totes les caselles com a buides d'un tauler passat com a parametres
void Tauler::inicialitzaTauler(char tauler[N_FILES][N_COLUMNES])
{
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            tauler[i][j] = ' ';
        }
    }
}

//Llegeix un tauler des d'un fitxer i ompla els valors del tauler passat com a parametre
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
            //Tractem dades
            tauler[posicio.getFila()][posicio.getColumna()] = tipusFitxa;

        }

        fitxer.close();
    }
    else //Comprovacio d'obertura de fitxer
    {
        cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }
}

//Escriu un tauler a un fitxer passat com a parametre
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
                    //Obtenir dades a escriure
                    Posicio posicio(i, j);
                    /*posicio.setPosicio(i, j);*/

                    //Escriure dades a fitxer
                    fitxer << tauler[i][j] << " ";
                    fitxer << posicio;
                    fitxer << endl;
                }
            }
        }
        fitxer.close();
    }
    else //Comprovacio d'obertura de fitxer
    {
        cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }
}

//Inicialitza el tauler a partir d'un fitxer
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
            //Tractem dades

            posicio.fromString(pos);
            m_tauler[posicio.getFila()][posicio.getColumna()].fromChar(fitxa);
        }
        fitxer.close();
    }
    else //Comprovacio d'obertura de fitxer
    {
        cout << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
        return;
    }
}

//Converteix el tauler a un string
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

//Retorna true si esta dins del tauler, i false en cas contrari
bool Tauler::dinsDimTauler(const Posicio& pos) const
{
    bool dins = false;

    int fila = pos.getFila();
    int columna = pos.getColumna();

    if(fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES)
        dins = true;

    return dins;
}

//Retorna si una casella esta buida
bool Tauler::esBuida(const Posicio& pos) const
{
    return (m_tauler[pos.getFila()][pos.getColumna()].getTipus() == TIPUS_EMPTY);
}

//Retorna el color contrari al especificat
ColorFitxa Tauler::getColorContrari(ColorFitxa color) const
{
    ColorFitxa c;

    if (color == COLOR_BLANC)
        c = COLOR_NEGRE;
    else
        c = COLOR_BLANC;
    return c;
}

//Omple tots els arrays i variables de control en fer un nou moviment
void Tauler::afegirMoviment(Fitxa& fitxa, Moviment& mov, Posicio cami)
{
    mov.afegirCami(cami);
    fitxa.afegeixMovimentValid(mov);
}

//Omple tots els arrays i variables de control en fer un nou moviment amb captura
void Tauler::afegirMovimentAmbCaptura(Fitxa& fitxa, Moviment& mov, Posicio cami, Posicio captures)
{
    mov.afegirCami(cami);
    mov.afegirCaptures(captures);
    fitxa.afegeixMovimentValid(mov);
}

//Calula quins son els moviments valids d'una fitxa normal
void Tauler::movimentsNormals(Fitxa& fitxa, const Posicio& pos)
{
    int direccio = (fitxa.getColor() == COLOR_BLANC) ? -1 : 1; // Direcció del moviment: -1 per blanc (amunt), +1 per negre (avall)
    Posicio desti;

    //Cas sense captures
    for (int i = -1; i <= 1 ; i = i + 2) //Comprova les diagonals dreta i esquerra
    {
        desti = Posicio(pos.getFila() + direccio, pos.getColumna() + i);

        if (dinsDimTauler(desti) && esBuida(desti))
        {
            Moviment mov;
            afegirMoviment(fitxa, mov, desti);//Afegim moviment normal
        }
    }

    //Cas amb captures
    for (int i = -1; i <= 1; i = i + 2)
    {
        Posicio inici(pos.getFila() + direccio, pos.getColumna() + i);
        desti = Posicio(pos.getFila() + 2 * direccio, pos.getColumna() + 2 * i);

        if (dinsDimTauler(inici) && dinsDimTauler(desti))
        {
            Fitxa fitxaSalt = m_tauler[inici.getFila()][inici.getColumna()];
            if (fitxaSalt.getColor() == getColorContrari(fitxa.getColor()) && esBuida(desti))
            {
                Moviment mov;
                afegirMovimentAmbCaptura(fitxa, mov, desti, inici); //Afegim el moviment amb captura
                saltsMultiples(fitxa, mov, desti, direccio); //Mira si pot fer mes salts
            }
        }
    }
}

//Comprova si hi han mes salts a fer despres d'una captura
void Tauler::saltsMultiples(Fitxa& fitxa, Moviment& movimentActual, const Posicio& posActual, int direccio)
{
    static int nSalts = 0; //Com que es crida a ella mateixa em de mantenir un compte de maxim numero de salts per no fer un bucle infinit
    if (nSalts > 10) return;
    nSalts++;

    ColorFitxa colorContrari = getColorContrari(fitxa.getColor());
    vector<int> dir1;
    vector<int> dir2;


    if (direccio != 0) //Vol dir que es mou nomes en una direcció (normal)
    {
        dir1 = { direccio, direccio };
        dir2 = { -1, 1 };
    }
    else //Vol dir que es mou en totes direccions (dama)
    {
        dir1 = { -1, -1, 1, 1 };
        dir2 = { -1, 1, -1, 1 };
    }

    for (int i = 0; i < dir1.size(); i++)  //Mira totes les direccions possibles (que son les passades en els vectors)
    {
        int deltaFila = dir1[i];
        int deltaColumna = dir2[i];

        Posicio inici(posActual.getFila() + deltaFila, posActual.getColumna() + deltaColumna);
        Posicio desti(inici.getFila() + deltaFila, inici.getColumna() + deltaColumna);

        if (dinsDimTauler(inici) && dinsDimTauler(desti) && esBuida(desti))
        {
            Fitxa fitxaSalt = m_tauler[inici.getFila()][inici.getColumna()];

            if (fitxaSalt.getColor() == colorContrari) //Si es del color contrari la mata, comptabilitza la captura i afegeix el nou moviment
            {
                Moviment nouMoviment = movimentActual;
                afegirMovimentAmbCaptura(fitxa, nouMoviment, desti, inici);
                saltsMultiples(fitxa, nouMoviment, desti, direccio); //Continua buscant si pot fer mes salts
            }
        }
    }
    nSalts--;
}

//Calcula quins son els moviments valids d'una fitxa dama
void Tauler::movimentsDama(Fitxa& fitxa, const Posicio& pos)
{
    //Amb el doble for comprovem primer les dues direccions (esquerra i dreta) i despres (amunt i avall)
    for (int i = -1; i <= 1; i = i + 2)
    {
        for (int j = -1; j <= 1; j = j + 2)
        {
            bool fContraria = false;
            Posicio actual = pos;
            bool movimentValid = true;

            while (movimentValid)
            {
                actual = Posicio(actual.getFila() + i, actual.getColumna() + j);
                movimentValid = dinsDimTauler(actual);

                if (movimentValid)
                {
                    if (esBuida(actual)) //Si esta buida avançem normal
                    {
                        if (!fContraria)
                        {
                            Moviment mov;
                            afegirMoviment(fitxa, mov, actual);
                        }
                    }
                    else //Si esta ocupada doncs, o haurem de capturar(color contrari) o no podrem avançar cap a aquell costat(mateix color)
                    {
                        if (m_tauler[actual.getFila()][actual.getColumna()].getColor() == fitxa.getColor())
                        {
                            movimentValid = false;
                        }

                        if (!fContraria)
                        {
                            fContraria = true;
                            Posicio captura = actual;
                            Posicio possibleDesti(captura.getFila() + i, captura.getColumna() + j);

                            if (dinsDimTauler(possibleDesti) && esBuida(possibleDesti))
                            {
                                Moviment mov;
                                afegirMovimentAmbCaptura(fitxa, mov, possibleDesti, captura);
                                saltsMultiples(fitxa, mov, possibleDesti, DIRECCIO_DAMES);
                            }
                            movimentValid = false; // Atura el moviment després de la captura
                        }
                    }
                }

                
            }
        }
    }
}

//Actualitza nomes els moviemnts que son valids
void Tauler::actualitzaMovimentsValids()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Fitxa& fitxa = m_tauler[i][j];
            fitxa.buidaMoviments();

            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                 Posicio pos(i, j);
                if (fitxa.getTipus() == TIPUS_NORMAL)
                {
                    movimentsNormals(fitxa, pos);
                }
                else
                {
                    movimentsDama(fitxa, pos);
                }
            }
        }
    }
}

//Mou la fitxa si el moviment es valid
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    Fitxa& fitxa = m_tauler[origen.getFila()][origen.getColumna()];

    bool mValid = false;
    bool trobat = false;
    bool fi = false;
    Moviment unMov;

    ColorFitxa jugador = fitxa.getColor();
    bool hiHaCapturesTotes = false;
	vector<Posicio> FIC; //Son les fitxes que tenen una o mes captures possibles (Fitxes I Captures)

    for (int i = 0; i < N_FILES; ++i)
    {
        for (int j = 0; j < N_COLUMNES; ++j)
        {
            Fitxa fitxa = m_tauler[i][j];
            if (fitxa.getColor() == jugador && fitxa.getTipus() != TIPUS_EMPTY)
            {
                Moviment mov;

                for (int k = 0; k < fitxa.getNMovimentsValids(); k++)
                {
                    mov = fitxa.getMovimentsValids()[k];

                    if (!mov.getCaptures().empty())
                    {
                        FIC.push_back(Posicio(i, j));
                        hiHaCapturesTotes = true;
						break; 
                    }
                }
            }
        }
    }

    Moviment mov;

    for (int i = 0; i < fitxa.getNMovimentsValids(); i++)
    {
        mov = fitxa.getMovimentsValids()[i];
        if (!trobat && mov.getCami().back() == desti)
        {
            unMov = mov;
            mValid = true;
            trobat = true;
        }
    }

    if (mValid)
    {
        m_tauler[desti.getFila()][desti.getColumna()] = fitxa;
        m_tauler[origen.getFila()][origen.getColumna()] = Fitxa();

        Posicio cap;
		int nCaptures = unMov.getCaptures().size();

        for (int c = 0; c < nCaptures; c++)
        {
			cap = unMov.getCaptures()[c];
            m_tauler[cap.getFila()][cap.getColumna()] = Fitxa();
        }

        Fitxa& fDesti = m_tauler[desti.getFila()][desti.getColumna()];
        bool fitxaB = (fDesti.getColor() == COLOR_BLANC && desti.getFila() == FILA_BLANCA);
        bool fitxaN = (fDesti.getColor() == COLOR_NEGRE && desti.getFila() == FILA_NEGRA);
        if (fitxaB || fitxaN)
        {
            fDesti.promocioADama();
        }

        if (hiHaCapturesTotes && unMov.getCaptures().empty())
        {
            Posicio pos;
			int nFIC = FIC.size();

            for (int l = 0; l < nFIC; l++)
            {
                pos = FIC[l];
                m_tauler[pos.getFila()][pos.getColumna()] = Fitxa();
            }
        }

        actualitzaMovimentsValids();

        ColorFitxa color = fDesti.getColor();
        vector<Posicio> bufar;

        bool capturesFitxa = false;
        for (const Moviment& m : fDesti.getMovimentsValids())
        {
            if (!m.getCaptures().empty())
            {
                capturesFitxa = true;
                break;
            }
        }

        if (capturesFitxa)
        {
            bufar.push_back(desti);
        }

        Posicio pos;
		int nBufar = bufar.size();

        for (int b = 0; b < nBufar; b++)
        {
            pos = bufar[b];
            m_tauler[pos.getFila()][pos.getColumna()] = Fitxa();
        }
        actualitzaMovimentsValids();
    }
    return mValid;
}

//Calcula posicions possibles d'una fitxa
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    Fitxa fitxa = m_tauler[origen.getFila()][origen.getColumna()];
    vector<Moviment> moviments = fitxa.getMovimentsValids();
	int nMoviments = fitxa.getNMovimentsValids();

    Moviment mov;
    for (int i = 0; i < nMoviments; i++)
    {
        mov = moviments[i];

        if (!mov.getCami().empty())
        {
            Posicio desti = mov.getCami().back();
            bool repetit = false;

            for (int i = 0; i < nPosicions; i++)
            {
                if (posicionsPossibles[i] == desti)
                {
                    repetit = true;
                    break;
                }
            }

            if (!repetit)
            {
                posicionsPossibles[nPosicions++] = desti;
            }
        }
    }
}

