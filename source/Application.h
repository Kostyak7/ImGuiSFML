#pragma once

#include "JobManager.h"


class Application : public JobManager {
public:
	~Application();

	static Application& app();
	int run();
private:
	int job_executer();
	void init_application();

	Application();
	Application(const Application& other_) = delete;
	Application& operator=(const Application&) = delete;
};