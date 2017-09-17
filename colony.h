#pragma once

#include <SFML/Graphics.hpp>

class Colony
{
public:
	Colony( sf::Color Color ) : m_ColonyColor( Color ) {};
	sf::Color GetColonyColor() { return m_ColonyColor; };
	
private:
	sf::Color m_ColonyColor;
};