#include "JobManager.h"


unsigned int JobManager::check_job(Job* job_) {
	for (auto it = m_jobs.begin(); it != m_jobs.end(); ++it) {
		if (job_ == it->second.get()) {
			return it->first;
		}
	}
	return 0;
}

void JobManager::add_job(std::shared_ptr<Job> job_, unsigned int priorety_) {
	if (!priorety_) {
		if (check_job(job_.get())) { kill_job(job_.get()); }
		return;
	}
	if (!m_jobs.size() || m_jobs.front().first <= priorety_) {
		m_jobs.emplace_front(std::pair{ priorety_, job_ });
		return;
	}
	if (m_jobs.back().first >= priorety_) {
		m_jobs.emplace_back(std::pair{ priorety_, job_ });
		return;
	}
	for (auto it = m_jobs.begin(); it != m_jobs.end(); ++it) {
		if (it->first <= priorety_) {
			m_jobs.emplace(it, std::pair{ priorety_, job_ });
			return;
		}
	}
}

void JobManager::kill_job(Job* job_) {
	for (auto it = m_jobs.begin(); it != m_jobs.end(); ++it) {
		if (job_ == it->second.get()) {
			m_jobs.erase(it);
			return;
		}
	}
}

void JobManager::set_job_priorety(Job* job_, unsigned int new_priorety_) {
	if (new_priorety_) { add_job(std::shared_ptr<Job>(job_), new_priorety_); }
	for (auto it = m_jobs.begin(); it != m_jobs.end(); ++it) {
		if (job_ == it->second.get() && it->first != new_priorety_) {
			m_jobs.erase(it);
			return;
		}
	}
}