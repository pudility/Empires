#pragma once

#include <SFML/Graphics.hpp>
#include "person.h"

class BaseCell
{
public:
	virtual bool	IsOccupiableTerrain() = 0;
	virtual Person* GetOccupant() = 0;
	virtual void	MoveInPerson( Person* pPerson ) = 0;
	virtual void    EvictOccupant() = 0;

	virtual sf::Color GetCellColor() = 0;
private:
};