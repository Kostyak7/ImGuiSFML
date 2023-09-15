#include "IJobManager.h"


void IJobManager::add_job(const std::shared_ptr<IWindowJob>& ptr_new_job_) {
    m_job_list_to_add.push_back(ptr_new_job_);
}


void IJobManager::apply_deferred_job() {
    for (const auto& job : m_job_list_to_add) {
        if (job) m_job_list.push_back(job);
    }
    m_job_list_to_add.clear();
}