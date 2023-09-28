#include "Model.h"


Model::Model() {
	init_model();
}


void Model::init_model() {
	m_prisms.emplace_back(5, sf::Vector3f{ 0,0,0 }, std::vector<GLfloat>{ -1, 0, 1, 1, 1, -1 });
	m_prisms.emplace_back(5, sf::Vector3f{ 2,0,0 }, std::vector<GLfloat>{ 1, 0, -1, 1, -1, -1 });
}

void Model::update() {
	for (auto& prism : m_prisms) {
		prism.update();
	}
}

void Model::draw(sf::RenderWindow& window_) {
	for (auto& prism : m_prisms) {
		prism.draw(window_);
	}
}

