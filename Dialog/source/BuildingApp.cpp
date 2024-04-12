#pragma once

#include <BuidingApp.h>


bool BuildingApp::addWorkingSite(const std::shared_ptr<WorkingSite> &newWorkingSite) {
    if (newWorkingSite == nullptr) return false;

    workingSites.push_back(newWorkingSite);
    return true;
}




void BuildingAppShow::ShowBuildingApp(const std::vector<std::shared_ptr<WorkingSite>> &ConstructionSites) {
    system("cls");

    size_t k = 0;
    for (const auto &tmp: ConstructionSites) {
        std::cout << "[" << ++k << \"]\n";
        WorkingSiteShow::ShowWorkingSite(*tmp);
        std::cout << std::endl;
    }

    std::cout << "\n\n\n";
}

void BuildingAppShow::ShowBuildingApp(std::vector<std::shared_ptr<WorkingSite>> &workingSites, size_t &maxRange,
                                      std::vector<size_t> &indexesOfWorkingSites) {
    system("cls");


    size_t t = 0;

    size_t num = 0;
    for (const auto &tmp: workingSites) {
        if (!tmp->hasBrigades()) continue;

        num++;

    }


    if (num == 0) {
        std::cout << "There are no working sites\n";
        return;
    } else {

        std::cout << "There are " << num << " construction sites\n";

        size_t t = 0;
        size_t k = 0;


        for (const auto &tmp: workingSites) {

            if (!tmp->hasBrigades()) continue;

            std::cout << "[" << ++k << "]\n";
            WorkingSiteShow::ShowWorkingSite(*tmp);
            std::cout << std::endl;
            indexesOfWorkingSites.push_back(t);
            t++;
        }

        maxRange = k;
    }
    std::cout << "\n\n\n";
}
