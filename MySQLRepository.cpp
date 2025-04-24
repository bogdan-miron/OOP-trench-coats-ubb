#include "MySQLRepository.h"

MySQLRepository::MySQLRepository(const std::string& server,
    const std::string& username,
    const std::string& password,
    const std::string& database)
    : server(server), username(username), password(password), database(database) {
    connect();
}

MySQLRepository::~MySQLRepository() {
    disconnect();
}

void MySQLRepository::connect() {
    try {
        driver = get_driver_instance();
        connection.reset(driver->connect(server, username, password));
        connection->setSchema(database);
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL Connection Error: " << e.what() << std::endl;
        throw;
    }
}

void MySQLRepository::disconnect() {
    if (connection) {
        connection->close();
    }
}

void MySQLRepository::addTrenchCoat(int id, int size, const std::string& colour,
    float price, int quantity, const std::string& link) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            connection->prepareStatement(
                "INSERT INTO trenchcoats (id, size, color, price, quantity, photography_link) "
                "VALUES (?, ?, ?, ?, ?, ?)"
            )
        );
        pstmt->setInt(1, id);
        pstmt->setInt(2, size);
        pstmt->setString(3, colour);
        pstmt->setDouble(4, price);
        pstmt->setInt(5, quantity);
        pstmt->setString(6, link);
        pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL Add Error: " << e.what() << std::endl;
        throw;
    }
}

std::vector<TrenchCoat> MySQLRepository::getAllTrenchCoats() {
    std::vector<TrenchCoat> coats;
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(
            stmt->executeQuery("SELECT * FROM trenchcoats")
        );

        while (res->next()) {
            coats.emplace_back(
                res->getInt("id"),
                res->getInt("size"),
                res->getString("color"),
                res->getDouble("price"),
                res->getInt("quantity"),
                res->getString("photography_link")
            );
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL Query Error: " << e.what() << std::endl;
        throw;
    }
    return coats;
}

void MySQLRepository::removeTrenchCoat(int trenchID) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            connection->prepareStatement(
                "DELETE FROM trenchcoats WHERE id = ?"
            )
        );
        pstmt->setInt(1, trenchID);
        int affectedRows = pstmt->executeUpdate();

        if (affectedRows == 0) {
            throw std::runtime_error("No trench coat found with ID: " + std::to_string(trenchID));
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL Delete Error: " << e.what() << std::endl;
        throw;
    }
}

void MySQLRepository::updateTrenchCoat(int trenchID, int newID, int newSize,
    const std::string& newColour, float newPrice,
    int newQuantity, const std::string& newLink) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            connection->prepareStatement(
                "UPDATE trenchcoats SET id = ?, size = ?, color = ?, "
                "price = ?, quantity = ?, photography_link = ? "
                "WHERE id = ?"
            )
        );
        pstmt->setInt(1, newID);
        pstmt->setInt(2, newSize);
        pstmt->setString(3, newColour);
        pstmt->setDouble(4, newPrice);
        pstmt->setInt(5, newQuantity);
        pstmt->setString(6, newLink);
        pstmt->setInt(7, trenchID);

        int affectedRows = pstmt->executeUpdate();
        if (affectedRows == 0) {
            throw std::runtime_error("No trench coat found with ID: " + std::to_string(trenchID));
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL Update Error: " << e.what() << std::endl;
        throw;
    }
}



