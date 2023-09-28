#include "Prism.h"
#include "config.h"


Prism::Prism(float height_, const sf::Vector3f& position_, const std::vector<GLfloat>& vertexes_)
	: m_height(height_), m_position(position_), m_vertexes(18) {
	std::vector<GLfloat> vertexes{ vertexes_ };
	vertexes.resize(6);

	for (int i = 0; i < 6; i += 2) {
		m_vertexes[3 * i / 2] = m_vertexes[3 * i / 2 + 9] = vertexes[i];
		m_vertexes[3 * i / 2 + 1] = m_vertexes[3 * i / 2 + 1 + 9] = vertexes[i + 1];
		m_vertexes[3 * i / 2 + 2] = m_height / 2.f;
		m_vertexes[3 * i / 2 + 2 + 9] = - m_height / 2.f;
	}

	
	init_prism();
}


void Prism::init_prism() {
	m_vert_indexes = { 0,1,2,5,4,3,1,0,3,2,5,3 };
	m_ind_indexes = { 0,1,2,0,3,5,2,5,4,1,4,3 };

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexes.size() * sizeof(GLfloat), m_vertexes.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Prism::update() {

}

void Prism::draw(sf::RenderWindow& window_) {
	window_.setActive();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(SF_COLOR_TO_3F(m_color));

	//Bases
	glPushMatrix();
	
	glTranslatef(SF_VECTOR3_TO_3(m_position));
	//glTranslatef(m_position.x, m_position.y, m_position.z + m_height / 2.f);
	glColor3f(SF_COLOR_TO_3F(m_color));
	glDrawElements(GL_TRIANGLE_STRIP, m_vert_indexes.size(), GL_UNSIGNED_INT, m_vert_indexes.data());

	glColor3f(SF_COLOR_TO_3F(sf::Color::Black));
	glDrawElements(GL_LINE_LOOP, m_ind_indexes.size(), GL_UNSIGNED_INT, m_ind_indexes.data());

	/*glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glColor3f(SF_COLOR_TO_3F(sf::Color::Black));
	glDrawArrays(GL_LINE_LOOP, 0, 6);
	
	glColor3f(SF_COLOR_TO_3F(m_color));
	glTranslatef(0, 0, -m_height);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glColor3f(SF_COLOR_TO_3F(sf::Color::Black));
	glDrawArrays(GL_LINE_LOOP, 0, 6);*/
	glPopMatrix();



	glDisableClientState(GL_VERTEX_ARRAY);
}