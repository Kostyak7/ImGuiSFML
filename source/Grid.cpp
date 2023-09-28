#include "Grid.h"
#include "config.h"
#include <iostream>


Grid::Grid() {
	init_grid();
}


void Grid::init_grid() {
	m_vertexes = { 0.f, 1.f, 0.f,  0.f, -1.f, 0.f,   1.f, 0.f, 0.f,  -1.f, 0.f, 0.f, };

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexes.size() * sizeof(GLfloat), m_vertexes.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Grid::draw(sf::RenderWindow& window_) {
	window_.setActive();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
		glColor3f(SF_COLOR_TO_3F(m_color));

		for (int i = -1000; i < 1000; ++i) {
			glPushMatrix();
			glTranslatef(-1 + i * 0.1f, 0.0f, 0.0f);
			glScalef(1.f, 100.0f, 1.f);
			glDrawArrays(GL_LINES, 0, 2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.f, -1 + i * 0.1f, 0.0f);
			glScalef(100.0f, 1.f, 1.f);
			glDrawArrays(GL_LINES, 2, 4);
			glPopMatrix();
		}

	glDisableClientState(GL_VERTEX_ARRAY);
}