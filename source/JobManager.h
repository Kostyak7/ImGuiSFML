#pragma once

#include "Job.h"
#include <list>


class JobManager {
public:
	JobManager() = default;
	virtual ~JobManager() = default;

	virtual unsigned int check_job(Job* job_);
	virtual void add_job(std::shared_ptr<Job> job_, unsigned int priorety_);
	virtual void kill_job(Job* job_);
	virtual void set_job_priorety(Job* job_, unsigned int new_priorety_);
protected:
	std::list<std::pair<unsigned int, std::shared_ptr<Job>>> m_jobs;
};