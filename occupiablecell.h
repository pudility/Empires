#pragma once

#include "basecell.h"

class OccupiableCell : public BaseCell
{
public:
	virtual bool	IsOccupiableTerrain() override { return true; }
	virtual Person* GetOccupant() override 
	{ 
		return m_pOccupant; 
	}
	virtual void	MoveInPerson( Person* pPerson ) override;
	virtual void    EvictOccupant() override;

	virtual sf::Color GetCellColor() override;
private:
	Person *m_pOccupant;
};