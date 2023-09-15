#include "CubeJob.h"


/////////////////Cube///////////////////////
Cube::Cube()
    : Figure(sf::Vector3f(0.f, 0.f, -100.f)) {
    m_texture = load_texture("saul.png");


    m_squares.emplace_back(m_size, sf::Vector3f(0, 0, m_size), sf::Vector3f(), "saul.png");         //front
    m_squares.emplace_back(m_size, sf::Vector3f(0, 0, -m_size), sf::Vector3f(), "saul.png");        //back
    m_squares.emplace_back(m_size, sf::Vector3f(-m_size, 0, 0), sf::Vector3f(0, 90, 0), "saul.png");//left
    m_squares.emplace_back(m_size, sf::Vector3f(m_size, 0, 0), sf::Vector3f(0, 90, 0), "saul.png"); //right
    m_squares.emplace_back(m_size, sf::Vector3f(0, -m_size, 0), sf::Vector3f(90, 0, 0), "saul.png");//bottom
    m_squares.emplace_back(m_size, sf::Vector3f(0, m_size, 0), sf::Vector3f(90, 0, 0), "saul.png"); //top
}

void Cube::draw(sf::RenderWindow& window_, const sf::Vector3f& rotation_, float zoom_) {
    window_.setActive();

    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glClearDepth(100.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    set_zoom(zoom_);
    rotate(rotation_);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    for (auto& square : m_squares) {
        square.draw(window_);
    }
}


/////////////////CubeJob///////////////////////
CubeJob::CubeJob()
    : WindowJob("Cube", sf::ContextSettings(24)) {
    init_job();

}


void CubeJob::init_job() {
   
}

int CubeJob::process_events() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            m_window.close();
            return END_FLAG;
        }
        if (event.type == sf::Event::MouseWheelMoved) {
            m_zoom += event.mouseWheel.delta * 5;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!m_is_left_pressed) m_start_press_pos = sf::Mouse::getPosition();
        m_is_left_pressed = true;
        m_new_cube_rotation.x = -(m_start_press_pos.y - sf::Mouse::getPosition().y) / 2.f + m_last_cube_rotation.x;
        m_new_cube_rotation.y = -(m_start_press_pos.x - sf::Mouse::getPosition().x) / 2.f + m_last_cube_rotation.y;
    }
    else {
        m_last_cube_rotation = m_new_cube_rotation;
        m_is_left_pressed = false;
    }

    return CONTINUE_FLAG;
}

int CubeJob::update() {
    static int cc = 0;
    bool returning_flag = CONTINUE_FLAG;
    ImGui::SFML::Update(m_window, m_deltaClock.restart());

    ImGui::Begin("Menu");
    if (ImGui::Button("Close")) {
        returning_flag = END_FLAG;
    }
    ImGui::End();
    return returning_flag;
}

int CubeJob::render() {
    m_window.setActive();
    glClearColor(0., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    m_cube.draw(m_window, m_new_cube_rotation, m_zoom);

    ImGui::SFML::Render(m_window);
    m_window.display();
    return CONTINUE_FLAG;
}