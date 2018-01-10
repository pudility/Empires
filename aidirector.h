#pragma once

#include <SFML/System/Clock.hpp>
#include <random>

#include "map.h"
#include "person.h"
#include "randomnum.h"

#define AI_DEFAULT_THINK_TIME sf::milliseconds( 50 )

class Director
{
public:
	Director( Map *pMap );
	void Start();
	void Stop();
	bool DoThink() { return DirectorThink(); }
	void SetThinkInterval( sf::Time tThinkInverval ) { m_tThinkInterval = tThinkInverval; }

	DeltaMap* GetDeltaMap() { return m_pDeltaMap; }
private:
	bool DirectorThink();
	bool DoFight( Person *pPersonOne, Person *pPersonTwo );
	// [min,max)
	inline bool IsNumberInRange( int num, int min, int max )
	{
		return ( num >= min ) && ( num < max );
	}

	bool m_bIsRunning = false;
	
	sf::Clock m_Clock;
	sf::Time  m_tLastThink;
	sf::Time  m_tThinkInterval; // Default constructor sets this to zero
	Map		 *m_pMap;
	DeltaMap *m_pDeltaMap;
	RandomNumberGenerator m_RandomNumberGenerator;
};
