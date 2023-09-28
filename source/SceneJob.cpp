#include "SceneJob.h"
#include "imgui.h"
#include "imgui-sfml.h"
#include "config.h"

SceneJob::SceneJob() {
    init_job();
}


void SceneJob::init_job() {

}

int SceneJob::process_events() {
    if (!m_is_set_projection) {
        glFrustum(-1, 1, -1, 1, 2, 100);
        m_is_set_projection = true;
    }
    sf::Event event;
    while (WindowHandler::window().pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            WindowHandler::Instance().close();
            return END_FLAG;
        }
        if (event.type == sf::Event::MouseWheelMoved) {
            m_camera.addZoomDelta(event.mouseWheel.delta);
        }
    }
    return CONTINUE_FLAG;
}

int SceneJob::update() {
    bool returning_flag = CONTINUE_FLAG;
    ImGui::SFML::Update(WindowHandler::window(), m_clock.restart());

    m_camera.update(WindowHandler::window());
    m_model.update();

    return returning_flag;
}

int SceneJob::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glClearDepth(24.f);
    
    m_camera.render(WindowHandler::window());
    m_grid.draw(WindowHandler::window());
    m_model.draw(WindowHandler::window());

    glPopMatrix();

    WindowHandler::window().pushGLStates();
    ImGui::SFML::Render(WindowHandler::window());
    WindowHandler::window().popGLStates();

    WindowHandler::window().display();
    return CONTINUE_FLAG;
}