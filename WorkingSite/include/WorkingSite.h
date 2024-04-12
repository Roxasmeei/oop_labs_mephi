#pragma once

#include <Brigade.h>

#include <utility>


class WorkingSite {

private:

    std::string nameOfObject = "Not defined";
    double volumeOfWork = 0; // Overall
    double productivity = 0; // per day
    std::vector<std::shared_ptr<Brigade>> workingBrigades; // working brigades

//Constructors
    double curVolumeOfWork = volumeOfWork;// work left (Вернуть) тут сложно

    friend class WorkingSiteShow;


private:

//Private Methods
    void setProductivity(double num) { productivity = num; }


public:

    explicit WorkingSite(std::string name, double volume) : nameOfObject(std::move(name)),
                                                            volumeOfWork(volume) {}; // лишнее копирование строки


public:
//Getters and Setters
    void updateCurVolume(double num) { curVolumeOfWork -= num; };

    void currentVolume(double num) { curVolumeOfWork = num; }

    double getCurVolume() const { return curVolumeOfWork; }

    [[nodiscard]] double getVolumeOfWork() const { return volumeOfWork; }

    [[nodiscard]] double getProductivity();  // тригер при любой возможности

    void setVolumeOfWork(double num) { volumeOfWork = num; }

    [[nodiscard]] size_t getAmountOfBrigades() const { return workingBrigades.size(); }

//    void UpdateCurVolumeWork() { (double)curVolumeOfWork - productivity;}

    std::string &getNameOfWorkingSite() { return nameOfObject; } // почему не конст ссылка и метод тоже

    std::vector<std::shared_ptr<Brigade>> &getWorkingBrigades() { return workingBrigades; } // инкапсулировать веткор

    bool hasBrigades() { return !workingBrigades.empty(); }


public:
//Methods

    std::string &determineProblemBrigade(); // по ссылке

    [[nodiscard]] bool WillBeCompletedInADay();

    std::shared_ptr<Brigade> &findBrigadeById(const std::string &id);

    void addBrigade(const std::shared_ptr<Brigade> &brigade);

    std::shared_ptr<Brigade> &getBrigade(size_t ind);


};


class WorkingSiteShow {

public:

    void static ShowWorkingSite(const WorkingSite &);

};