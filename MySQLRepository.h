#pragma once
#include "Repository.h"
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MySQLRepository : public Repository {
private:
    sql::Driver* driver;
    std::unique_ptr<sql::Connection> connection;
    std::string server, username, password, database;

    void connect();
    void disconnect();

public:
    MySQLRepository(const std::string& server,
        const std::string& username,
        const std::string& password,
        const std::string& database);

    ~MySQLRepository();

    void addTrenchCoat(int id, int sizeOfTrench, const std::string& colourOfTrench,
        float priceOfTrench, int quantityOfTrench,
        const std::string& photography_linkOfTrench) override;

    void removeTrenchCoat(int trenchID) override;
    void updateTrenchCoat(int trenchID, int newID, int newSizeOfTrench,
        const std::string& newColourOfTrench, float newPriceOfTrench,
        int newQuantityOfTrench, const std::string& newPhotography_linkOfTrench) override;

    std::vector<TrenchCoat> getAllTrenchCoats() override;
};