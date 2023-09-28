#pragma once

#include "Drawble.h"
#include <glad/glad.h>
#include <vector>


class Grid : public IDrawble {
public:
	Grid();

	void draw(sf::RenderWindow& window_) override;
private:
	sf::Vector3f m_position = {0, 0, 0};
	sf::Color m_color = sf::Color(150, 150, 150);
	std::vector<GLfloat> m_vertexes;
	GLuint m_vbo;

	virtual void init_grid();
};