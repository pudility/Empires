#include "occupiablecell.h"

void OccupiableCell::MoveInPerson( Person *pPerson )
{
    if ( !pPerson || m_pOccupant )
        return;

    m_pOccupant = pPerson;
}

void OccupiableCell::EvictOccupant()
{
    m_pOccupant = nullptr;
}

sf::Color OccupiableCell::GetCellColor()
{
    if ( !m_pOccupant )
        return sf::Color( 0, 255, 0, 255 );

    return m_pOccupant->GetColony()->GetColonyColor();
}