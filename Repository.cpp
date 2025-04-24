#include "Repository.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void Repository::addTrenchCoat(int id, int sizeOfTrench, const std::string& colourOfTrench,
    float priceOfTrench, int quantityOfTrench, const std::string& photography_linkOfTrench) {
    TrenchCoat trenchToAdd(id, sizeOfTrench, colourOfTrench, priceOfTrench,
        quantityOfTrench, photography_linkOfTrench);
    this->trenchCoats.push_back(trenchToAdd);
}

void Repository::removeTrenchCoat(int trenchID) {
    for (int i = 0; i < this->trenchCoats.size(); i++) {
        if (this->trenchCoats[i].getTrenchID() == trenchID) {
            this->trenchCoats.erase(trenchCoats.begin() + i);
            return;
        }
    }
}

void Repository::updateTrenchCoat(int trenchID, int newID, int newSizeOfTrench,
    const std::string& newColourOfTrench, float newPriceOfTrench,
    int newQuantityOfTrench, const std::string& newPhotography_linkOfTrench) {
    this->removeTrenchCoat(trenchID);
    this->addTrenchCoat(newID, newSizeOfTrench, newColourOfTrench, newPriceOfTrench,
        newQuantityOfTrench, newPhotography_linkOfTrench);
}

bool Repository::validID(int trenchID) {
    for (int i = 0; i < this->trenchCoats.size(); i++) {
        if (this->trenchCoats[i].getTrenchID() == trenchID) {
            return true;
        }
    }
    return false;
}

TrenchCoat Repository::getTrenchCoat(int trenchID) {
    for (int i = 0; i < this->trenchCoats.size(); i++) {
        if (this->trenchCoats[i].getTrenchID() == trenchID) {
            return this->trenchCoats[i];
        }
    }
    return TrenchCoat(-1, -1, "", -1, -1, "");
}

std::vector<TrenchCoat> Repository::getAllTrenchCoats() {
    return this->trenchCoats;
}

int Repository::getSize() {
    return this->trenchCoats.size();
}

void Repository::setFileName(std::string newFileName) {
    this->FileName = newFileName;
}

std::string Repository::getFileName() const {
    return this->FileName;
}

void Repository::writeToFile() {
    std::ofstream file(this->FileName);
    if (file.is_open()) {
        for (int i = 0; i < this->trenchCoats.size(); i++) {
            file << this->trenchCoats[i].getTrenchID() << " "
                << this->trenchCoats[i].getTrenchSize() << " "
                << this->trenchCoats[i].getTrenchColour() << " "
                << this->trenchCoats[i].getTrenchPrice() << " "
                << this->trenchCoats[i].getTrenchQuantity() << " "
                << this->trenchCoats[i].getTrenchPhotographyLink() << "\n";
        }
    }
    file.close();
}

void Repository::readFromFile() {
    std::ifstream file(this->FileName);
    if (file.is_open()) {
        int id, size, quantity;
        float price;
        std::string colour, photographyLink;
        while (file >> id >> size >> colour >> price >> quantity >> photographyLink) {
            TrenchCoat trenchToAdd(id, size, colour, price, quantity, photographyLink);
            this->trenchCoats.push_back(trenchToAdd);
        }
    }
    file.close();
}

Repository::Repository() : FileName("default.txt") {}

Repository::Repository(std::string FileName) : FileName(FileName) {
    this->readFromFile();
}

void CSVRepository::writeToFile()
{
    std::ofstream file(FileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open CSV file: " + this->FileName);
    }
    for (auto& coat : this->trenchCoats) {
        file << coat.getTrenchID() << ","
            << coat.getTrenchSize() << ","
            << "\"" << coat.getTrenchColour() << "\","
            << coat.getTrenchPrice() << ","
            << coat.getTrenchQuantity() << ","
            << "\"" << coat.getTrenchPhotographyLink() << "\"\n";
    }

    file.close();
}

void CSVRepository::readFromFile() 
{
    std::ifstream file(FileName);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open CSV file: " + this->FileName);
    }

    /*trenchCoats.clear();*/
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string token;

        // ID
        std::getline(lineStream, token, ',');
        int id = std::stoi(token);

        // parse size
        std::getline(lineStream, token, ',');
        int size = std::stoi(token);

        // parse colour
        std::getline(lineStream, token, ',');
        std::string colour = token;
        if (colour.front() == '"' && colour.back() == '"') {
            colour = colour.substr(1, colour.size() - 2);
        }

        // parse price
        std::getline(lineStream, token, ',');
        float price = std::stof(token);

        // parse quantity
        std::getline(lineStream, token, ',');
        int quantity = std::stoi(token);

        // parse photo link
        std::getline(lineStream, token);
        std::string photographyLink = token;
        if (photographyLink.front() == '"' && photographyLink.back() == '"') {
            photographyLink = photographyLink.substr(1, photographyLink.size() - 2);
        }
        trenchCoats.emplace_back(id, size, colour, price, quantity, photographyLink);
    }
}
