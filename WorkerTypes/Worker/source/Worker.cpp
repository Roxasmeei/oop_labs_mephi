#include <Worker.h>

Worker::Worker(const std::string &_name, size_t _age) : name(_name), age(_age) {
    uniqueNum = "0000::" + generateRandomString(UNIQUE_NUM_LEN - 6);
}


Worker::Worker() {
    uniqueNum = "0000::" + generateRandomString(UNIQUE_NUM_LEN - 6);
}

Worker::Worker(const std::string &_name, size_t _age, const std::string &_brigadeId) : name(_name), age(_age) {
    uniqueNum = _brigadeId + "::" + generateRandomString(UNIQUE_NUM_LEN - 6);
}

bool Worker::addFriend(std::shared_ptr<Worker> &friendPtr) {

    if (friendPtr->getUniqueNum() == this->uniqueNum) return false;


    if (!isFriendOrEnemy(friendPtr->uniqueNum)) {
        std::weak_ptr<Worker> weakFriendPtr = friendPtr;
        friends.push_back(weakFriendPtr);
        return true;
    }

    return false;
}

bool Worker::addEnemy(std::shared_ptr<Worker> &enemyPtr) {
    if (enemyPtr->getUniqueNum() == this->uniqueNum) return false;

    if (!isFriendOrEnemy(enemyPtr->uniqueNum)) {
        std::weak_ptr<Worker> weakFriendPtr = enemyPtr;
        enemies.push_back(weakFriendPtr);
        return true;
    }

    return false;
}

//bool Worker::removeFriend(const std::string &id) {
//    auto it = std::find_if(friends.begin(), friends.end(),
//                           [&id](const auto &friendPtr) {
//                               return friendPtr->uniqueNum == id;
//                           });
//
//    if (it != friends.end()) {
//        friends.erase(it);
//        return true;
//    }
//
//    return false;
//}

bool Worker::removeFriend(const std::string &id) {
    auto it = std::remove_if(friends.begin(), friends.end(),
                             [&id](const auto &weakFriendPtr) {
                                 auto friendPtr = weakFriendPtr.lock();
                                 return friendPtr && friendPtr->uniqueNum == id;
                             });

    if (it != friends.end()) {
        friends.erase(it, friends.end());
        return true;
    }

    return false;
}

bool Worker::removeEnemy(const std::string &id) {
    auto it = std::remove_if(enemies.begin(), enemies.end(),
                             [&id](const auto &weakEnemyPtr) {
                                 auto EnemyOtr = weakEnemyPtr.lock();
                                 return EnemyOtr && EnemyOtr->uniqueNum == id;
                             });

    if (it != enemies.end()) {
        enemies.erase(it, enemies.end());
        return true;
    }

    return false;
}



bool Worker::isFriendOrEnemy(const std::string &id) const {

    for (const auto &weakFriendPtr : friends) {
        auto friendPtr = weakFriendPtr.lock();
        if (friendPtr && friendPtr->getUniqueNum() == id) {
            return true;
        }
    }

    for (const auto &weakEnemyPtr : enemies) {
        auto enemyPtr = weakEnemyPtr.lock();
        if (enemyPtr && enemyPtr->getUniqueNum() == id) {
            return true;
        }
    }

    return false;
}

bool Worker::makeFriends(std::shared_ptr<Worker> &friend1, std::shared_ptr<Worker> &friend2) {
    bool act1 = false;
    bool act2 = false;


    if (friend1 && friend2) {
        act1 = friend1->addFriend(friend2);
        act2 = friend2->addFriend(friend1);
    }


    return act1 && act2;
}

bool Worker::makeEnemies(std::shared_ptr<Worker> &enemy1, std::shared_ptr<Worker> &enemy2) {
    bool act1 = false;
    bool act2 = false;

    if (enemy1 && enemy2) {
        act1 = enemy1->addEnemy(enemy2);
        act2 = enemy2->addEnemy(enemy1);
    }

    return act1 * act2;
}

bool Worker::removeFriendship(std::shared_ptr<Worker> &friend1, std::shared_ptr<Worker> &friend2) {
    bool act1 = false;
    bool act2 = false;


    if (friend1 && friend2) {
        act1 = friend1->removeFriend(friend2->uniqueNum);
        act2 = friend2->removeFriend(friend1->uniqueNum);
    }


    return act1 && act2;
}

bool Worker::removeHate(std::shared_ptr<Worker> &enemy1, std::shared_ptr<Worker> &enemy2) {
    bool act1 = false;
    bool act2 = false;


    if (enemy1 && enemy2) {
        act1 = enemy1->removeFriend(enemy2->uniqueNum);
        act2 = enemy2->removeFriend(enemy1->uniqueNum);
    }


    return act1 && act2;
}


void WorkerShow::ShowWorker(const Worker &worker) {

    std::cout << "Worker Information" << std::endl;
    std::cout << "Unique Number: " << worker.getUniqueNum() << std::endl;
    std::cout << "Name: " << worker.getName() << std::endl;
    std::cout << "Age: " << worker.getAge() << std::endl;


    std::cout << "Friends:" << std::endl;
    for (const auto &friendPtr: worker.getFriends()) {
        std::cout << "  " << friendPtr->getName() << " (Unique Number: " << friendPtr->getUniqueNum() << ")"
                  << std::endl;
    }


    std::cout << "Enemies:" << std::endl;
    for (const auto &enemyPtr: worker.getEnemies()) {
        std::cout << "  " << enemyPtr->getName() << " (Unique Number: " << enemyPtr->getUniqueNum() << ")" << std::endl;
    }

    std::cout << "--------------------------" << std::endl;

}

