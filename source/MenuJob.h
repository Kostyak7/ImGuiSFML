#pragma once

#include "IJobManager.h"
#include "Console.h"

csys::ItemLog& operator<<(csys::ItemLog& log, sf::Color& color_);

class MenuJob : public WindowJob {
public:
    MenuJob(IJobManager* ptr_job_manager_);

    void set_background_color(const sf::Color& color_);

    Console console;
private:
    IJobManager* m_ptr_job_manager;
    void init_job() override;
    sf::Color m_bkg_color{ sf::Color::Black };
    ImVec4 m_bkg_color_vec4{ 0.25f, 0.25f, 0.25f, 1.00f };

    int update() override;
    int render() override;
};