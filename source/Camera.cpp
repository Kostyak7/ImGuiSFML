#include "Camera.h"
#include <glad/glad.h>
#include "config.h"


void Camera::addZoomDelta(float delta_) {
    m_position.z += delta_ * 0.1f;
}

void Camera::update(sf::RenderWindow& window_) {
    auto mouse_pos = sf::Mouse::getPosition();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (!m_is_right_pressed) {
            m_tmp_rotation = m_rotation;
            m_start_press_right_pos = mouse_pos;
        }
        m_is_right_pressed = true;
        int z_pos = (m_position.z < 0) ? 1 : -1;
        m_rotation.x = m_tmp_rotation.x - z_pos * (m_start_press_right_pos.y - mouse_pos.y) / 2.f;
        m_rotation.y = m_tmp_rotation.y - z_pos * (m_start_press_right_pos.x - mouse_pos.x) / 2.f;
    }
    else {
        m_is_right_pressed = false;
    }

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!m_is_left_pressed) {
            m_tmp_position = m_position;
            m_start_press_left_pos = mouse_pos;
        }
        int z_pos = (m_position.z < 0) ? 1 : -1;
        m_is_left_pressed = true;
        m_position.x = m_tmp_position.x - z_pos * (m_start_press_left_pos.x - mouse_pos.x) / 100.f;;
        m_position.y = m_tmp_position.y + (m_start_press_left_pos.y - mouse_pos.y) / 100.f;
    }
    else {
        m_is_left_pressed = false;
    }
}

void Camera::render(sf::RenderWindow& window_) {
    render_rotation(window_);
    render_position(window_);
}

void Camera::render_position(sf::RenderWindow& window_) {
	glTranslatef(SF_VECTOR3_TO_3(m_position));
}

void Camera::render_rotation(sf::RenderWindow& window_) {
    glRotatef(m_rotation.x, 1., 0., 0.);
    glRotatef(m_rotation.y, 0., 1., 0.);
    glRotatef(m_rotation.z, 0., 0., 1.);
}