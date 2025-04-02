#include "UI.h"
#include "Repository.h"
#include "Controller.h"
#include "TestAll.h"
#include <crtdbg.h>

int main()
{
    testDomain();
    testDynamicArray();
    testRepository();
    testController();
    testTrenchCoatExists();

    {
        Controller controller;
        Repository basket_repository("basket.txt");
        Controller basket_controller(basket_repository);

        UI ui(controller, basket_controller);
        ui.runApplication();
    }

	_CrtDumpMemoryLeaks();
    return 0;
}