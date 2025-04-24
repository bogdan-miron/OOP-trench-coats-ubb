#include "UI.h"
#include "Repository.h"
#include "Controller.h"
#include "TestAll.h"
#include <crtdbg.h>
#include "MySQLRepository.h"

int main()
{

    {
        std::cout << "Enter repo type:\n";
        std::cout << "1. Txt file.\n";
        std::cout << "2. CSV file\n";
        std::cout << "3. HTML file\n";
        std::cout << "4. MySQL server.\n";
        std::cout << "Choice: ";
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            Repository mainRepo("default.txt");
            Controller controller(mainRepo);
            Repository basket_repository("basket.txt");
            Controller basket_controller(basket_repository);

            UI ui(controller, basket_controller);
            ui.runApplication();
        }
        else if (choice == 2) {
            CSVRepository mainRepo("csv-database.csv");
            Controller controller(mainRepo);
            Repository basket_repository("basket.txt");
            Controller basket_controller(basket_repository);

            UI ui(controller, basket_controller);
            ui.runApplication();
        }
        else if (choice == 3) {
            HTMLRepository htmlRepo("html-database.html");
            Controller controller(htmlRepo);
            Repository basket_repository("basket.txt");
            Controller basket_controller(basket_repository);

            UI ui(controller, basket_controller);
            ui.runApplication();
        }
        else if (choice == 4) {
            MySQLRepository  sqlRepo("localhost", "root", "password", "trenchcoat_store");
            Controller controller(sqlRepo);
            Repository basket_repository("basket.txt");
            Controller basket_controller(basket_repository);

            UI ui(controller, basket_controller);
            ui.runApplication();

        }
        else {
            exit(0);
        }
        
    }

	_CrtDumpMemoryLeaks();
    return 0;
}

/*
CREATE DATABASE trenchcoat_store;
USE trenchcoat_store;

CREATE TABLE trenchcoats (
    id INT PRIMARY KEY,
    size INT NOT NULL,
    color VARCHAR(50) NOT NULL,
    price FLOAT NOT NULL,
    quantity INT NOT NULL,
    photography_link VARCHAR(255) NOT NULL
);

*/