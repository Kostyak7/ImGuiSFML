#include "PyramidJob.h"

#define GL_CLAMP_TO_EDGE 0x812F


static GLuint LoadTexture(const std::string& name_) {
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


/////////////////Cube///////////////////////
Pyramid::Pyramid()
    : m_box(LoadTexture("mike.png")) {

}

Pyramid::~Pyramid() {
    glDeleteTextures(1, &m_box);
}


void Pyramid::draw(sf::RenderWindow& window_, float rotate_x_, float rotate_y_) {
    float time = m_clock.getElapsedTime().asSeconds() * 10;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -100);
    //glRotatef(time, 50, 50, 0);
    glRotatef(rotate_x_, 1., 0., 0.);
    glRotatef(rotate_y_, 0., 1., 0.);

    auto size = m_size;

    glBindTexture(GL_TEXTURE_2D, m_box);
    glBegin(GL_QUADS);
    //front
    glTexCoord2f(0, 0);   glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 0);   glVertex3f(size, -size, -size);
    glTexCoord2f(1, 1);   glVertex3f(size, size, -size);
    glTexCoord2f(0, 1);   glVertex3f(-size, size, -size);
    glEnd();

    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, size);
    glTexCoord2f(0, 1); glVertex3f(size, size, size);
    glEnd();

    glBegin(GL_QUADS);
    //left
    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, size, size);
    glEnd();

    glBegin(GL_QUADS);
    //right
    glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
    glTexCoord2f(1, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(size, size, size);
    glTexCoord2f(0, 1); glVertex3f(size, size, -size);
    glEnd();

    glBegin(GL_QUADS);
    //bottom
    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
    glEnd();

    glBegin(GL_QUADS);
    //top  		
    glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
    glTexCoord2f(1, 0); glVertex3f(size, size, -size);
    glTexCoord2f(1, 1); glVertex3f(size, size, size);
    glTexCoord2f(0, 1); glVertex3f(-size, size, size);
    glEnd();

}


/////////////////CubeJob///////////////////////
PyramidJob::PyramidJob()
    : WindowJob("Pyramid", sf::ContextSettings(24)) {
    init_job();

}


void PyramidJob::init_job() {
    m_window.setActive();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glClearDepth(100.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    glEnable(GL_TEXTURE_2D);
}

int PyramidJob::process_events() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            m_window.close();
            return END_FLAG;
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

int PyramidJob::update() {
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

int PyramidJob::render() {
    m_window.setActive();
    glClearColor(0., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    init_job();

    m_pyramid.draw(m_window, m_new_cube_rotation.x, m_new_cube_rotation.y);

    ImGui::SFML::Render(m_window);
    m_window.display();
    return CONTINUE_FLAG;
}