#pragma once

#include "imgui.h"
#include "imgui-sfml.h"

#include "config.h"

#include <memory>


class IWindowJob {
public:
    IWindowJob(const std::string& title_, const sf::ContextSettings& settings_)
        : m_window(DEFAULT_VIDEO_MODE, title_, sf::Style::Default, settings_) {}

    virtual int do_step() = 0;

protected:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    virtual void init_job() = 0;

    virtual int process_events() = 0;
    virtual int update() = 0;
    virtual int render() = 0;
};


class WindowJob : public IWindowJob {
public:
    WindowJob(const std::string& title_);
    WindowJob(const std::string& title_, const sf::ContextSettings& settings_);

    int do_step() override;
protected:
    void init_job() override;

    int process_events() override;
    int update() override;
    int render() override;
};