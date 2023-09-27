#pragma once
#include <SFML/Graphics.hpp>
#include <string>


#ifndef GL_CLAMP_TO_EDGE 
#define GL_CLAMP_TO_EDGE 0x812F
#endif // !GL_CLAMP_TO_EDGE 


#define END_FLAG 0
#define CONTINUE_FLAG 1

const sf::VideoMode DEFAULT_VIDEO_MODE{ 1000, 900 };
const sf::Color DEFAULT_BACKGROUND_COLOR{ sf::Color::Black };