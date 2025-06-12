/*
#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"

using namespace std;


class Joc 
{

public:
    Joc() {};
    
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    
    
private:

};

#endif 
*/

#ifndef JOC_HPP
#define JOC_HPP

#include <vector>
#include <string>
#include "posicio.hpp"
#include "fitxa.h"
#include "tauler.hpp"
#include "info_joc.hpp"
#include "GraphicManager.h"

class Joc
{
public:
    Joc();
    void inicialitza(const std::string& nomFitxerTauler);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void visualitza() const;
    void finalitza();

private:
    void processaClick(int mousePosX, int mousePosY);
    bool esMovimentValid(const Posicio& desti) const;
    void canviaTorn();

    Tauler m_tauler;
    ColorFitxa m_torn;
    bool m_finalitzat;
    Posicio m_seleccionada;
    std::vector<Posicio> m_movimentsValids;
};

#endif