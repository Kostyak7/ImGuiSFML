#pragma once

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <string>


#ifndef GL_CLAMP_TO_EDGE 
#define GL_CLAMP_TO_EDGE 0x812F
#endif // !GL_CLAMP_TO_EDGE 

#define END_FLAG 0
#define CONTINUE_FLAG 1

///////////Base///////////
const sf::Vector2u WINDOW_SIZE = { 1280, 720 };
const unsigned int FRAME_LIMIT = 60;
const std::string DEFAULT_WINDOW_TITLE = "FOLK-Engine";
const auto DEFAULT_CONTEXT_SETTINGS = sf::ContextSettings(24);
const sf::Color DEFAULT_BACKGROUND_COLOR = { sf::Color::Black };