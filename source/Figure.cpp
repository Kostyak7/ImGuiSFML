#include "Figure.h"

/////////////Figure///////////////////
Figure::Figure(const sf::Vector3f& position_, float size_)
	: m_position(position_), m_size(size_) {}

Figure::~Figure() {
	glDeleteTextures(1, &m_texture);
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

GLuint Figure::load_texture(const std::string& name_) {
	sf::Image image;
	if (!image.loadFromFile(name_)) return END_FLAG;
	image.flipVertically();

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}


/////////////Plane///////////////////
Plane::Plane(const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::vector<sf::Vector2f>& vertexes_, const std::string& name_)
	: m_position(position_), m_rotation(rotation_), m_vertexes(vertexes_) {
	set_texture(name_);
}

Plane::~Plane() {
	glDeleteTextures(1, &m_texture);
}


void Plane::set_texture(const std::string& name_) {
	m_texture = Figure::load_texture(name_);
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

	glBegin(m_mode);
	//front
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