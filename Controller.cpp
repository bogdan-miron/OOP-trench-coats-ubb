#include "Controller.h"

using namespace std;

Controller::Controller() : repository(Repository()) {}

Controller::Controller(Repository repository) : repository(repository) {}

bool Controller::addTrenchCoat(int trenchID,
    int trenchSize,
    string trenchColour,
    int trenchPrice,
    int trenchQuantity,
    string trenchPhotograph) {
    for (int i = 0; i < repository.getSize(); i++) {
        if (repository.getAllTrenchCoats()[i].getTrenchID() == trenchID) {
            return false;
        }
    }

    repository.addTrenchCoat(trenchID, trenchSize, trenchColour,
        trenchPrice, trenchQuantity, trenchPhotograph);
    return true;
}

void Controller::removeTrenchCoat(int trenchID) {
    repository.removeTrenchCoat(trenchID);
}

bool Controller::updateTrenchCoat(int trenchID,
    int trenchNewID,
    int trenchSize,
    string trenchColour,
    int trenchPrice,
    int trenchQuantity,
    string trenchPhotograph) {
    if (!trenchCoatExists(trenchID)) {
        return false;
    }

    repository.updateTrenchCoat(trenchID, trenchNewID, trenchSize, trenchColour,
        trenchPrice, trenchQuantity, trenchPhotograph);
    return true;
}

int Controller::trenchCoatExists(int trenchID) {
    int counter = 0;
    for (int i = 0; i < repository.getSize(); i++) {
        if (repository.getAllTrenchCoats()[i].getTrenchID() == trenchID) {
            counter++;
        }
    }
    return counter;
}

TrenchCoat Controller::getTrenchCoat(int trenchID) {
    return repository.getTrenchCoat(trenchID);
}

dynamicVector<TrenchCoat> Controller::getAllTrenchCoats() {
    return repository.getAllTrenchCoats();
}

dynamicVector<TrenchCoat> Controller::filterBySize(int trenchSize) {
    dynamicVector<TrenchCoat> filteredTrenchCoats;
    dynamicVector<TrenchCoat> allTrenchCoats = repository.getAllTrenchCoats();

    for (int i = 0; i < repository.getSize(); i++) {
        if (allTrenchCoats[i].getTrenchSize() == trenchSize) {
            filteredTrenchCoats.append(allTrenchCoats[i]);
        }
    }

    return filteredTrenchCoats;
}

int Controller::getSize() {
    return repository.getSize();
}

void Controller::setFileName(string newFileName) {
    repository.setFileName(newFileName);
}

string Controller::getFileName() const {
    return repository.getFileName();
}

void Controller::saveProgress() {
    repository.writeToFile();
}

void Controller::loadFromFile() {
    repository.readFromFile();
}