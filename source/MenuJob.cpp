#include "MenuJob.h"
#include "CubeJob.h"
#include "PyramidJob.h"


MenuJob::MenuJob(IJobManager* ptr_job_manager_) 
    : WindowJob("Main menu"), m_ptr_job_manager(ptr_job_manager_) {
    init_job();
}

//csys::ItemLog& operator<<(csys::ItemLog& log, sf::Color& color_) {
//    log << "sf::Color: [" << color_.r << ", "
//        << color_.g << ", "
//        << color_.b << ", "
//        << color_.a << "]";
//    return log;
//}
//static void color_setter(sf::Color& color_, const std::vector<int>& vec_) {
//    if (vec_.size() < 4) return;
//
//    color_.r = vec_[0];
//    color_.g = vec_[1];
//    color_.b = vec_[2];
//    color_.a = vec_[3];
//}

csys::ItemLog& operator<<(csys::ItemLog& log, ImVec4& vec)
{
    log << "ImVec4: [" << vec.x << ", "
        << vec.y << ", "
        << vec.z << ", "
        << vec.w << "]";
    return log;
}

csys::ItemLog& operator<<(csys::ItemLog& log, MenuJob& job_) {
    log << "MenuJob";
    return log;
}

void imvec4_setter(ImVec4& my_type, std::vector<int> vec)
{
    if (vec.size() < 4) return;

    my_type.x = vec[0] / 255.f;
    my_type.y = vec[1] / 255.f;
    my_type.z = vec[2] / 255.f;
    my_type.w = vec[3] / 255.f;
}

void job_color_setter(MenuJob& job_, std::vector<int> vec) {
    if (vec.size() < 3) return;
    job_.set_background_color(sf::Color(vec[0], vec[1], vec[2]));
}


void MenuJob::init_job() {
    console().System().RegisterCommand("say_hello", "call this command if you want to say hello",
        [this]() {
            this->console().System().Log(csys::ItemType::INFO) << "Hello!!! I'm console" << csys::endl;
        });
    console().System().RegisterVariable("background_color", *this, job_color_setter);
}

void MenuJob::set_background_color(const sf::Color& color_) {
    m_bkg_color = color_;
}

int MenuJob::update() {
    bool returning_flag = CONTINUE_FLAG;
    ImGui::SFML::Update(m_window, m_deltaClock.restart());

    ImGui::Begin("Menu");
    if (ImGui::Button("Add Saul window")) {
        m_ptr_job_manager->add_job(std::make_shared<CubeJob>());
        ImGui::SFML::SetCurrentWindow(m_window);
    }

    if (ImGui::Button("Add Mike window")) {
        m_ptr_job_manager->add_job(std::make_shared<PyramidJob>());
        ImGui::SFML::SetCurrentWindow(m_window);
    }

    if (ImGui::Button("Show console")) {
        console.activate();
    }

    if (ImGui::Button("Close")) {
        returning_flag = END_FLAG;
    }

    ImGui::End();

    return returning_flag;
}

int MenuJob::render() {
    m_window.clear(m_bkg_color);

    if (console.is_active()) {
        console().Draw();
    }

    ImGui::SFML::Render(m_window);
    m_window.display();
    return CONTINUE_FLAG;
}
