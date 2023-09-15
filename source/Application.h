#pragma once

#include "MenuJob.h"
#include <iostream>


class Application : public IJobManager {
public:
    Application();
    ~Application();

    int run();
private:
    int job_executer();

    void init_application();
};