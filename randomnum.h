#pragma once

#include <random>

// Util for creating random number between 0-3
class RandomNumberGenerator
{
public:
	RandomNumberGenerator( int max )
	{
		// Random number util
		m_RandomNumberEngine = std::mt19937( std::random_device()() );
		m_UnbiasedGenerator = std::uniform_int_distribution<int>( 0, max );
	}
	int CreateRandomNumber() { return m_UnbiasedGenerator( m_RandomNumberEngine ); };
private:
	std::mt19937 m_RandomNumberEngine;    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> m_UnbiasedGenerator; // guaranteed unbiased
};
