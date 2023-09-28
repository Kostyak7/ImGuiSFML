#include "Application.h"
#include "config.h"
#include "imgui.h"
#include "imgui-SFML.h"


/////////////Job//////////////////
void Job::kill() {
	Application::app().kill_job(this);
}

int Job::do_step() {
    return CONTINUE_FLAG;
}


/////////////WindowJob//////////////////
int WindowJob::do_step() {
    ImGui::SFML::SetCurrentWindow(WindowHandler::window());

    int process_events_res = process_events();
    int update_res = update();
    int render_res = render();

    if (process_events_res == END_FLAG ||
        update_res == END_FLAG ||
        render_res == END_FLAG
        ) {
        return END_FLAG;
    }

    return CONTINUE_FLAG;
}

void Job::init_job() {

}

int WindowJob::process_events() {
    sf::Event event;
    while (WindowHandler::window().pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            WindowHandler::Instance().close();
            return END_FLAG;
        }
    }
    return CONTINUE_FLAG;
}

int WindowJob::update() {
    ImGui::SFML::Update(WindowHandler::window(), m_clock.restart());
    return CONTINUE_FLAG;
}

int WindowJob::render() {
    WindowHandler::window().clear(DEFAULT_BACKGROUND_COLOR);
    WindowHandler::window().pushGLStates();
    ImGui::SFML::Render(WindowHandler::window());
    WindowHandler::window().popGLStates();
    WindowHandler::window().display();
    return CONTINUE_FLAG;
}