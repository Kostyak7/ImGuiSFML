#pragma once

#include "Job.h"
#include "Grid.h"
#include "Camera.h"
#include "Model.h"


class SceneJob : public WindowJob {
public:
	SceneJob();
protected:
	bool m_is_set_projection = false;
	Grid m_grid;
	Camera m_camera;
	Model m_model;

	void init_job() override;
	int process_events() override;
	int update() override;
	int render() override;
};