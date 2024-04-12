#pragma once

#include <BuidingApp.h>

#define MIN_MENU_CHOICE 0
#define MAX_MENU_CHOICE 7


class Dialog {

private:
    BuildingApp buildingApp = BuildingApp();


private:
    void printMenu() {
        std::cout << "===== Menu =====\n"
                  << "0) Exit\n"
                  << "1) Show info\n"
                  << "2) Add WorkingSite\n"
                  << "3) Add Brigade\n"
                  << "4) Add Worker\n"
                  << "5) Fire Worker\n"
                  << "6) Productivity of a construction place\n"
                  << "7) Simulate day\n"
                  << "================\n";
    }


    int handleChoice(int choice);

    void WorkingDaySimulation();

    void findWeakConstructionSites();

    void calculateProductivity();

    void deleteWorker();

    void createWorkingSite();

    void createBrigade();

    bool addBrigadeLeaderToSite();

    bool addMasterToSite();

    bool addStandardWorkerToSite();

    void createWorker();


public:

    void start();

};