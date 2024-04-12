#ifndef PROJECT_WORKER_H
#define PROJECT_WORKER_H

#include <iostream>
#include <vector>
#include <memory>
#include <Descriptors.h>
#include <Utils.h>
#include <algorithm>


#define UNIQUE_NUM_LEN 16

class Worker {
public:
    std::string uniqueNum;
    std::string name;
    size_t age = 0;
    std::vector<std::weak_ptr<Worker>> friends;
    std::vector<std::weak_ptr<Worker>> enemies;


private:

    bool addFriend(std::shared_ptr<Worker> &friendPtr);

    bool addEnemy(std::shared_ptr<Worker> &enemyPtr);

    bool removeFriend(const std::string &id);

    bool removeEnemy(const std::string &id);

    [[nodiscard]] bool isFriendOrEnemy(const std::string &id) const;


public:


    Worker();

    Worker(const std::string &, size_t);

    Worker(const std::string &, size_t, const std::string &);

//    Worker(const Worker &other);

//    [[nodiscard]] virtual bool IsBrigadeLeader() const = 0;
//
//    [[nodiscard]] virtual bool IsMaster() const = 0;
//
//    [[nodiscard]] virtual bool IsStandardWorker() const = 0;

    [[nodiscard]] size_t getFriendsAmount() const { return friends.size(); }

    [[nodiscard]] size_t getEnemiesAmount() const { return enemies.size(); }

    [[nodiscard]] const std::string &getUniqueNum() const { return uniqueNum; }

    [[nodiscard]] const std::string &getName() const { return name; }

    [[nodiscard]] size_t getAge() const { return age; }

    void setName(std::string &newName) { name = std::move(newName); }

    void setAge(size_t newAge) { age = newAge; }

    void setUniqueNum(std::string &newNum) { uniqueNum = std::move(newNum); }

    [[nodiscard]] const std::vector<std::shared_ptr<Worker>> &getFriends() const {
        std::vector<std::shared_ptr<Worker>> result;
        for (const auto &weakFriendPtr: friends) {
            auto sharedFriendPtr = weakFriendPtr.lock();
            if (sharedFriendPtr) {
                result.push_back(sharedFriendPtr);
            }
        }
        return result;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<Worker>> &getEnemies() const {
        std::vector<std::shared_ptr<Worker>> result;
        for (const auto &weakEnemyPtr: friends) {
            auto sharedEnemyPtr = weakEnemyPtr.lock();
            if (sharedEnemyPtr) {
                result.push_back(sharedEnemyPtr);
            }
        }
        return result;
    }

    static bool makeFriends(std::shared_ptr<Worker> &friend1, std::shared_ptr<Worker> &friend2);

    static bool makeEnemies(std::shared_ptr<Worker> &enemy1, std::shared_ptr<Worker> &enemy2);

    static bool removeFriendship(std::shared_ptr<Worker> &friend1, std::shared_ptr<Worker> &friend2);

    static bool removeHate(std::shared_ptr<Worker> &enemy1, std::shared_ptr<Worker> &enemy2);

    virtual double WorkerEffectiveness() = 0; // Расскащзать про SOLID


    virtual ~Worker() = default;


};


class WorkerShow {

    void static ShowWorker(const Worker &worker);

};


#endif //PROJECT_WORKER_H
