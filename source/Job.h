#pragma once

#include "WindowHandler.h"
#include <memory>


class JobManager;

class Job {
public:
	Job() = default;
	virtual ~Job() = default;

	virtual void kill();
	virtual int do_step();
protected:
	virtual void init_job();
};


class WindowJob : public Job {
	int do_step() override;
protected:
	sf::Clock m_clock;

	virtual int process_events();
	virtual int update();
	virtual int render();
};