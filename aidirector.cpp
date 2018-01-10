#include "aidirector.h"


Director::Director( Map *pMap )
{
	if ( !pMap ) // Handle this
		return;

	m_pMap = pMap;
	m_pDeltaMap = new DeltaMap;

	m_Clock.restart();
	m_tThinkInterval = AI_DEFAULT_THINK_TIME;
}

void Director::Start()
{
	if ( !m_bIsRunning )
		m_bIsRunning = true;
}

void Director::Stop()
{
	if ( m_bIsRunning )
		m_bIsRunning = false;
}

// Returns TRUE if the AI performed a think
bool Director::DirectorThink()
{
	if ( m_bIsRunning && ( m_tLastThink + m_tThinkInterval ) <= m_Clock.getElapsedTime() )
	{
		if ( !m_pMap )
			return false; 

		// Clear the delta map
		m_pDeltaMap->clear();

		// Loop through map contents
		Map::iterator yIterator;
		std::vector< BaseCell* >::iterator xIterator;
		size_t iMapHeight = m_pMap->size();
		size_t iMapWidth = m_pMap->at(0).size();

		int iHorizontalPosition = 0, iVerticalPosition = 0;

		for ( yIterator = m_pMap->begin(); yIterator < m_pMap->end(); yIterator++, iVerticalPosition++ )
		{
			for ( xIterator = yIterator->begin(); xIterator < yIterator->end(); xIterator++, iHorizontalPosition++ )
			{
				BaseCell *pCell = *xIterator;
				
				if ( !pCell || !pCell->IsOccupiableTerrain() )
					continue;

				Person *pPerson = pCell->GetOccupant();

				if ( !pPerson || !pPerson->IsAlive() )
					continue;

				// Do standart person turn things
				pPerson->Age();

				if ( pPerson->GetReproductionValue() >= PERSON_REPRODUCTION_THRESHOLD )
				{
					// Find an open square to dump the child
					BaseCell *pEmptyCell = nullptr; // Compiler hack, wont build if not expressly set to nullptr
					for ( int iXOffset = -1; iXOffset <= 1; iXOffset++ )
					{
						for ( int iYOffset = -1; iYOffset <= 1 ; iYOffset++ )
						{
							int iDesiredXPosition = iHorizontalPosition + iXOffset;
							int iDesiredYPosition = iVerticalPosition + iYOffset;
							if ( !IsNumberInRange( iDesiredYPosition, 0, ( int )iMapHeight ) || !IsNumberInRange( iDesiredXPosition, 0, ( int )iMapWidth ) )
								continue;

							pEmptyCell = UTIL_At2D( m_pMap, iHorizontalPosition + iXOffset, iVerticalPosition + iYOffset );
                            m_pDeltaMap->push_back( std::make_pair( iHorizontalPosition, iVerticalPosition ) );
							if ( pEmptyCell && pEmptyCell->IsOccupiableTerrain() && !pEmptyCell->GetOccupant() )
								goto EmptyCellFound;
						}	
					}
				EmptyCellFound:
					if( pEmptyCell && !pEmptyCell->GetOccupant() )
					{
						Person *pOffspring = pPerson->Reproduce();
						if ( pOffspring )
						{
							pEmptyCell->MoveInPerson( pOffspring );
							m_pDeltaMap->push_back( std::make_pair( iHorizontalPosition, iVerticalPosition ) );
						}

						continue;
					}
					// If no empty space dont have baby yet
				}
				// Person think. Start by trying to move up, down, left, or right
				int iDesiredXPosition = iHorizontalPosition;
				int iDesiredYPosition = iVerticalPosition;

				switch ( m_RandomNumberGenerator.CreateRandomNumber() )
				{
				case 0:
					// Move UP
					iDesiredYPosition--;
					break;
				case 1:
					// Move RIGHT
					iDesiredXPosition++;
					break;
				case 2:
					// Move DOWN
					iDesiredYPosition++;
					break;
				case 3:
					// move LEFT
					iDesiredXPosition--;
					break;
				default:
					break;
				}

				BaseCell *pTargetCell = nullptr; // Another compiler hack
				if ( IsNumberInRange( iDesiredYPosition, 0, ( int )iMapHeight ) && IsNumberInRange( iDesiredXPosition, 0, ( int )iMapWidth) )
				{
					pTargetCell = UTIL_At2D( m_pMap, iDesiredXPosition, iDesiredYPosition );
				}
				
				if ( !pTargetCell || !pTargetCell->IsOccupiableTerrain() )
					continue;

				Person *pDesiredCellOccupant = pTargetCell->GetOccupant();
				if ( pDesiredCellOccupant )
				{
					if ( pDesiredCellOccupant->GetColony() != pPerson->GetColony() )
					{
						// Kill then free the cell
						if ( DoFight( pPerson, pDesiredCellOccupant ) )
						{
							pTargetCell->EvictOccupant();
							pDesiredCellOccupant->Kill();
							pCell->EvictOccupant();
						}
						else
						{
							pPerson->Kill();
							pCell->EvictOccupant();

							m_pDeltaMap->push_back( std::make_pair( iHorizontalPosition, iVerticalPosition) ); //pCell
							continue;
						}
					}
					else
					{
						continue;
					}
				}

				// Move person into new cell
				pCell->EvictOccupant();
				pTargetCell->MoveInPerson( pPerson );

				m_pDeltaMap->push_back( std::make_pair( iHorizontalPosition, iVerticalPosition) ); // pCell
				m_pDeltaMap->push_back( std::make_pair( iDesiredXPosition, iDesiredYPosition ) ); // pTargetCell
			}
			iHorizontalPosition = 0;
		}
		
		m_tLastThink = m_Clock.getElapsedTime();
		return true;
	}
	return false;
}

// Returns TRUE if person one wins
bool Director::DoFight( Person *pPersonOne, Person *pPersonTwo )
{
	if ( !pPersonOne || !pPersonTwo )
		return false;	// TODO: Handle this error

	// Gives person two a slight advantage ( wins ties ) because they are the defending force.
	return pPersonOne->GetStrength() > pPersonTwo->GetStrength();
}
