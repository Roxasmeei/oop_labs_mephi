#pragma once


#include <Menu.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


void GenerateRandomRelationShips(std::vector<std::shared_ptr<WorkingSite>> &workingSites) {

    if (workingSites.empty()) { std::cout << "Nothing to simulate\n"; };


    for (const auto &site: workingSites) {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (const auto &brigade: site->getWorkingBrigades()) {
            if (!brigade) continue;

            if (brigade->getAmountOfPeople() < 2) continue;

            auto team = brigade->get_table();

            std::uniform_int_distribution<int> distribution(0, team.getTableSize() - 1);

            size_t ind1 = distribution(gen);
            size_t ind2 = distribution(gen);

            Worker::makeFriends(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);


            ind1 = distribution(gen);
            ind2 = distribution(gen);


            Worker::makeEnemies(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);

        }
    }
}


int Dialog::handleChoice(int choice) {
    switch (choice) {
        case 0:
            std::cout << "Program is over.\n";
            return 0;
        case 1:
            BuildingAppShow::ShowBuildingApp(buildingApp.getWorkingSites());
            return 1;
        case 2:
            createWorkingSite();
            return 2;
        case 3:
            createBrigade();
            return 3;
        case 4:
            createWorker();
            return 4;
        case 5:
            deleteWorker();
            return 5;
        case 6:
            calculateProductivity();
            return 6;
        case 7:
            WorkingDaySimulation();
            return 7;
        default:
            std::cout << "Invalid choice. Try again.\n";
            return 100;
    }
}

//void Dialog::WorkingDaySimulation() {
//
//
//    system("cls");
//
//    std::vector<std::shared_ptr<WorkingSite>> workingSites = buildingApp.getWorkingSites();
//
//
//    GenerateRandomRelationShips(workingSites);
//
//
//    for (const auto &site: workingSites) {
//
//
//        site->curVolumeOfWork = (site->curVolumeOfWork > site->getProductivity()) ? site->curVolumeOfWork -
//                                                                                    site->getProductivity() : 0;
//
//        WorkingSiteShow::ShowWorkingSite(*site);
//        std::cout << "\n";
//
//    }
//
//
//}

void simulateBrigade(std::shared_ptr<Brigade> brigade) {
    if (brigade) {
        std::random_device rd;
        std::mt19937 gen(rd());

        if (brigade->getAmountOfPeople() < 2) return;

        auto team = brigade->get_table();

        std::uniform_int_distribution<int> distribution(0, team.getTableSize() - 1);

        size_t ind1 = distribution(gen);
        size_t ind2 = distribution(gen);

        Worker::makeFriends(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);


        ind1 = distribution(gen);
        ind2 = distribution(gen);


        Worker::makeEnemies(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);
    }
}

void simulateWorkingSite(std::shared_ptr<WorkingSite> site, std::mutex &siteMutex) {

    std::lock_guard<std::mutex> lock(siteMutex);


    std::vector<std::thread> brigadeThreads;
    for (const auto &brigade: site->getWorkingBrigades()) {
        brigadeThreads.emplace_back(simulateBrigade, brigade);
    }


    for (auto &thread: brigadeThreads) {
        thread.join();
    }


    double num = (site->getCurVolume() > site->getProductivity()) ?
                 site->getCurVolume() - site->getProductivity() : 0;

    site->currentVolume(num);

    WorkingSiteShow::ShowWorkingSite(*site);
    std::cout << "\n";
}












void Dialog::WorkingDaySimulation() {
    system("cls");

    std::vector<std::shared_ptr<WorkingSite>> workingSites = buildingApp.getWorkingSites();

    if (workingSites.empty()) {
        std::cout << "Nothing to simulate\n";
        return;
    }


    std::vector<std::mutex> siteMutexes(workingSites.size());


    std::vector<std::thread> siteThreads;
    for (size_t i = 0; i < workingSites.size(); ++i) {
        siteThreads.emplace_back(simulateWorkingSite, workingSites[i], std::ref(siteMutexes[i]));
    }


    for (auto &thread: siteThreads) {
        thread.join();
    }
}


void Dialog::findWeakConstructionSites() {

    system("cls");

    std::vector<std::shared_ptr<WorkingSite>> workingSites = buildingApp.getWorkingSites();

    size_t max = 0;

    size_t num = 0;
    size_t i = 0;


    for (const auto &site: workingSites) {
        size_t tmp = site->getCurVolume() / site->getProductivity();
        if (tmp > max) {
            max = tmp;
            num = i;
        }

        i++;
    }


    const auto &res = workingSites.at(num);


    std::cout << "The most problematic construction site: ";


}

void Dialog::calculateProductivity() {
    system("cls");

    size_t amountOfWorkingSites = buildingApp.getWorkingSitesNum();

    if (amountOfWorkingSites == 0) {
        std::cout << "Nobody works!\n";
        return;
    }

    std::vector<std::shared_ptr<WorkingSite>> workingSitesWithBrigades;
    std::vector<size_t> workingSitesIndexes;

    int i = -1;
    for (const auto &tmp: buildingApp.getWorkingSites()) {
        i++;
        if (tmp->getAmountOfBrigades() == 0) continue;
        else {
            workingSitesWithBrigades.push_back(tmp);
            workingSitesIndexes.push_back(i);
        }

    }

    int t = 0;
    for (const auto &tmp: workingSitesWithBrigades) {
        std::cout << t + 1 << ")\n";
        WorkingSiteShow::ShowWorkingSite(*tmp);
        t++;
    }

    size_t min = (workingSitesWithBrigades.empty()) ? 0 : 1;

    std::cout << "Choose working site [" << min << ";" << workingSitesWithBrigades.size() << "]: ";

    size_t choice = getNum<size_t>(min, workingSitesWithBrigades.size());


    std::vector<std::shared_ptr<Brigade>> BrigadesWithinWorkingSite = workingSitesWithBrigades.at(
            choice - 1)->getWorkingBrigades();

    system("cls");
    size_t BrigadeChoice = 0;
    size_t q = 0;
    size_t w = 0;

    std::vector<std::shared_ptr<Brigade>> brigades;
    std::vector<size_t> brigadesIndexes;
    for (const auto &tmp: BrigadesWithinWorkingSite) {
        w++;
        if (tmp->getCurBrigadeSize() == 0) continue;
        std::cout << "[" << ++q << "]\n";
        BrigadeShow::ShowBrigade(*tmp);
        std::cout << "\n";
        brigades.push_back(tmp);
        brigadesIndexes.push_back(w - 1);
    }

    if (brigades.empty()) {
        std::cout << "Nobody to delete\n";
        return;
    }

    std::cout << "Choose brigade [" << 1 << ";" << brigades.size() << "]";

    BrigadeChoice = getNum<size_t>(1, brigades.size());


    std::shared_ptr<Brigade> chosenBrigade = brigades.at(brigadesIndexes.at(BrigadeChoice - 1));

    system("cls");

    BrigadeShow::ShowBrigade(*chosenBrigade);


}

void Dialog::deleteWorker() {

    system("cls");

    size_t amountOfWorkingSites = buildingApp.getWorkingSitesNum();

    if (amountOfWorkingSites == 0) {
        std::cout << "Nobody works!\n";
        return;
    }

    std::vector<std::shared_ptr<WorkingSite>> workingSitesWithBrigades;
    std::vector<size_t> workingSitesIndexes;

    int i = -1;
    for (const auto &tmp: buildingApp.getWorkingSites()) {
        i++;
        if (tmp->getAmountOfBrigades() == 0) continue;
        else {
            workingSitesWithBrigades.push_back(tmp);
            workingSitesIndexes.push_back(i);
        }

    }

    int t = 0;
    for (const auto &tmp: workingSitesWithBrigades) {
        std::cout << t + 1 << ")\n";
        WorkingSiteShow::ShowWorkingSite(*tmp);
        t++;
    }

    size_t min = (workingSitesWithBrigades.empty()) ? 0 : 1;

    std::cout << "Choose working site [" << min << ";" << workingSitesWithBrigades.size() << "]: ";

    size_t choice = getNum<size_t>(min, workingSitesWithBrigades.size());


    std::vector<std::shared_ptr<Brigade>> BrigadesWithinWorkingSite = workingSitesWithBrigades.at(
            choice - 1)->getWorkingBrigades();

    system("cls");
    size_t BrigadeChoice = 0;
    size_t q = 0;
    size_t w = 0;

    std::vector<std::shared_ptr<Brigade>> brigades;
    std::vector<size_t> brigadesIndexes;
    for (const auto &tmp: BrigadesWithinWorkingSite) {
        w++;
        if (tmp->getCurBrigadeSize() == 0) continue;
        std::cout << "[" << ++q << "]\n";
//        tmp->showBrigade();
        BrigadeShow::ShowBrigade(*tmp);
        std::cout << "\n";
        brigades.push_back(tmp);
        brigadesIndexes.push_back(w - 1);
    }

    if (brigades.empty()) {
        std::cout << "Nobody to delete\n";
        return;
    }

    std::cout << "Choose brigade [" << 1 << ";" << brigades.size() << "]";

    BrigadeChoice = getNum<size_t>(1, brigades.size());


    std::shared_ptr<Brigade> chosenBrigade = brigades.at(brigadesIndexes.at(BrigadeChoice - 1));

    system("cls");


//    chosenBrigade->showBrigade();
    BrigadeShow::ShowBrigade(*chosenBrigade);

    std::string id;

    std::cout << "Type an ID of a person: ";

    std::cin >> id;

    if (chosenBrigade->fireWorker(id)) std::cout << "Worker has been deleted!\n";
    else std::cout << "There is no worker with such id\n";

}

void Dialog::createWorkingSite() {

    system("cls");

    std::string name;
    std::cout << "Enter new working site's name: ";
    std::cin >> name;

    std::cout << "Enter amount of work that should be done (unsigned num): ";
    size_t volume = getNum<size_t>(0, SIZE_MAX);

    std::shared_ptr<WorkingSite> newWorkingSite = std::make_shared<WorkingSite>(name, volume);

    system("cls");

    if (buildingApp.addWorkingSite(newWorkingSite)) std::cout << "New working site added successfully\n";
    else std::cout << "Adding new working site was failed\n";


}

void Dialog::createBrigade() {
    system("cls");

    size_t amountOfWorkingSites = buildingApp.getWorkingSitesNum();

    if (amountOfWorkingSites == 0) {
        std::cout << "You can't create brigade while you don't have working sites!\n";
        return;
    }


    std::cout << "Enter amount of workers in your future brigade: ";

    size_t numOfWorkers = getNum<size_t>(0, SIZE_MAX);

    std::shared_ptr<Brigade> newBrigade = std::make_shared<Brigade>(numOfWorkers);


    system("cls");

    BuildingAppShow::ShowBuildingApp(buildingApp.getWorkingSites());

    std::cout << "Select the working site you want to send a brigade to [" << 1 << "; "
              << buildingApp.getWorkingSitesNum()
              << "]: ";

    size_t choice = getNum<size_t>(1, buildingApp.getWorkingSitesNum());

    buildingApp.getWorkingSites()[choice - 1]->addBrigade(newBrigade);

    system("cls");

    std::cout << "Brigade was added on " << buildingApp.getWorkingSites()[choice - 1]->getNameOfWorkingSite()
              << " object\n";


}

bool Dialog::addBrigadeLeaderToSite() {
    std::string leaderName;
    std::cout << "What's name of brigade leader: ";
    std::cin >> leaderName;

    std::cout << "What's age of brigade leader: ";
    size_t leaderAge = getNum<size_t>(0, SIZE_MAX);

    std::shared_ptr<BrigadeLeader> leader = std::make_shared<BrigadeLeader>(leaderName, leaderAge);

    system("cls");

    size_t maxRange = 0;
    std::vector<size_t> WorkingSitesIndexes;

    BuildingAppShow::ShowBuildingApp(buildingApp.getWorkingSites(), maxRange, WorkingSitesIndexes);

    std::cout << "Choose place where brigade leader gonna work: ";
    size_t UserChoiceBrigLead = getNum<size_t>(1, maxRange + 1);


    std::shared_ptr<WorkingSite> placeOfWorkBrigLead = buildingApp.getWorkingSites().at(
            WorkingSitesIndexes.at(UserChoiceBrigLead - 1));


    system("cls");


    std::vector<size_t> BrigadeIndexesBrigLead;

    size_t i = 0;
    size_t t = -1;

    for (const auto &tmp: placeOfWorkBrigLead->getWorkingBrigades()) {
        t++;
        if (tmp->hasBrigadeLeader()) continue;
        std::cout << "[" << ++i << "]\n";
//        tmp->showStats();
        BrigadeShow::ShowBrigadeStats(*tmp);
        BrigadeIndexesBrigLead.push_back(t);
    }


    bool res = placeOfWorkBrigLead->getBrigade(BrigadeIndexesBrigLead[getNum<size_t>(1, i) - 1])->addBrigadeLeader(
            leader);


    return res;
}

bool Dialog::addMasterToSite() {

    std::string name;
    std::cout << "What's name of master: ";
    std::cin >> name;

    std::cout << "What's age of master: ";
    size_t age = getNum<size_t>(0, SIZE_MAX);

    std::cout << "What's his contribution (multiplicative [" << MASTER_MIN_CONTRIBUTION << ";"
              << MASTER_MAX_CONTRIBUTION << "]): ";
    double contribution = getNum<double>(MASTER_MIN_CONTRIBUTION, MASTER_MAX_CONTRIBUTION);


    std::shared_ptr<Worker> masterWorker = std::make_shared<ContributingWorker>(name, age,
                                                                                MASTER, contribution);

    system("cls");


//    buildingApp.ShowInfo();
    BuildingAppShow::ShowBuildingApp(buildingApp.getWorkingSites());


    std::cout << "Choose place where master gonna work: ";
    size_t UserChoice = getNum<size_t>(1, buildingApp.getWorkingSitesNum());


    std::shared_ptr<WorkingSite> placeOfWorkMaster = buildingApp.getWorkingSites()[UserChoice - 1];

    size_t i = 0;
    size_t t = -1;
    std::vector<size_t> BrigadeIndexesMaster;

    system("cls");

    for (const auto &tmp: placeOfWorkMaster->getWorkingBrigades()) {
        t++;
        if (tmp->getCurBrigadeSize() == tmp->getMaxBrigadeSize()) continue;
        std::cout << "[" << ++i << "]\n";
        BrigadeShow::ShowBrigade(*tmp);
        BrigadeIndexesMaster.push_back(t);
    }

    return placeOfWorkMaster->getBrigade(BrigadeIndexesMaster[getNum<size_t>(1, i) - 1])->addWorker(
            masterWorker);


}

bool Dialog::addStandardWorkerToSite() {
    std::string standardName;
    std::cout << "What's name of standard worker: ";
    std::cin >> standardName;

    std::cout << "What's age of standard worker: ";
    size_t standardAge = getNum<size_t>(0, SIZE_MAX);

    std::cout << "What's his contribution (additive [" << STANDARD_WORKER_MIN_CONTRIBUTION << ";"
              << STANDARD_WORKER_MAX_CONTRIBUTION << "]): ";
    size_t standardContribution = getNum<size_t>(STANDARD_WORKER_MIN_CONTRIBUTION,
                                                 STANDARD_WORKER_MAX_CONTRIBUTION);


    system("cls");
    std::shared_ptr<Worker> standard = std::make_shared<ContributingWorker>(standardName, standardAge,
                                                                            STANDARD_WORKER,
                                                                            standardContribution);


//    buildingApp.ShowInfo(); // потенциально перегрузи для раюочего
    BuildingAppShow::ShowBuildingApp(buildingApp.getWorkingSites());


    std::cout << "Choose place where standard worker gonna work: ";
    size_t UserChoice = getNum<size_t>(1, buildingApp.getWorkingSitesNum());


    std::shared_ptr<WorkingSite> placeOfWork = buildingApp.getWorkingSites()[UserChoice -
                                                                             1]; // working site


    system("cls");
    int i = 0;
    int t = -1;
    std::vector<size_t> BrigadeIndexes;

    std::cout << "Choose brigade in which standard worker gonna work:\n";

    for (const auto &tmp: placeOfWork->getWorkingBrigades()) {
        t += 1;
        if (tmp->getCurBrigadeSize() == tmp->getMaxBrigadeSize()) continue;
        std::cout << "[" << ++i << "]\n";
        BrigadeShow::ShowBrigade(*tmp);
        std::cout << "\n";
        BrigadeIndexes.push_back(t);
    }

//    system("cls");

    return placeOfWork->getBrigade(BrigadeIndexes[getNum<size_t>(1, i) - 1])->addWorker(standard);


}

void Dialog::createWorker() {

    system("cls");

    size_t amountOfWorkingSites = buildingApp.getWorkingSitesNum();

    bool IsItPossibleToFindPlaceForWorker = false;


    for (const auto &tmp: buildingApp.getWorkingSites()) {
        if (tmp->getAmountOfBrigades() > 0) IsItPossibleToFindPlaceForWorker = true;
    }

    if (amountOfWorkingSites == 0) {
        std::cout << "You won't be able to create a worker while you don't have neither working sites nor teams!\n";
        return;
    } else if (!IsItPossibleToFindPlaceForWorker) {
        std::cout << "You won't be able to create a worker while you don't have any brigades!\n";
        return;
    }


    std::cout << "What's a qualification of your worker?\n"
              << "1)Brigade Leader\n"
              << "2)Master\n"
              << "3)Standard Worker\n";

    size_t choice = getNum<size_t>(1, 3);

    system("cls");

    switch (choice) {
        case 1:
            if (addBrigadeLeaderToSite()) std::cout << "Brigade leader was added successfully\n";
            else std::cout << "We already have a leader on this construction site\n";
            break;
        case 2:
            if (addMasterToSite()) std::cout << "Master was added successfully\n";
            else std::cout << "Failed adding master\n";
            break;
        case 3:

            if (addStandardWorkerToSite()) std::cout << "Standard worker was added successfully\n";
            else std::cout << "Failed adding standard worker\n";
            break;
        default:
            std::cout << "Unable to identify workers qualification\n";
            return;
    }


}

void Dialog::start() {
    int choice = -1;


    while (choice != 0) {
        printMenu();
        std::cout << "Choose action (pick a number [" << MIN_MENU_CHOICE << ";" << MAX_MENU_CHOICE << "]): ";

        choice = handleChoice(getNum<int>(MIN_MENU_CHOICE, MAX_MENU_CHOICE));

    }
}
