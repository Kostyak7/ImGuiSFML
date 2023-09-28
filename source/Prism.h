#pragma once

#include "Drawble.h"
#include <glad/glad.h>
#include <vector>


class Prism : public IDrawble {
public:
	Prism(float height_, const sf::Vector3f& position_, const std::vector<GLfloat>& vertexes_);

	void update();
	void draw(sf::RenderWindow& window_) override;
private:
	sf::Color m_color = sf::Color::Green;
	GLuint m_vbo;
	sf::Vector3f m_position;
	sf::Vector3f m_rotation;
	float m_height = 1;
	std::vector<GLfloat> m_vertexes;
	std::vector<GLuint> m_vert_indexes, m_ind_indexes;


	void init_prism();
};