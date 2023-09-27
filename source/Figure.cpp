#include "Figure.h"


/////////////Figure///////////////////
Figure::Figure(const sf::Vector3f& position_, float size_)
	: m_position(position_), m_size(size_) {}


void Figure::set_texture(const std::string& path_) {
	m_texture = log_gl_texture(*ResourceHolder::Instance().getSfImage(path_));
}
void Figure::set_texture(GLuint texture_) {
	m_texture = texture_;
}


void Figure::rotate(const sf::Vector3f& rotation_) {
	m_rotation = rotation_;
	glRotatef(m_rotation.x, 1., 0., 0.);
	glRotatef(m_rotation.y, 0., 1., 0.);
	glRotatef(m_rotation.z, 0., 0., 1.);
}
void Figure::set_zoom(float zoom_) {
	m_zoom = zoom_;
	glTranslatef(m_position.x, m_position.y, m_position.z + m_zoom);
}

/////////////Plane///////////////////
Plane::Plane(const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::vector<sf::Vector2f>& vertexes_, const std::string& name_)
	: m_position(position_), m_rotation(rotation_), m_vertexes(vertexes_) {
	set_texture(name_);
}

Plane::~Plane() {
	glDeleteTextures(1, &m_texture);
}

#include <iostream>
void Plane::set_texture(const std::string& path_) {
	m_texture = log_gl_texture(*ResourceHolder::Instance().getSfImage(path_));
	std::cout << "TEX: " << m_texture << "\n";
}
void Plane::set_texture(GLuint texture_) {
	m_texture = texture_;
}


void Plane::set_mode(GLenum mode_) {
	m_mode = mode_;
}

void Plane::draw(sf::RenderWindow& window_) {
	if (m_vertexes.size() < 3) return;
	window_.setActive();
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_rotation.x, 1., 0., 0.);
	glRotatef(m_rotation.y, 0., 1., 0.);
	glRotatef(m_rotation.z, 0., 0., 1.);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(m_mode);
	for (const auto& vertex : m_vertexes) {
		glVertex2f( vertex.x, vertex.y);
	}
	glEnd();

	glPopMatrix();
}


/////////////////Square/////////////////////
Square::Square(float size_, const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::string& name_) 
	: DefinedPlane(size_, position_, rotation_, { {-1, -1}, {1, -1}, {1, 1}, {-1, 1} }, name_) {

}

void Square::draw(sf::RenderWindow& window_) {
	window_.setActive();
	glPushMatrix();

	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_rotation.x, 1., 0., 0.);
	glRotatef(m_rotation.y, 0., 1., 0.);
	glRotatef(m_rotation.z, 0., 0., 1.);

	//glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(m_mode);
	
	glTexCoord2f(0, 0);   glVertex2f(m_size * m_vertexes[0].x, m_size * m_vertexes[0].y);
	glTexCoord2f(1, 0);   glVertex2f(m_size * m_vertexes[1].x, m_size * m_vertexes[1].y);
	glTexCoord2f(1, 1);   glVertex2f(m_size * m_vertexes[2].x, m_size * m_vertexes[2].y);
	glTexCoord2f(0, 1);   glVertex2f(m_size * m_vertexes[3].x, m_size * m_vertexes[3].y);

	glEnd();

	glPopMatrix();
}


///////////////////Triangle/////////////////////
//Triangle::Triangle(float size_, const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::string& name_, const sf::Vector3f& angles_)
//	: DefinedPlane(size_, position_, rotation_, { {0, 1}, {1, -1}, {1, 1} }, name_) {
//
//}
//
//void Triangle::draw(sf::RenderWindow& window_) {
//	window_.setActive();
//	glPushMatrix();
//
//	glTranslatef(m_position.x, m_position.y, m_position.z);
//	glRotatef(m_rotation.x, 1., 0., 0.);
//	glRotatef(m_rotation.y, 0., 1., 0.);
//	glRotatef(m_rotation.z, 0., 0., 1.);
//
//	glBegin(m_mode);
//
//	glTexCoord2f(0, 0);   glVertex2f(m_size * m_vertexes[0].x, m_size * m_vertexes[0].y);
//	glTexCoord2f(1, 0);   glVertex2f(m_size * m_vertexes[1].x, m_size * m_vertexes[1].y);
//	glTexCoord2f(1, 1);   glVertex2f(m_size * m_vertexes[2].x, m_size * m_vertexes[2].y);
//	glTexCoord2f(0, 1);   glVertex2f(m_size * m_vertexes[3].x, m_size * m_vertexes[3].y);
//
//	glEnd();
//
//	glPopMatrix();
//}