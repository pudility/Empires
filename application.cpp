#include "application.h"
#include "aidirector.h"
#include <SFML/Graphics.hpp>

void Application::run()
{
	m_Window.create( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Empires", sf::Style::Default );

	Map *pGameMap = new Map;
	UTIL_MakeEmptyMap( pGameMap, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT );
	UTIL_PopulateTestMap( pGameMap );
	Director AI( pGameMap );

	// Start the director
	AI.Start();

	m_View.setPosition(0, 0);
	m_View.setScale( WINDOW_WIDTH / DEFAULT_MAP_WIDTH , WINDOW_HEIGHT / DEFAULT_MAP_HEIGHT );

	sf::Image *pFrame = new sf::Image();

	pFrame->create( DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT );

	Colony *pColonyOne = new Colony( sf::Color( 255, 255, 0, 255 ) );
	Person *pPersonOne = new Person( 10, 0, 0, pColonyOne );
	Colony *pColonyTwo = new Colony( sf::Color( 255, 0, 255, 255 ) );
	Person *pPersonTwo = new Person( 10, 0, 0, pColonyTwo ); /* I changed this from 15 to 10 inorder to make it more fair, otherwise one of the armies wins every time */
	UTIL_At2D( pGameMap, 1, 1 )->MoveInPerson( pPersonOne );
	UTIL_At2D( pGameMap, 80, 80 )->MoveInPerson( pPersonTwo );

	UTIL_RenderMap( pGameMap, pFrame ); // Draw the init map
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
			UTIL_RenderMap( pGameMap, pFrame , AI.GetDeltaMap() ); // if deltamap stops working don't pass it in
			m_BackgroundTexture.loadFromImage( *pFrame );
			m_View.setTexture( m_BackgroundTexture );
			m_Window.draw( m_View );
			m_Window.display();
		}
	}
}
