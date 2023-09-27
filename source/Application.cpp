#include "Application.h"
#include "DevMenuJob.h"
#include "config.h"
#include "imgui.h"
#include "imgui-sfml.h"
#include <iostream>


Application::Application() {
	init_application();
}

Application::~Application() {
    ImGui::SFML::Shutdown(WindowHandler::window());
    ImGui::SFML::Shutdown();
}


Application& Application::app() {
	static Application app;
	return app;
}

int Application::run() {
    try {
        while (job_executer()) {
            if (WindowHandler::Instance().is_to_close()) {
                WindowHandler::window().close();
                break;
            }
        }
    }
    catch (...) {
        std::cout << "Unknown exception\n";
        return 1;
    }
    return 0;
}

int Application::job_executer() {
    for (auto it = m_jobs.begin(); it != m_jobs.end();) {
        if (it->second->do_step() == END_FLAG) {
            it = m_jobs.erase(it);
        }
        else ++it;
    }
    return (m_jobs.empty()) ? END_FLAG : CONTINUE_FLAG;
}

void Application::init_application() {
    add_job(std::make_shared<DevMenuJob>(), 100);
}
