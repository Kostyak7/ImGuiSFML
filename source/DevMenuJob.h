#pragma once

#include "Job.h"


class DevMenuJob : public WindowJob {
public:
	DevMenuJob();
private:
	void init_job() override;
	int update() override;
	int render();
};