#include "person.h"
#include <iostream>

void Person::Kill()
{
	if ( m_bIsAlive )
		m_bIsAlive = false;

	// No use for dead people... yet.
	if( this )
		delete this;
}

void Person::Age()
{
	if ( !IsAlive() )
		return;
	m_iAge++;
	m_iReproductionValue++;
}

Person* Person::Reproduce()
{
	if ( m_iReproductionValue < PERSON_REPRODUCTION_THRESHOLD )
		return nullptr;

	m_iReproductionValue = 0;

	int iOffspringStrength = m_iStrength;

	// Roll for mutation. 25% chance for weaker offspring or 25% chance of stronger offspring
    int iRoll = m_RandomNumberGenerator.CreateRandomNumber();

    switch ( iRoll )
	{
	case 1:
		iOffspringStrength--;
    case 2:
        iOffspringStrength++;
	default:
		break;
	}

	return new Person( iOffspringStrength, 0, 0, m_pColony );
}
