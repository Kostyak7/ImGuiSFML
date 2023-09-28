#pragma once

#include <SFML/Graphics.hpp>


class Camera {
public:

	void update(sf::RenderWindow& window_);
	void render(sf::RenderWindow& window_);
	void render_position(sf::RenderWindow& window_);
	void render_rotation(sf::RenderWindow& window_);

	void addZoomDelta(float delta_);
private:
	sf::Vector3f m_rotation = { 0,0,0 }, m_tmp_rotation;
	sf::Vector3f m_position = { 0,0, -3 }, m_tmp_position;

	bool m_is_left_pressed = false, m_is_right_pressed = false;
	sf::Vector2i m_start_press_left_pos, m_start_press_right_pos;

};