#pragma once


#include <Utils.h>
#include <HashMap.h>
#include <Worker.h>
#include <ContributingWorker.h>
#include <BrigadeLeader.h>


class Brigade {

private:
    const std::string brigadeId = generateRandomString(4);
    HashTable<std::string, std::shared_ptr<Worker>> team;
    std::shared_ptr<BrigadeLeader> leader;

    double brigadePower = 0;

    friend class BrigadeShow;

private:


    void removeFromFriends(const std::string &key);

    void removeFromEnemies(const std::string &key);

public:

    Brigade() = default;

    explicit Brigade(size_t brigadeSize) : team(brigadeSize) {};

public:

    HashTable<std::string, std::shared_ptr<Worker>> &get_table() { return team; }

    [[nodiscard]] double calculate_brigade_power() const;

    double &set_brigade_power() {
        brigadePower = calculate_brigade_power();
        return brigadePower;
    }

    [[nodiscard]] double get_brigade_power() const { return brigadePower; }

    size_t calculate_penalty() const;

    [[nodiscard]] size_t getAmountOfPeople() const { return team.getCurSize(); }

    [[nodiscard]] const std::string &getBrigadeId() const { return brigadeId; } // ссылка на строку

    [[nodiscard]] size_t getMaxBrigadeSize() const { return team.getTableSize(); }

    size_t getCurBrigadeSize() { return team.getCurSize(); }

    [[nodiscard]] bool hasBrigadeLeader() const;

    bool addBrigadeLeader(std::shared_ptr<BrigadeLeader> &newLeader);

    bool redirectBrigadeLeader(Brigade &newPlaceForLeader);

    bool addWorker(std::shared_ptr<Worker> &newWorker);

    bool fireWorker(const std::string &key);

    std::shared_ptr<Worker> findWorker(const std::string &key); // const перегрухки


    std::shared_ptr<Worker> findWorker(const std::string &key) const; // const перегрухки






};


class BrigadeShow {

public:

    void static ShowBrigade(const Brigade &);

    void static ShowBrigadeStats(const Brigade &);


};



