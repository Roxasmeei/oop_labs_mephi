#pragma once

#include <BaseDescriptor.h>
#include <random>


#define MASTER_MAX_CONTRIBUTION 5
#define MASTER_MIN_CONTRIBUTION 1


class MasterDescriptor : public BaseDescriptor {
private:
    double contribution;

public:

    MasterDescriptor() {
        srand((unsigned) time(NULL));
        contribution = rand() % MASTER_MAX_CONTRIBUTION + MASTER_MIN_CONTRIBUTION;
    }


    explicit MasterDescriptor(double _contribution) {
        if (_contribution > MASTER_MAX_CONTRIBUTION || _contribution < MASTER_MIN_CONTRIBUTION)
            throw std::invalid_argument("Invalid master contribution argument");

        contribution = _contribution;
    }


    explicit MasterDescriptor(const BaseDescriptor &_descriptor) {

        if (_descriptor.IsStandardWorker()) {
            double descriptorContribution = _descriptor.GetContribution();
            contribution = (descriptorContribution == MASTER_MIN_CONTRIBUTION) ? MASTER_MIN_CONTRIBUTION :
                           descriptorContribution / 2;
        } else if (_descriptor.IsMaster()) {
            contribution = _descriptor.GetContribution();

        }

    }


    bool IsStandardWorker() const override { return false; }

    bool IsMaster() const override { return true; }

    double GetContribution() const override { return contribution; }

    void SetContribution(double _contribution) override {
        if (_contribution > MASTER_MAX_CONTRIBUTION || _contribution < MASTER_MIN_CONTRIBUTION)
            throw std::invalid_argument("Invalid master contribution argument");

        contribution = _contribution;
    }
};