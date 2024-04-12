#ifndef PROJECT_STANDARD_DESCRIPTOR_H
#define PROJECT_STANDARD_DESCRIPTOR_H


class BaseDescriptor {
public:


    [[nodiscard]] virtual bool IsStandardWorker() const = 0;

    [[nodiscard]] virtual bool IsMaster() const = 0;

    [[nodiscard]] virtual double GetContribution() const = 0;

    virtual void SetContribution(double newContribution) = 0;

};


#endif //PROJECT_STANDARDDESCRIPTOR_H
