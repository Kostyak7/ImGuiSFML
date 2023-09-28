#pragma once
#include <SFML/Graphics.hpp>

struct IDrawble {
	virtual void draw(sf::RenderWindow& window_) = 0;
};