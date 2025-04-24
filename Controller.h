#pragma once
#include <string>
#include "Repository.h"

class Controller{
    private:
        Repository& repository;

    public:
        //Controller();
        Controller(Repository& repo) : repository(repo) {};

        bool addTrenchCoat(int trenchID, 
                            int trenchSize, 
                            std::string trenchColour, 
                            int trenchPrice, 
                            int trenchQuantity, 
                            std::string trenchPhotograph);

        void removeTrenchCoat(int trenchID);
        bool updateTrenchCoat(int trenchID, 
                                int trenchNewID,
                                int trenchSize, 
                                std::string trenchColour, 
                                int trenchPrice, 
                                int trenchQuantity, 
                                std::string trenchPhotograph);

        int trenchCoatExists(int trenchID);
        TrenchCoat getTrenchCoat(int trenchID);
        std::vector<TrenchCoat> getAllTrenchCoats();
        std::vector<TrenchCoat> filterBySize(int trenchSize);
        
        int getSize();
        void setFileName(std::string newFileName);
        std::string getFileName() const;
        
        void saveProgress();
        void loadFromFile();
};