#include "Application.h"


Application::Application() : IJobManager() {
    init_application();
}

Application::~Application() {
    ImGui::SFML::Shutdown();
}

int Application::run() {
    try {
        while (job_executer()) {
            apply_deferred_job();
        }
    }
    catch (...) {
        std::cout << "Unknown exception\n";
        return 1;
    }
    return 0;
}

int Application::job_executer() {
    for (auto it = m_job_list.begin(); it != m_job_list.end();) {
        if ((*it)->do_step() == END_FLAG) {
            it = m_job_list.erase(it);
        }
        else ++it;
    }
    return (m_job_list.empty()) ? END_FLAG : CONTINUE_FLAG;
}

void Application::init_application() {
    m_job_list.push_back(std::make_shared<MenuJob>(this));
}