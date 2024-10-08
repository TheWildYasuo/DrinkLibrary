#include "DrinkLibrary.h"

#include <iostream>
using namespace std;

int main ()
{
    DrinkLibrary library;

    library.readIn();

    int choice;

    do {
        choice = library.displayMenuGetChoice();

        switch(choice) {
            case 1:
                library.printDrinks();
                break;
            case 2:
                library.addDrink();
                break;
            case 3:
                library.editDrinks();
                break;
            case 4:
                library.makeNew();
                library.readIn();
                break;
            case 5:
                library.changeFile();
                break;
            case 6:
                cout << "\n\t\tExiting Program.\n";
                return(0);
            default:
                cout << "\n\t\tInvalid choice Please try again.\n";
        }
    } while(choice != 6);

    return 0;
}