#include "application.h"
#include "aidirector.h"
#include <SFML/Graphics.hpp>

void Application::run()
{
    m_Window.create( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Empires", sf::Style::Default );

    Map *pGameMap = new Map;
    m_mMap->UTIL_MakeEmptyMap( pGameMap, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT );
    m_mMap->UTIL_PopulateTestMap( pGameMap );
    Director AI( pGameMap );

    // Start the director
    AI.Start();

    m_View.setPosition(0, 0);
    m_View.setScale( WINDOW_WIDTH / DEFAULT_MAP_WIDTH, WINDOW_HEIGHT / DEFAULT_MAP_HEIGHT );

    sf::Image *pFrame = new sf::Image();

    pFrame->create( DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT );

    for (int i = 0; i < rules::iTeams; i++) {
        Colony *pColony;
        
        switch (i) {
            case 0:
                pColony = new Colony( sf::Color( 255, 0, 255, 255 ) );
                break;
            case 1:
                pColony = new Colony( sf::Color( 255, 255, 0, 255 ) );
                break;
            case 2:
                pColony = new Colony( sf::Color( 255, 0, 0, 255 ) );
                break;
            case 3:
                pColony = new Colony( sf::Color( 0, 0, 255, 255 ) );
                break;
            default:
                pColony = new Colony( sf::Color( 255, 0, 255, 255 ) );
                break;
        }

        Person *pPerson = new Person( 10, 0, 0, pColony );
        
        int iSpawnLoc = m_RandomNumberGenerator.CreateRandomNumber();
        
        m_mMap->UTIL_At2D( pGameMap, iSpawnLoc, iSpawnLoc )->MoveInPerson( pPerson );
    }

    m_mMap->UTIL_RenderMap( pGameMap, pFrame ); // Draw the init map
    while ( m_Window.isOpen() )
    {
        sf::Event event;
        while ( m_Window.pollEvent( event ) )
        {
            if (event.type == sf::Event::Closed)
                m_Window.close();
        }

        if ( AI.DoThink() )
        {
            m_mMap->UTIL_RenderMap( pGameMap, pFrame, AI.GetDeltaMap() );  // if deltamap stops working don't pass it in
            m_BackgroundTexture.loadFromImage( *pFrame );
            m_View.setTexture( m_BackgroundTexture );
            m_Window.draw( m_View );
            m_Window.display();
        }
    }
}
