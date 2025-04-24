#include "UI.h"
#include "Repository.h"
#include "Controller.h"
#include "TestAll.h"
#include <crtdbg.h>

int main()
{
    /*testDomain();
    testDynamicArray();
    testRepository();
    testController();
    testTrenchCoatExists();*/

    {
        std::cout << "Enter repo type:\n";
        std::cout << "1. Txt file.\n";
        std::cout << "2. CSV file\n";
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
        
    }

	_CrtDumpMemoryLeaks();
    return 0;
}