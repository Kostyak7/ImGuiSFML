#pragma once

#include "WindowJob.h"
#include <list>


class IJobManager {
public:
    IJobManager() = default;
    ~IJobManager() = default;

    virtual void add_job(const std::shared_ptr<IWindowJob>& ptr_new_job_);
protected:
    std::list<std::shared_ptr<IWindowJob>> m_job_list;
    std::list<std::shared_ptr<IWindowJob>> m_job_list_to_add;

    virtual void apply_deferred_job();
};