#pragma once
#include <string>
#include <vector>

#include "Domain.h"

class Repository {
protected:

    std::vector<TrenchCoat> trenchCoats;
    std::string FileName;

public:

    Repository();
    Repository(std::string FileName);

    virtual void addTrenchCoat(int id, int sizeOfTrench,
        const std::string& colourOfTrench, float priceOfTrench,
        int quantityOfTrench,
        const std::string& photography_linkOfTrench);

    virtual void removeTrenchCoat(int trenchID);
    virtual void updateTrenchCoat(int trenchID, int newID, int newSizeOfTrench,
        const std::string& newColourOfTrench,
        float newPriceOfTrench, int newQuantityOfTrench,
        const std::string& newPhotography_linkOfTrench);

    virtual bool validID(int trenchID);
    TrenchCoat getTrenchCoat(int trenchID);
    virtual std::vector<TrenchCoat> getAllTrenchCoats();

    int getSize();
    void setFileName(std::string newFileName);
    std::string getFileName() const;
    virtual void writeToFile();
    virtual void readFromFile();
};

class CSVRepository : public Repository {
public:
    CSVRepository() { this->FileName = "csv-database.csv"; }
    CSVRepository(std::string filename) { this->FileName = filename; }

    void writeToFile() override;
    void readFromFile() override;

};

class HTMLRepository : public Repository {
public:
    HTMLRepository() { this->FileName = "html-database.html"; }
    HTMLRepository(std::string filename) { this->FileName = filename; }

    void writeToFile() override;
    void readFromFile() override;
};