#include "DevMenuJob.h"
#include "SceneJob.h"
#include "Application.h"
#include "imgui.h"
#include "imgui-sfml.h"
#include "config.h"


DevMenuJob::DevMenuJob() {
	init_job();
}


void DevMenuJob::init_job() {

}

int DevMenuJob::update() {
    bool returning_flag = CONTINUE_FLAG;
    ImGui::SFML::Update(WindowHandler::window(), m_clock.restart());

    ImGui::Begin("Menu");
    
    if (ImGui::Button("Show scene_1")) {
        Application::app().add_job(std::make_shared<SceneJob>());
        returning_flag = END_FLAG;
    }

    if (ImGui::Button("Console")) {
        //console.activate();
    }

    if (ImGui::Button("Close")) {
        WindowHandler::Instance().close();
        returning_flag = END_FLAG;
    }
    ImGui::End();
	return returning_flag;
}

int DevMenuJob::render() {
	return WindowJob::render();
}