#pragma once

#include "Prism.h"
#include <list>


class Model : public IDrawble {
public:
	Model();

	void update();
	void draw(sf::RenderWindow& window_) override;
protected:
	std::list<Prism> m_prisms;

	virtual void init_model();
};