#pragma once

#include <SFML/Graphics.hpp>
#include <string>


#ifndef GL_CLAMP_TO_EDGE 
#define GL_CLAMP_TO_EDGE 0x812F
#endif // !GL_CLAMP_TO_EDGE 

#define END_FLAG 0
#define CONTINUE_FLAG 1

#define SF_COLOR_TO_3I(color_) 	color_.r, color_.g, color_.b
#define SF_COLOR_TO_3F(color_) 	color_.r / 255.f, color_.g / 255.f, color_.b / 255.f
#define SF_COLOR_TO_4I(color_) 	color_.r, color_.g, color_.b, color_.a
#define SF_COLOR_TO_4F(color_) 	color_.r / 255.f, color_.g / 255.f, color_.b / 255.f, color_.a/ 255.f

#define SF_VECTOR2_TO_2(value_) value_.x, value_.y
#define SF_VECTOR3_TO_3(value_) value_.x, value_.y, value_.z

///////////Base///////////
const sf::Vector2u WINDOW_SIZE = { 800, 800 };
const unsigned int FRAME_LIMIT = 60;
const std::string DEFAULT_WINDOW_TITLE = "FOLK-Engine";
const auto DEFAULT_CONTEXT_SETTINGS = sf::ContextSettings(24);
const sf::Color DEFAULT_BACKGROUND_COLOR = { sf::Color::Black };