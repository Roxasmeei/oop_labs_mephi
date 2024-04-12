#include <Brigade.h>
#include <Utils.h>


bool Brigade::addBrigadeLeader(std::shared_ptr<BrigadeLeader> &newLeader) {

    std::string id = newLeader->getUniqueNum();
    id.replace(0, getBrigadeId().length(), getBrigadeId());
    newLeader->setUniqueNum(id);

    if (leader || !newLeader) return false;
    leader = std::move(newLeader);
    return true;
}

bool Brigade::redirectBrigadeLeader(Brigade &newPlaceForLeader) {
    return newPlaceForLeader.addBrigadeLeader(leader);
}

bool Brigade::addWorker(std::shared_ptr<Worker> &newWorker) {

    if (!newWorker) { return false; }

    std::string id = newWorker->getUniqueNum();
    id.replace(0, getBrigadeId().length(), getBrigadeId());
    newWorker->setUniqueNum(id);

    return team.insert(newWorker->getUniqueNum(), newWorker);


}

bool Brigade::fireWorker(const std::string &key) {


    removeFromFriends(key);
    removeFromEnemies(key);


    return team.remove(key);
}

std::shared_ptr<Worker> Brigade::findWorker(const std::string &key) {
    return team.find(key)->value;
}

void Brigade::removeFromEnemies(const std::string &key) {
    auto it = team.begin();

    for (size_t i = 0; i < team.getTableSize(); i++) {
        if (!it->empty) {
            auto &friends = it->value->friends;

            friends.erase(std::remove_if(friends.begin(), friends.end(),
                                         [&key](const std::weak_ptr<Worker> &weakFriend) {
                                             if (auto lockedFriend = weakFriend.lock()) {
                                                 return lockedFriend->getUniqueNum() == key;
                                             }
                                             return false;
                                         }),
                          friends.end());
        }

        it++;
    }


}

void Brigade::removeFromFriends(const std::string &key) {

    auto it = team.begin();

    for (size_t i = 0; i < team.getTableSize(); i++) {
        if (!it->empty) {
            auto &friends = it->value->friends;

            friends.erase(std::remove_if(friends.begin(), friends.end(),
                                         [&key](const std::weak_ptr<Worker> &weakFriend) {
                                             if (auto lockedFriend = weakFriend.lock()) {
                                                 return lockedFriend->getUniqueNum() == key;
                                             }
                                             return false;
                                         }),
                          friends.end());
        }

        it++;
    }

}



//void Brigade::showBrigade() {
//    std::cout << "   Power: " << getBrigadePower() << "\n";
//    if (leader) std::cout << "   Brigade Leader (" << leader->name << ": " << leader->getUniqueNum() << ")\n";
//    else std::cout << "   Brigade Leader on holidays\n";
//
//    for (auto tmp = team.begin(); tmp != team.end(); tmp++) {
//
//        if (tmp->empty) std::cout << "   Empty\n";
//        else {
//            if ((*tmp).value->IsMaster()) {
//                std::cout << "   MASTER (" << (*tmp).key << ")\n";
//            } else if ((*tmp).value->IsStandardWorker()) {
//                std::cout << "   STANDARD (" << (*tmp).key << ")\n";
//            }
//        }
//    }
//
//
//}

//bool Brigade::createFriendship() {
//
//
//    if (getAmountOfPeople() < 2) return false;
//
//
//    size_t ind1 = 0;
//    size_t ind2 = 1;
//
//
//    std::cout << "_______FL5_______\n";
//
//
//    while (team.getAtIndex(ind1).key == team.getAtIndex(ind2).key) {
//        size_t ind1 = (ind1 + std::rand()) % team.getTableSize();
//        size_t ind2 = (ind2 + std::rand()) % team.getTableSize();
//    }
//
//    Worker::removeHate(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);
//
//    Worker::makeFriends(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);
//
//    return true;
//
//}

//bool Brigade::createEnmity() {
//
//    if (getAmountOfPeople() < 2) return false;
//
//    size_t ind1 = 0;
//    size_t ind2 = 1;
//    std::cout << "_______FL4_______\n";
//
//
//    while (team.getAtIndex(ind1).key == team.getAtIndex(ind2).key) {
//        size_t ind1 = (ind1 + std::rand()) % team.getTableSize();
//        size_t ind2 = (ind2 + std::rand()) % team.getTableSize();
//    }
//
//    Worker::removeFriendship(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);
//
//    Worker::makeEnemies(team.getAtIndex(ind1).value, team.getAtIndex(ind2).value);
//
//    return true;
//}

//size_t Brigade::calculate_penalty() {
//    size_t penaltySum = 0;
//
//    for (auto tmp = team.begin(); tmp != team.end(); tmp++) {
//        if (tmp->empty) continue;
//
//        std::shared_ptr<Worker> curWorker = tmp->value;
//
//        penaltySum = penaltySum + ((curWorker->getFriendsAmount() / 3) + (curWorker->getEnemiesAmount() / 2));
//    }
//
//    return penaltySum;
//}

double Brigade::calculate_brigade_power() const {

    double additiveSum = 0;
    double multiplicativeSum = 1;


    bool BrigadeLeaderExists = hasBrigadeLeader();

    for (auto tmp = team.begin(); tmp != team.end(); tmp++) {
        if (tmp->empty) continue;

        std::shared_ptr<Worker> curWorker = tmp->value;

        auto derivedWorker = std::dynamic_pointer_cast<ContributingWorker>(curWorker);

        if (derivedWorker != nullptr) {
            auto baseDescriptor = derivedWorker->getDescriptor().get();
            auto derivedDescriptor = dynamic_cast<MasterDescriptor *>(baseDescriptor);

            if (derivedDescriptor != nullptr) {
                multiplicativeSum *= curWorker->WorkerEffectiveness();
            } else {
                additiveSum += curWorker->WorkerEffectiveness();
            }
        }

    }

    double res = BrigadeLeaderExists ? additiveSum * multiplicativeSum :
                 (additiveSum - (double) calculate_penalty()) * multiplicativeSum;

    return res;
}

bool Brigade::hasBrigadeLeader() const {
    if (!leader) return false;
    return true;
}

size_t Brigade::calculate_penalty() const {

    size_t amount_or_uneffinciency = 0;


    for (auto tmp = team.begin(); tmp != team.end(); tmp++) {
        if (tmp->empty) continue;

        amount_or_uneffinciency += tmp->value->getFriendsAmount() / 3 + tmp->value->getEnemiesAmount() / 2;

    }


    return amount_or_uneffinciency;
}

std::shared_ptr<Worker> Brigade::findWorker(const std::string &key) const {
    return team.find(key)->value;
}

//void Brigade::showStats() {
//    getBrigadePower();
//    size_t penalty = calculate_penalty();
//    std::cout << "BRIGADE[" << brigadeId << "] INFO:\n";
//    std::cout << "Power: " << brigadePower << "\n";
//    std::cout << "Amount of inefficiencies: " << penalty << "\n\n\n";
//}


//void Brigade::calculate_efficiency() {
//    size_t i, additive_sum = 0;
//    double multiplicative_coefficient = 1;
//    bool BrigadeLeaderExists = hasBrigadeLeader();
//    for (auto tmp = team.begin(); i < team.getCurSize(); tmp++) {
//
//
//        if (!tmp->empty) {
//            auto cur = tmp->value;
//            if (cur->IsStandardWorker()) {
//                additive_sum += cur->standardWorkerEffectivenes();
//            } else if (cur->IsMaster()) {
//                multiplicative_coefficient *= cur->masterWorkerEffectivenes();
//            }
//
//
//            additive_sum = BrigadeLeaderExists ? additive_sum : additive_sum - (cur->getEnemiesAmount() / 2) -
//                                                                (cur->getFriendsAmount() / 3);
//            i++;
//        }
//
//    }
//
//    brigadePower = (double) additive_sum * multiplicative_coefficient;
//
//}

void BrigadeShow::ShowBrigade(const Brigade &brigade) {
    std::cout << "   Power: " << brigade.getBrigadeId() << "\n";
    if (brigade.leader)
        std::cout << "   Brigade Leader (" << brigade.leader->name << ": " << brigade.leader->getUniqueNum() << ")\n";
    else std::cout << "   Brigade Leader on holidays\n";

    for (auto tmp = brigade.team.begin(); tmp != brigade.team.end(); tmp++) {

        if (tmp->empty) {
            std::cout << "   Empty\n";
            continue;
        }

        std::shared_ptr<Worker> curWorker = tmp->value;

        auto derivedWorker = std::dynamic_pointer_cast<ContributingWorker>(curWorker);


        if (derivedWorker != nullptr) {
            auto baseDescriptor = derivedWorker->getDescriptor().get();
            auto derivedDescriptor = dynamic_cast<MasterDescriptor *>(baseDescriptor);

            if (derivedDescriptor != nullptr) {
                std::cout << "   MASTER (" << (*tmp).key << ")\n";
            } else {
                std::cout << "   STANDARD (" << (*tmp).key << ")\n";
            }


        }


    }
}

void BrigadeShow::ShowBrigadeStats(const Brigade &brigade) {
    brigade.calculate_brigade_power();
    size_t penalty = brigade.calculate_penalty();
    std::cout << "BRIGADE[" << brigade.brigadeId << "] INFO:\n";
    std::cout << "Power: " << brigade.brigadePower << "\n";
    std::cout << "Amount of inefficiencies: " << penalty << "\n\n\n";
}


