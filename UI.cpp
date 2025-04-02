#include "UI.h"
#include <string>
#include <iostream>
#include <utility>
#include <cstdlib>

using namespace std;
#define MAX_NAME_LEN 60

UI::UI(Controller controller, Controller basket_controller) {
    this->controller = std::move(controller);
    this->basket_controller = std::move(basket_controller);
}

void UI::printWelcomeMessage() {
    std::cout << "========================================" << std::endl;
    std::cout << "   ProperTrenchCoat - Admin Dashboard   " << std::endl;
    std::cout << "========================================" << std::endl;
}

void UI::printQuestioningMessage() {
    std::cout << "\n*** Welcome to Proper Trench Coats! ***" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Select mode:" << std::endl;
    std::cout << "  1. Administrator" << std::endl;
    std::cout << "  2. User" << std::endl;
    std::cout << "  0. Exit" << std::endl;
    std::cout << "> ";
}

void UI::printAddToCartButton() {
    std::cout << "\n[+] Add to Cart" << std::endl;
}

void UI::printTrenchCoat(TrenchCoat trenchCoatToPrint) {
    std::cout << "\n--- Trench Coat Details ---" << std::endl;
    std::cout << "ID: " << trenchCoatToPrint.getTrenchID() << std::endl;
    std::cout << "Size: " << trenchCoatToPrint.getTrenchSize() << std::endl;
    std::cout << "Colour: " << trenchCoatToPrint.getTrenchColour() << std::endl;
    std::cout << "Price: $" << trenchCoatToPrint.getTrenchPrice() << std::endl;
    std::cout << "Quantity: " << trenchCoatToPrint.getTrenchQuantity() << std::endl;
    std::cout << "Photo: " << trenchCoatToPrint.getTrenchPhotographyLink() << std::endl;
}

void UI::printAdminMenu() {
    std::cout << "\n=== ADMIN MENU ===" << std::endl;
    std::cout << "1. Add a trench coat" << std::endl;
    std::cout << "2. Remove a trench coat" << std::endl;
    std::cout << "3. Update a trench coat" << std::endl;
    std::cout << "4. View a trench coat" << std::endl;
    std::cout << "5. List all trench coats" << std::endl;
    std::cout << "6. Save to database" << std::endl;
    std::cout << "7. Load from database" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "> ";
}

void UI::printUserMenu() {
    std::cout << "\n=== USER MENU ===" << std::endl;
    std::cout << "1. Browse trench coats" << std::endl;
    std::cout << "2. View shopping cart" << std::endl;
    std::cout << "3. Checkout" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "> ";
}

void UI::printUserBrowsingMenu() {
    std::cout << "\n[1] Previous  [2] Next" << std::endl;
    std::cout << "[3] Add to Cart  [4] Exit" << std::endl;
    std::cout << "> ";
}

void UI::printPurchaseMessage() {
    std::cout << "\nPurchase confirmed. Thank you!" << std::endl;
}

void UI::printGoodbyeMessage() {
    std::cout << "\nGoodbye!" << std::endl;
}

void UI::printAllTrenchCoats(int codeOfController) {
    if (codeOfController == 1) {
        std::vector<TrenchCoat> allTrenchCoats = this->controller.getAllTrenchCoats();
        for (int i = 0; i < allTrenchCoats.size(); i++) {
            printTrenchCoat(allTrenchCoats[i]);
        }
    }
    else {
        std::vector<TrenchCoat> allTrenchCoats = this->basket_controller.getAllTrenchCoats();
        for (int i = 0; i < allTrenchCoats.size(); i++) {
            TrenchCoat trenchCoat = allTrenchCoats[i];
            std::cout << "ID: " << trenchCoat.getTrenchID() << " || "
                << "Size: " << trenchCoat.getTrenchSize() << " || "
                << "Colour: " << trenchCoat.getTrenchColour() << " || "
                << "Price: " << trenchCoat.getTrenchPrice() << " || "
                << "Quantity: " << trenchCoat.getTrenchQuantity() << " || "
                << "Link: " << trenchCoat.getTrenchPhotographyLink() << std::endl;
        }
    }
}

void UI::administratorMode() {
    this->printWelcomeMessage();
    this->printAdminMenu();
    int command;
    std::cin >> command;
    while (command < 9 && command > 0) {
        switch (command) {
        case 1: this->addTrenchCoat(); break;
        case 2: this->removeTrenchCoat(); break;
        case 3: this->updateTrenchCoat(); break;
        case 4: this->getTrenchCoat(); break;
        case 5: this->printAllTrenchCoats(1); break;
        case 6: this->writeToDatabase(); break;
        case 7: this->readFromDatabase(); break;
        case 8: this->printGoodbyeMessage(); return;
        default: std::cout << "Invalid command!" << std::endl; break;
        }
        this->printAdminMenu();
        std::cin >> command;
    }
    this->printGoodbyeMessage();
}

void UI::addTrenchCoat() {
    int id, sizeOfTrench, quantityOfTrench;
    char colourOfTrench[MAX_NAME_LEN], photography_linkOfTrench[MAX_NAME_LEN];
    float priceOfTrench;

    std::cout << "Enter ID: ";
    std::cin >> id;
    while (id <= 0) {
        std::cout << "ID must be positive: ";
        std::cin >> id;
    }

    std::cout << "Enter size [30-50]: ";
    std::cin >> sizeOfTrench;
    while (sizeOfTrench < 30 || sizeOfTrench > 50) {
        std::cout << "Size must be 30-50: ";
        std::cin >> sizeOfTrench;
    }

    std::cout << "Enter colour: ";
    std::cin.ignore();
    std::cin >> colourOfTrench;

    std::cout << "Enter price: ";
    std::cin >> priceOfTrench;
    while (priceOfTrench <= 0) {
        std::cout << "Price must be positive: ";
        std::cin >> priceOfTrench;
    }

    std::cout << "Enter quantity: ";
    std::cin >> quantityOfTrench;
    while (quantityOfTrench <= 0) {
        std::cout << "Quantity must be positive: ";
        std::cin >> quantityOfTrench;
    }

    std::cout << "Enter photo link: ";
    std::cin.ignore();
    std::cin >> photography_linkOfTrench;

    if (this->controller.addTrenchCoat(id, sizeOfTrench, colourOfTrench,
        priceOfTrench, quantityOfTrench, photography_linkOfTrench)) {
        std::cout << "Trench coat added!" << std::endl;
    }
    else {
        std::cout << "ID already exists!" << std::endl;
    }
}

void UI::removeTrenchCoat() {
    int id;
    std::cout << "Enter ID to remove: ";
    std::cin >> id;
    while (id <= 0) {
        std::cout << "ID must be positive: ";
        std::cin >> id;
    }

    if (!this->controller.trenchCoatExists(id)) {
        std::cout << "Trench coat not found!" << std::endl;
    }
    else {
        this->controller.removeTrenchCoat(id);
        std::cout << "Trench coat removed!" << std::endl;
    }
}

void UI::updateTrenchCoat() {
    int id, newID, sizeOfTrench, quantityOfTrench;
    std::string colourOfTrench, photography_linkOfTrench;
    float priceOfTrench;

    std::cout << "Enter ID to update: ";
    std::cin >> id;
    if (!this->controller.trenchCoatExists(id)) {
        std::cout << "Trench coat not found!" << std::endl;
        return;
    }

    std::cout << "Enter new ID: ";
    std::cin >> newID;
    if (this->controller.trenchCoatExists(newID)) {
        std::cout << "ID already taken!" << std::endl;
        return;
    }

    std::cout << "Enter size [30-50]: ";
    std::cin >> sizeOfTrench;
    while (sizeOfTrench < 30 || sizeOfTrench > 50) {
        std::cout << "Size must be 30-50: ";
        std::cin >> sizeOfTrench;
    }

    std::cout << "Enter colour: ";
    std::cin >> colourOfTrench;

    std::cout << "Enter price: ";
    std::cin >> priceOfTrench;
    while (priceOfTrench <= 0) {
        std::cout << "Price must be positive: ";
        std::cin >> priceOfTrench;
    }

    std::cout << "Enter quantity: ";
    std::cin >> quantityOfTrench;
    while (quantityOfTrench <= 0) {
        std::cout << "Quantity must be positive: ";
        std::cin >> quantityOfTrench;
    }

    std::cout << "Enter photo link: ";
    std::cin >> photography_linkOfTrench;

    this->controller.updateTrenchCoat(id, newID, sizeOfTrench, colourOfTrench,
        priceOfTrench, quantityOfTrench, photography_linkOfTrench);
    std::cout << "Trench coat updated!" << std::endl;
}

void UI::getTrenchCoat() {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    while (id <= 0) {
        std::cout << "ID must be positive: ";
        std::cin >> id;
    }

    if (!this->controller.trenchCoatExists(id)) {
        std::cout << "Trench coat not found!" << std::endl;
    }
    else {
        this->controller.getTrenchCoat(id);
        std::cout << "Trench coat retrieved!" << std::endl;
    }
}

void UI::writeToDatabase() {
    this->controller.saveProgress();
    std::cout << "Database saved!" << std::endl;
}

void UI::readFromDatabase() {
    this->controller.loadFromFile();
    std::cout << "Database loaded!" << std::endl;
}

void UI::cycleThroughTrenchCoats() {
    int sizeToFilterBy;
    std::cout << "Enter size filter (0 for all): ";
    std::cin >> sizeToFilterBy;

    int index = 0, command, totalCost = 0;
    std::vector<TrenchCoat> trenchCoats = (sizeToFilterBy != 0)
        ? this->controller.filterBySize(sizeToFilterBy)
        : this->controller.getAllTrenchCoats();

    if (trenchCoats.size() == 0) {
        std::cout << "No matching trench coats!" << std::endl;
        return;
    }

    this->printUserBrowsingMenu();
    std::cin >> command;

    while (command != 4) {
        if (command == 1) {
            index = (index == 0) ? trenchCoats.size() - 1 : index - 1;
        }
        else if (command == 2) {
            index = (index == trenchCoats.size() - 1) ? 0 : index + 1;
        }
        else if (command == 3) {
            this->addTrenchCoatToShoppingBasket(trenchCoats[index]);
            totalCost += trenchCoats[index].getTrenchPrice();
            std::cout << "Added to cart! Total: $" << totalCost << std::endl;
        }
        else {
            std::cout << "Invalid command!" << std::endl;
        }
        this->printTrenchCoat(trenchCoats[index]);
        std::cout << "> ";
        std::cin >> command;
    }
}

void UI::addTrenchCoatToShoppingBasket(TrenchCoat trenchCoatToAdd) {
    this->basket_controller.addTrenchCoat(
        trenchCoatToAdd.getTrenchID(),
        trenchCoatToAdd.getTrenchSize(),
        trenchCoatToAdd.getTrenchColour(),
        trenchCoatToAdd.getTrenchPrice(),
        trenchCoatToAdd.getTrenchQuantity(),
        trenchCoatToAdd.getTrenchPhotographyLink()
    );
}

void UI::printShoppingBasket() {
    int totalCost = 0;
    std::vector<TrenchCoat> shoppingBasket = this->basket_controller.getAllTrenchCoats();
    for (int i = 0; i < shoppingBasket.size(); i++) {
        this->printTrenchCoat(shoppingBasket[i]);
        totalCost += shoppingBasket[i].getTrenchPrice();
    }
    std::cout << "TOTAL: $" << totalCost << std::endl;
}

void UI::emptyBasketOfTrenchCoats() {
    std::vector<TrenchCoat> shoppingBasket = this->basket_controller.getAllTrenchCoats();
    for (int i = 0; i < shoppingBasket.size(); i++) {
        this->controller.updateTrenchCoat(
            shoppingBasket[i].getTrenchID(),
            shoppingBasket[i].getTrenchID(),
            shoppingBasket[i].getTrenchSize(),
            shoppingBasket[i].getTrenchColour(),
            shoppingBasket[i].getTrenchPrice(),
            shoppingBasket[i].getTrenchQuantity() - 1,
            shoppingBasket[i].getTrenchPhotographyLink()
        );
        this->basket_controller.removeTrenchCoat(shoppingBasket[i].getTrenchID());
    }
}

void UI::userMode() {
    this->printUserMenu();
    this->controller.loadFromFile();
    int command;
    std::cin >> command;

    while (command < 4 && command > 0) {
        switch (command) {
        case 1: this->cycleThroughTrenchCoats(); break;
        case 2: this->printShoppingBasket(); break;
        case 3:
            this->printPurchaseMessage();
            this->emptyBasketOfTrenchCoats();
            break;
        default: std::cout << "Invalid command!" << std::endl; break;
        }
        this->printUserMenu();
        std::cin >> command;
    }
}

void UI::runApplication() {
    this->printQuestioningMessage();
    int command;
    std::cin >> command;
    while (command < 3 && command > 0) {
        switch (command) {
        case 1: this->administratorMode(); break;
        case 2: this->userMode(); break;
        default: std::cout << "Invalid command!" << std::endl; break;
        }
        this->printQuestioningMessage();
        std::cin >> command;
    }
    this->printGoodbyeMessage();
}