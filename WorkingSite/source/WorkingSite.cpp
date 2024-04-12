#include <WorkingSite.h>

std::string & WorkingSite::determineProblemBrigade() {

    size_t max = 0;

    std::string worstBrigadeId;

    for (auto& cur : workingBrigades) {
        size_t num = cur->calculate_penalty();
        if (num > max) {
            max = num;
            worstBrigadeId = cur->getBrigadeId();
        }
    }

    return worstBrigadeId;

}

std::shared_ptr<Brigade> &WorkingSite::findBrigadeById(const std::string &id) {
    for (auto& cur : workingBrigades) {
        if (cur->getBrigadeId() == id) return cur;
    }
}

void WorkingSite::addBrigade(const std::shared_ptr<Brigade> &brigade) {

    workingBrigades.push_back(brigade);

}

std::shared_ptr<Brigade> &WorkingSite::getBrigade(size_t ind) {
    return workingBrigades.at(ind);
}

bool WorkingSite::WillBeCompletedInADay()  {
    return ((double) volumeOfWork - getProductivity()) < 0;
}



double WorkingSite::getProductivity()  {
    double sum = 0;

    for(const auto &tmp : workingBrigades) {
        sum += tmp->get_brigade_power();
    }

    productivity = sum;
    return sum;
}

void WorkingSiteShow::ShowWorkingSite(const WorkingSite &obj) {

    std::cout << "Name of Object: " << obj.nameOfObject << std::endl;
    std::cout << "Overall Volume of Work: " << obj.volumeOfWork << std::endl;
    std::cout << "Remaining Work: " << obj.curVolumeOfWork << std::endl;
    std::cout << "Productivity per Day: " << obj.productivity << std::endl;

    size_t numOfWorkingBrigades = obj.workingBrigades.size();

    if (numOfWorkingBrigades == 0) {
        std::cout << "There are no brigades on this site\n";

    } else {
        std::cout << "There are [" << numOfWorkingBrigades << "] brigades on this working site: \n";

        for (const auto &tmp: obj.workingBrigades) {

            std::string leader;

            switch (tmp->hasBrigadeLeader()) {
                case true:
                    leader = "have a leader";
                    break;

                case false:
                    leader = "doesn't have a leader";
                    break;

                default:
                    break;

            }

            std::cout << "-> Brigade #" << tmp->getBrigadeId() << "\n";
            BrigadeShow::ShowBrigade(*tmp);


        }
    }
}
