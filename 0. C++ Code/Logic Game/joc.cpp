/*
//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"



bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) 
{
	//TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
	// 	      Dibuixar a pantalla el fons i el gràfic amb el tauler buit.
	//------------------------------------------------------------------

	//TODO 1.1 Afegir l'include de GraphicManager --> #include "GraphicManager.h"
	//TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY);
	//	    Per començar podem cridar el drawSprite amb els params --> 
	//          (GRAFIC_FONS,0,0) i 
	//          (GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER)

 


	//TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i una fitxa blanca a la posició (fila, columna ) del tauler


	//TODO 2: Interactuar amb el ratolí.
	//------------------------------------------------------------------
	//TODO 2.1: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí



    //TODO 2.2: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
    // està dins del límits del tauler

 

    //TODO 2.3: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
    // està dins del límits del tauler. Dibuixa la fitxa a la casella on està el ratolí



    //TODO 2.4: Dibuixar la fitxa blanca a la casella on cliquem al ratolí. La fitxa s'ha de mantenir dibuixada
    // a la casella quan deixem de clicar amb el ratolí. Quan cliquem a una altra casella, la fitxa canvia de posició
    // a la nova casella

        
        
    // TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Mostrar la posició actual del ratolí a sota del tauler

	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);


	for (int fila = 0; fila < NUM_FILES_TAULER; fila++)
	{
		for (int columna = 0; columna < NUM_COLS_TAULER; columna++)
		{
			// Calcula la posición de la casilla
			int posX = POS_X_TAULER + CASELLA_INICIAL_X + (columna * AMPLADA_CASELLA);
			int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (fila * ALCADA_CASELLA);

			// Coloca las fichas en las casillas oscuras de las primeras tres filas de cada lado
			if ((fila + columna) % 2 != 0) // Solo en casillas oscuras
			{
				if (fila < 3)
				{
					// Fichas negras
					GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
				}
				else if (fila >= NUM_FILES_TAULER - 3)
				{
					// Fichas blancas
					GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
				}
			}
		}
	}

	return false;
}

*/


#include "joc.hpp"
#include <iostream>
#include <fstream>


Joc::Joc() : m_torn(COLOR_BLANC), m_finalitzat(false) {}

void Joc::inicialitza(const std::string& nomFitxerTauler)
{
    m_torn = COLOR_BLANC;
    m_finalitzat = false;
    m_seleccionada = Posicio();
    m_movimentsValids.clear();

    m_tauler.inicialitza(nomFitxerTauler);
    m_tauler.actualitzaMovimentsValids();
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    visualitza();

    if (m_finalitzat)
    {
        // Mostrar missatge de final de partida
        return true;
    }

    if (mouseStatus)
    {
        processaClick(mousePosX, mousePosY);
    }

    return false;
}

void Joc::visualitza() const
{
    // Dibuixa el fons i el tauler
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    // Dibuixa les fitxes
    for (int fila = 0; fila < N_FILES; fila++)
    {
        for (int col = 0; col < N_COLUMNES; col++)
        {
            Fitxa fitxa = m_tauler.getFitxa(fila, col);
            int posX = POS_X_TAULER + CASELLA_INICIAL_X + (col * AMPLADA_CASELLA);
            int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (fila * ALCADA_CASELLA);

            if (fitxa.getTipus() == TIPUS_NORMAL)
            {
                if (fitxa.getColor() == COLOR_BLANC)
                    GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
                else if (fitxa.getColor() == COLOR_NEGRE)
                    GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
            }
            else if (fitxa.getTipus() == TIPUS_DAMA)
            {
                if (fitxa.getColor() == COLOR_BLANC)
                    GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, posX, posY);
                else if (fitxa.getColor() == COLOR_NEGRE)
                    GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, posX, posY);
            }
        }
    }

    // Dibuixa les posicions vàlides
    for (const Posicio& pos : m_movimentsValids)
    {
        int posX = POS_X_TAULER + CASELLA_INICIAL_X + (pos.getColumna() * AMPLADA_CASELLA);
        int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (pos.getFila() * ALCADA_CASELLA);
        GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
    }
}


void Joc::processaClick(int mousePosX, int mousePosY)
{
    // Convertir coordenades de pantalla a posició al tauler
    int col = (mousePosX - POS_X_TAULER - CASELLA_INICIAL_X) / AMPLADA_CASELLA;
    int fila = (mousePosY - POS_Y_TAULER - CASELLA_INICIAL_Y) / ALCADA_CASELLA;

    if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
    {
        Posicio pos(fila, col);
        Fitxa fitxa = m_tauler.getFitxa(fila, col);

        // Si no hi ha fitxa seleccionada i es clica una fitxa del torn actual
        if (m_seleccionada == Posicio() && fitxa.getColor() == m_torn)
        {
            m_seleccionada = pos;
            int nPosicions;
            Posicio posicionsPossibles[8];
            m_tauler.getPosicionsPossibles(m_seleccionada, nPosicions, posicionsPossibles);
            m_movimentsValids.clear();
            for (int i = 0; i < nPosicions; i++)
            {
                m_movimentsValids.push_back(posicionsPossibles[i]);
            }
        }
        // Si hi ha fitxa seleccionada i es clica una posició vàlida
        else if (!(m_seleccionada == Posicio()) && esMovimentValid(pos))
        {
            m_tauler.mouFitxa(m_seleccionada, pos);
            m_seleccionada = Posicio();
            m_movimentsValids.clear();
            canviaTorn();
        }
    }
}

bool Joc::esMovimentValid(const Posicio& desti) const
{
    for (const Posicio& pos : m_movimentsValids)
    {
        if (pos == desti)
        {
            return true;
        }
    }
    return false;
}

void Joc::canviaTorn()
{
    m_torn = (m_torn == COLOR_BLANC) ? COLOR_NEGRE : COLOR_BLANC;
    m_tauler.actualitzaMovimentsValids();

    // Comprovar si el jugador actual pot moure
    bool potMoure = false;
    for (int fila = 0; fila < N_FILES && !potMoure; fila++)
    {
        for (int col = 0; col < N_COLUMNES && !potMoure; col++)
        {
            Fitxa fitxa = m_tauler.getFitxa(fila, col);
            if (fitxa.getColor() == m_torn && fitxa.getTipus() != TIPUS_EMPTY)
            {
                int nPosicions;
                Posicio posicionsPossibles[8];
                m_tauler.getPosicionsPossibles(Posicio(fila, col), nPosicions, posicionsPossibles);
                if (nPosicions > 0)
                {
                    potMoure = true;
                }
            }
        }
    }

    if (!potMoure)
    {
        m_finalitzat = true;
    }
}

void Joc::finalitza()
{
    // Aquí es podrien guardar estadístiques o resultats de la partida
}