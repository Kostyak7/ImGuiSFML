#include "WindowJob.h"


WindowJob::WindowJob(const std::string& title_)
    : IWindowJob(title_, sf::ContextSettings()) {
    init_job();
}

WindowJob::WindowJob(const std::string& title_, const sf::ContextSettings& settings_)
    : IWindowJob(title_, settings_) {
    init_job();
}

int WindowJob::do_step() {
    ImGui::SFML::SetCurrentWindow(m_window);
    
    if (
        process_events() == END_FLAG ||
        update() == END_FLAG ||
        render() == END_FLAG
        ) {
        ImGui::SFML::Shutdown(m_window);
        return END_FLAG;
    }

    return CONTINUE_FLAG;
}

void WindowJob::init_job() {
    m_window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(m_window);
}

int WindowJob::process_events() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            m_window.close();
            return END_FLAG;
        }
    }
    return CONTINUE_FLAG;
}

int WindowJob::update() {
    ImGui::SFML::Update(m_window, m_deltaClock.restart());
    return CONTINUE_FLAG;
}

int WindowJob::render() {
    m_window.clear(DEFAULT_BACKGROUND_COLOR);
    ImGui::SFML::Render(m_window);
    m_window.display();
    return CONTINUE_FLAG;
}
