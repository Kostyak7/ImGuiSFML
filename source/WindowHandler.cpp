#include "WindowHandler.h"
#include "config.h"
#include <glad/glad.h>
#include "imgui.h"
#include "imgui-sfml.h"


WindowHandler::WindowHandler()
    : m_window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), DEFAULT_WINDOW_TITLE, sf::Style::Default, DEFAULT_CONTEXT_SETTINGS) {
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(60);
    m_window.setActive();

    gladLoadGL();

    m_window.pushGLStates();
    ImGui::SFML::Init(m_window);

    m_window.resetGLStates();
    m_window.popGLStates();
}

WindowHandler::~WindowHandler() {

}


WindowHandler& WindowHandler::Instance() {
    static WindowHandler me;
    return me;
}

sf::RenderWindow& WindowHandler::window() {
    return WindowHandler::Instance().m_window;
}
