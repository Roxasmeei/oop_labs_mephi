#pragma once


#include <Worker.h>

class BrigadeLeader : public Worker {

public:

    BrigadeLeader() : Worker() {}

    explicit BrigadeLeader(size_t _age) : Worker() {
        age = _age;
    }

    BrigadeLeader(std::string &_name, size_t _age) : Worker(_name, _age) {}

    double WorkerEffectiveness() override {return 0;}


    ~BrigadeLeader() override = default;




};


