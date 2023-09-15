#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>


#ifndef GL_CLAMP_TO_EDGE 
#define GL_CLAMP_TO_EDGE 0x812F
#endif // !GL_CLAMP_TO_EDGE 


class Figure {
public:
	Figure(const sf::Vector3f& position_, float size_ = 20.f);
	~Figure();

	virtual void draw(sf::RenderWindow& window_, const sf::Vector3f& rotation_, float zoom_ = 0) = 0;
protected:
	sf::Clock m_clock;
	sf::Vector3f m_position;
	sf::Vector3f m_rotation;
	float m_zoom = 0.f;
	GLuint m_texture;
	float m_size;

	void rotate(const sf::Vector3f& rotation_);
	void set_zoom(float zoom_ = 0);
public:
	static GLuint load_texture(const std::string& name_);
};


class Plane {
public:
	Plane(const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::vector<sf::Vector2f>& vertexes_, const std::string& name_);
	~Plane();

	void set_texture(const std::string& name_);
	void set_mode(GLenum mode_ = GL_TRIANGLE_FAN);
	virtual void draw(sf::RenderWindow& window_);
protected:
	std::vector<sf::Vector2f> m_vertexes;
	sf::Vector3f m_position;
	sf::Vector3f m_rotation;
	GLuint m_texture;
	GLenum m_mode = GL_TRIANGLE_FAN;
};


class DefinedPlane : public Plane {
public:
	DefinedPlane(float size_, const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::vector<sf::Vector2f>& vertexes_, const std::string& name_)
		: m_size(size_), Plane(position_, rotation_, vertexes_, name_) {}
protected:
	float m_size;
private:
	using Plane::set_mode;
};


class Square : public DefinedPlane {
public:
	Square(float size_, const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::string& name_);

	void draw(sf::RenderWindow& window_) override;
};


//class Triangle : public DefinedPlane {
//	Triangle(float size_, const sf::Vector3f& position_, const sf::Vector3f& rotation_, const std::string& name_, const sf::Vector3f& angles_);
//
//	void draw(sf::RenderWindow& window_) override;
//};