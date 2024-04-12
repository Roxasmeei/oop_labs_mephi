#pragma once

#include <Worker.h>
#include <ContributingWorker.h>
#include <BrigadeLeader.h>
#include <Brigade.h>
#include <WorkingSite.h>
#include <Utils.h>
#include <conio.h>


class BuildingApp {

private:


    std::vector<std::shared_ptr<WorkingSite>> workingSites;

    friend class BuildingAppShow;


public:

    BuildingApp() = default;

    explicit BuildingApp(const std::vector<std::shared_ptr<WorkingSite>> &initialize_vec) : workingSites(
            initialize_vec) {};

    bool addWorkingSite(const std::shared_ptr<WorkingSite> &newWorkingSite);

    [[nodiscard]] size_t getWorkingSitesNum() const { return workingSites.size(); }

    std::vector<std::shared_ptr<WorkingSite>> &getWorkingSites() { return workingSites; }


};


class BuildingAppShow {

public:


    void static ShowBuildingApp(const std::vector<std::shared_ptr<WorkingSite>> &);

    void static ShowBuildingApp(std::vector<std::shared_ptr<WorkingSite>> &, size_t &maxRange,
                                std::vector<size_t> &indexesOfWorkingSites);


};