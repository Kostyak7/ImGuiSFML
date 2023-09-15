#pragma once

#include "WindowJob.h"
#include <GL/freeglut.h>
#include <vector>


class Pyramid {
public:
    Pyramid();
    ~Pyramid();

    void draw(sf::RenderWindow& window_, float rotate_x_, float rotate_y_);
private:
    sf::Clock m_clock;
    GLuint m_box;
    float m_size = 20.f;
};


class PyramidJob : public WindowJob {
public:
    PyramidJob();

private:
    bool m_is_left_pressed = false;
    sf::Vector2i m_start_press_pos;
    sf::Vector2f m_new_cube_rotation, m_last_cube_rotation;
    Pyramid m_pyramid;
    void init_job() override;

    int process_events() override;
    int update() override;
    int render() override;
};
