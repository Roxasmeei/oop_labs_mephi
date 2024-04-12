#include <ContributingWorker.h>

ContributingWorker::ContributingWorker(int worker_type, double _contribution) {
    switch (worker_type) {
        case (STANDARD_WORKER) :
            info = std::make_unique<StandardWorkerDescriptor>((size_t) _contribution);
            break;

        case (MASTER) :
            info = std::make_unique<MasterDescriptor>(_contribution);
            break;

    }
}

ContributingWorker::ContributingWorker(const BaseDescriptor &baseDescriptor) {
    if (baseDescriptor.IsMaster()) info = std::make_unique<MasterDescriptor>(baseDescriptor);
    else if (baseDescriptor.IsStandardWorker()) info = std::make_unique<StandardWorkerDescriptor>(baseDescriptor);
}

ContributingWorker::ContributingWorker(std::string &name, size_t age, int worker_type, double _contribution)
        : ContributingWorker(worker_type, _contribution) {
    this->name = std::move(name);
    this->age = age;
}

//bool ContributingWorker::raiseQualification() {
//
//    if (info == nullptr) return false;
//
//    if (info->IsMaster()) return false;
//
//    else if (info->IsStandardWorker()) {
//        double newContribution = 1 + (info->GetContribution() - 1) / 2;
//        info = std::make_unique<MasterDescriptor>(newContribution);
//    }
//
//    return true;
//}


