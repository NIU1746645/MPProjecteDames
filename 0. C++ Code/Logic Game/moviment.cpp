#include "moviment.h"

int Moviment::getNCami()
{
	while (!m_cami.empty())
	{
		m_nCami++;
	}

	return m_nCami;
}

int Moviment::getNCaptures()
{
	while (!m_captures.empty())
	{
		m_nCaptures++;
	}

	return m_nCaptures;
}
