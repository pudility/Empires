#pragma once

#include "basecell.h"

class OceanCell : public BaseCell
{
public:
	virtual bool IsOccupiableTerrain() override { return false; }
	virtual sf::Color GetCellColor() override { return sf::Color( 0, 0, 255, 255 ); }
};