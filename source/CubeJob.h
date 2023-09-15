#pragma once

#include "WindowJob.h"
#include "Figure.h"
#include <vector>


class Cube : public Figure{
public:
    Cube();
    void draw(sf::RenderWindow& window_, const sf::Vector3f& rotation_, float zoom_ = 0) override;
private:
    std::vector<Square> m_squares;
};


class CubeJob : public WindowJob {
public:
    CubeJob();

private:
    bool m_is_left_pressed = false;
    sf::Vector2i m_start_press_pos;
    sf::Vector3f m_new_cube_rotation, m_last_cube_rotation;
    float m_zoom = 0.f;
    Cube m_cube;
    void init_job() override;

    int process_events() override;
    int update() override;
    int render() override;
};
