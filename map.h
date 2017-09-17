#pragma once

#include <vector>
#include "occupiablecell.h"

typedef std::vector< std::vector< BaseCell* > > Map;
typedef std::vector< std::pair< int, int > > DeltaMap;

void UTIL_MakeEmptyMap( Map *pMap, int iWidth, int iHeight );
void UTIL_PopulateTestMap( Map *pMap );
void UTIL_RenderMap( Map *pMap, sf::Image *pImage, DeltaMap *pDeltaMap = nullptr );
BaseCell* UTIL_At2D( Map *pMap, int x, int y );
BaseCell* UTIL_At2D_Safe( Map *pMap, int x, int y );