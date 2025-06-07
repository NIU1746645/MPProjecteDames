#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.hpp"
#include <vector>

using namespace std;

const int MAX_MOVIMENTS = 100;

class Moviment
{
public:
	Moviment() : m_nCami(0), m_nCaptures(0) {}
    
    void afegirCami(const Posicio& pos) { m_cami.push_back(pos); m_nCami++; }
    void afegirCaptures(const Posicio& pos) { m_captures.push_back(pos); m_nCaptures++; };
    
    vector<Posicio> getCami() const {return m_cami;}
    vector<Posicio> getCaptures() const { return m_captures;}

    int getNCami();
    int getNCaptures();

    bool esValid() const { return !m_cami.empty();}

private:
    vector<Posicio> m_cami;
    int m_nCami;
    vector<Posicio> m_captures; 
	int m_nCaptures;
};

#endif
