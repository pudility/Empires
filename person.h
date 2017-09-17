#pragma once

#include "colony.h"
#include "randomnum.h"

#define PERSON_REPRODUCTION_THRESHOLD 10

class Person
{
public:
	Person( int iStrength, int iAge, int iReproductionValue, Colony* pColony ) : m_iStrength( iStrength ), m_iAge( iAge ), m_iReproductionValue( iReproductionValue ), m_bIsAlive( true ), m_pColony( pColony ) {}
	bool	IsAlive() { return m_bIsAlive; }

	void	Kill();
	Person* Reproduce();
	void	Age();

	Colony* GetColony() { return m_pColony; }
	int		GetStrength() { return m_iStrength; }
	int		GetReproductionValue() { return m_iReproductionValue; }

private:
	Colony *m_pColony;
	int m_iStrength;
	int m_iAge;
	int m_iReproductionValue;
	bool m_bIsAlive;
	RandomNumberGenerator m_RandomNumberGenerator;
};