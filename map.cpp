#include "map.h"
#include <iostream>

void UTIL_MakeEmptyMap( Map *pMap, int iWidth, int iHeight )
{
	if ( !pMap )
		pMap = new Map();
	for ( int i = 0; i < iHeight; i++ )
	{
		std::vector< BaseCell* > vecRow;
		vecRow.resize( iWidth );

		pMap->push_back( vecRow );
	}
}

// Populate map with moveable terrain
void UTIL_PopulateTestMap( Map *pMap )
{
	if ( !pMap )
		return; // TODO: Handle this

	size_t MapWidth = pMap->at( 0 ).size();

	for ( size_t iVerticalIndex = 0; iVerticalIndex < pMap->size(); iVerticalIndex++ )
	{
		for ( size_t iHorizontalIndex = 0; iHorizontalIndex < MapWidth; iHorizontalIndex++ )
		{
			pMap->at(iHorizontalIndex).at(iVerticalIndex) = new OccupiableCell();
		}
	}
}

void UTIL_RenderMap( Map *pMap, sf::Image *pImage, DeltaMap *pDeltaMap /*= nullptr*/ )
{
	if ( !pMap )
		return;

	// Our 2D vector has Y=0 as the top. Alligned map is flipped for pixel output
	Map pAllignedMap = *pMap;
	std::reverse( pAllignedMap.begin(), pAllignedMap.end() );
	// Pre calculate dimentions
	size_t MapHeight = pAllignedMap.size();
	size_t MapWidth = pAllignedMap.at( 0 ).size();

	if ( !pDeltaMap )
	{
		for ( int iVerticalIndex = 0; iVerticalIndex < pAllignedMap.size(); iVerticalIndex++ )
		{
			for ( int iHorizontalIndex = 0; iHorizontalIndex < MapWidth; iHorizontalIndex++ )
			{
				pImage->setPixel( iHorizontalIndex, iVerticalIndex, UTIL_At2D( &pAllignedMap, iHorizontalIndex, iVerticalIndex )->GetCellColor() );
			}
		}
	}
	else
	{
		DeltaMap::iterator itDeltaMap;
		for ( itDeltaMap = pDeltaMap->begin(); itDeltaMap!=pDeltaMap->end(); itDeltaMap++ )
		{
			int iXPosition = itDeltaMap->second;
			int iYPosition = itDeltaMap->first;
            iYPosition = -iYPosition + ( int )MapHeight; // Flip Y values across the middle of the map

            if ( iYPosition==MapHeight )
            {
                iYPosition--; // 0 is a valid index but MapHeight isnt.
            }

			pImage->setPixel( iXPosition, iYPosition, UTIL_At2D( &pAllignedMap, iXPosition, iYPosition )->GetCellColor() );
		}
	}
}

inline BaseCell* UTIL_At2D( Map *pMap, int x, int y )
{
	return pMap->at( y ).at( x );
}


// Slower but preforms access checks. Will never cause a crash (almost)
// Note: In perf test took 2x more power than UTIL_At2D
BaseCell* UTIL_At2D_Safe( Map *pMap, int x, int y )
{
	if ( !pMap || ( x < 0 || y < 0 ) )
		return nullptr;

	if ( y > pMap->size() - 1 || x > pMap->at( 0 ).size() - 1 ) // This can cause crashing and is computationally heavy
		return nullptr;

	return UTIL_At2D( pMap, x, y );
}
