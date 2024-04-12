#pragma once

#include <Worker.h>
#include <Descriptors.h>


#define STANDARD_WORKER 1
#define MASTER 2


class ContributingWorker : public Worker {
private:

    std::unique_ptr<BaseDescriptor> info;

    friend class BrigadeLeader;

public:


    explicit ContributingWorker(const BaseDescriptor &baseDescriptor);

    ContributingWorker(int worker_type, double _contribution);

    ContributingWorker(std::string &, size_t, int worker_type, double _contribution);

    ~ContributingWorker() override = default;

    std::unique_ptr<BaseDescriptor> &getDescriptor() { return info; }

    double WorkerEffectiveness() override { return info->GetContribution(); }

};

