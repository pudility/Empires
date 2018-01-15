#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "randomnum.h"
#include "map.h"
#include "rules.hpp"

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 400
#define DEFAULT_MAP_WIDTH 100
#define DEFAULT_MAP_HEIGHT 100
#define DEFAULT_MAP_TEXTURE "world_map.png"

class Application
{
public:
    Application(): m_RandomNumberGenerator ( 100 ) {};
	void run();
private:
    RandomNumberGenerator m_RandomNumberGenerator;
	sf::RenderWindow m_Window;
	sf::Sprite		 m_View;
	sf::Texture		 m_BackgroundTexture;
    map      *m_mMap = new map();
};
