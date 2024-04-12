#pragma once


#define STANDARD_WORKER_MAX_CONTRIBUTION 10
#define STANDARD_WORKER_MIN_CONTRIBUTION 1 // константы внутри класса (по-хорошему меняться долэжно)


class StandardWorkerDescriptor : public BaseDescriptor {
private:
    size_t contribution;

public:

    StandardWorkerDescriptor() {
        srand((unsigned) time(nullptr)); // мб nullptr замени на NULL; рандом c++ использовать
        contribution = rand() % STANDARD_WORKER_MAX_CONTRIBUTION + STANDARD_WORKER_MIN_CONTRIBUTION;
    } // Убери ранлом отсюда


    explicit StandardWorkerDescriptor(size_t _contribution) {
        if (_contribution > STANDARD_WORKER_MAX_CONTRIBUTION || _contribution < STANDARD_WORKER_MIN_CONTRIBUTION)
            throw std::invalid_argument("Invalid master contribution argument");

        contribution = _contribution;
    }

    explicit StandardWorkerDescriptor(const BaseDescriptor &_descriptor) {

        if (_descriptor.IsMaster()) {
            double descriptorContribution = _descriptor.GetContribution();
            contribution = (descriptorContribution == STANDARD_WORKER_MIN_CONTRIBUTION)
                           ? STANDARD_WORKER_MIN_CONTRIBUTION : (size_t) descriptorContribution * 2;
        } else if (_descriptor.IsStandardWorker()) {
            contribution = (size_t) _descriptor.GetContribution();
        }

    }

    [[nodiscard]] bool IsStandardWorker() const override { return true; }

    [[nodiscard]] bool IsMaster() const override { return false; }

    [[nodiscard]] double GetContribution() const override { return (double) contribution; } // у аддитивного храни double

    void SetContribution(double _contribution) override {
        if (_contribution > STANDARD_WORKER_MAX_CONTRIBUTION || _contribution < STANDARD_WORKER_MIN_CONTRIBUTION)
            throw std::invalid_argument("Invalid master contribution argument");

        contribution = (size_t) _contribution;
    }

};