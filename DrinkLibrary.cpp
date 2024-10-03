/*
    Title: DrinkLibrary.cpp
    Project 1 - CSC1310
    Authors: Levi, Brody, Ryan, Justin
    Date: 9/18/2024
 */
#include "DrinkLibrary.h"   // header file
#include <fstream>          // allow input from input text file
#include <iostream>
#include "Drink.h"
#include "Recipe.h"

using namespace std;

void DrinkLibrary::readIn()
{
    ifstream input;                 // cin file


    int choice, numDrinks = 0;
    string fileName, inputCounter;

    // choose which file to read from
        cout << "\n\nWhich file would you like to read from?\n";
        cout << "\n\t1. Working Library\n";
        cout << "\t2. Other\n";
        cout << "\t3. Exit\n";
        cout << "\nChoice: ";
        cin >> choice;
    do{

        switch(choice)
        {
            case 1:
                fileName = "WORKING_LIBRARY.txt";
                break;

            case 2:
                fileName.clear();
                cout << "\n\t\tEnter name of file or hit Enter key to exit: " << endl;
                cin.ignore();
                getline(cin, fileName);
                if(fileName.empty())
                {
                    return;
                }
                break;

            case 3:
                return;
            
            default:
                cout << "\nInvalid selection!";
                cin >> choice;
                break;
        }
        input.open(fileName);
        if (input.fail())               // fail case
            {
                cout << "\n\t\tFailed to open input file. Check for " << fileName << " and try again." << endl;
            }
    }while(!input.is_open());


    // count numDrinks
    while (getline(input, inputCounter, '\n'))
    {
        numDrinks++;
    }
    input.clear();
    input.seekg(0);

    drinks = new Drink*[numDrinks]; // dynamically allocate array of pointers to Drink
    this->numDrinks = numDrinks;    // set numDrinks to the equivalent class variable

    for (int i = 0; i < numDrinks; i++)
    {
      string name, pairing, glassware, instructions;
      string* ingredients;
      int alchololPercentage, numIngredients;   // need to incorperate numIngredients into Recipe class

      // obtain values for parameters from input file
      getline(input, name, '*');

      input >> alchololPercentage;
      input.ignore();               // ignore *

      getline(input, pairing, '*');

      input >> numIngredients;                  // need to incorperate numIngredients into Recipe class !!!!!!!!!!!!!!!!!!
      input.ignore();               // ingore *
      ingredients = new string[numIngredients];
      for(int j = 0; j < numIngredients; j++)
      {
        getline(input, ingredients[j], '*');
      }

      getline(input, glassware, '*');

      getline(input, instructions, '*');

      // create a Recipe object
      Recipe* drinkRecipe = new Recipe(numIngredients, ingredients, glassware, instructions);

      // create a Drink object
      drinks[i] = new Drink(name, alchololPercentage, pairing, drinkRecipe);

      input.ignore();
    }

    input.close();
}

void DrinkLibrary::makeNew() {
    ofstream output;  // output file stream
    string fileName;
    string* ingredients;

    cout << "\n\tEnter the name of the new library file (ex. myDrinks.txt): ";
    cin >> fileName;
    output.open(fileName);
    if (output.fail()) {
        cout << "\n\t\tFailed to open output file." << endl;
        return;
    }

    // Write drinks to the file
    for (int i = 0; i < numDrinks; i++) {
        output << drinks[i]->getName() << "*"
               << drinks[i]->getAlcoholPercentage() << "*"
               << drinks[i]->getPairing() << "*"
               << drinks[i]->getRecipe()->getnumIngredients() << "*";

        ingredients = drinks[i]->getRecipe()->getIngredients();
        for (int j = 0; j < drinks[i]->getRecipe()->getnumIngredients(); j++) {
            output << ingredients[j] << (j < drinks[i]->getRecipe()->getnumIngredients() - 1 ? "*" : "");
        }

        output << "*" 
               << drinks[i]->getRecipe()->getGlassware() << "*" 
               << drinks[i]->getRecipe()->getInstructions() << "*" << endl;
    }

    output.close();
    cout << "\nNew drink library saved to " << fileName << endl;

    //Clean up dynamically allocated ingredients
    for (int i = 0; i < numDrinks; i++) {
        delete drinks[i]; 
    }
    delete[] drinks;                                      // clean up the drinks array
}

void DrinkLibrary::printDrinks()
{
    if (numDrinks <=0 )
    {
        cout << "\n\t\tNo drinks available." << endl;
        return;
    }

    for (int i = 0; i < numDrinks; i++)
    {
        // print Drink variables
        cout << "----------------------------------------------------" << endl;
        cout << "Drink #: "<< i + 1 << endl;
        cout << "\n\t\tName: " << drinks[i]->getName() << endl;
        cout << "\n\t\tAlcohol Percentage: " << drinks[i]->getAlcoholPercentage() << "%" << endl;
        cout << "\n\t\tPairing: " << drinks[i]->getPairing() << endl;

        // print ingredients
        string* ingredients = drinks[i]->getRecipe()->getIngredients();
        int numIngredients = drinks[i]->getRecipe()->getnumIngredients();
        cout << "\n\t\tIngredients: " << endl;
        for (int j = 0; j < numIngredients; j++)
        {
            cout << "\t\t * " << ingredients[j] << endl;
        }

        // print rest of Recipe
        cout << "\n\t\tGlassware: " << drinks[i]->getRecipe()->getGlassware() << endl;
        cout << "\nInstructions:\n\n " << drinks[i]->getRecipe()->getInstructions() << endl;
    }
}

//constructors
DrinkLibrary::DrinkLibrary()
{
    drinks = nullptr;
    numDrinks = 0;
}

DrinkLibrary::DrinkLibrary(Drink** drinks, int numDrinks)
{
    this->drinks = drinks;
    this->numDrinks = numDrinks;
}

//destructor
DrinkLibrary::~DrinkLibrary()
{
    for(int i = 0; i < numDrinks; i++)
        delete drinks[i];
    delete[] drinks;
    //cout << "\nDrinkLibrary deleted successfully" << endl;
}


//prints main menu
int DrinkLibrary::DisplayMenuGetChoice() {
    int choice;

    cout << "----------------------------------------------------"
         << "\n\t\t    DRINK LIBRARY\n\n"
         << "----------------------------------------------------\n\n"
		 << "\t1 - Display all Drinks\n"
		 << "\t2 - Add a Drink\n"
		 << "\t3 - Edit a Drink\n"
         << "\t4 - Save New Drink Library\n"
         << "\t5 - Change Library File\n"
         << "\t6 - End the Program\n"
		 << "\nCHOICE: ";

    cin >> choice;
    
    return choice;
}

//adds a drink to the library
void DrinkLibrary::addDrink() {
    string drinkName, pairing, glassware, instructions;
    int alcoholPercentage, numIngredients;
    
    cout << "\nAdding Drink:\n";

    //gets the drinks infromation from the user
    cin.ignore();
    cout << "\t\tEnter Drink Name: ";
    getline(cin, drinkName);
    cout << "\t\tEnter the alcohol Percentage: ";
    cin >> alcoholPercentage;
    cin.ignore();
    cout << "\t\tEnter a Pairing: ";
    getline(cin, pairing);
    cout << "\t\tNumber of Ingredients: ";
    cin >> numIngredients;
    cin.ignore();
    string* ingredients = new string[numIngredients];
    for (int j = 0; j < numIngredients; j++) {
        cout << "\t\tIngredient #" << (j + 1) << ": ";
        getline(cin, ingredients[j]);
    }

    cout << "\t\tGlassware: ";
    getline(cin, glassware);

    cout << "\t\tInstructions (type full instructions before hitting enter): ";
    getline(cin, instructions);

    // Create a new Recipe object
    Recipe* drinkRecipe = new Recipe(numIngredients, ingredients, glassware, instructions);

    // creates a new Drink object
    Drink* newDrink = new Drink(drinkName, alcoholPercentage, pairing, drinkRecipe);

    //creates a placeholder array of drinks
    Drink** newDrinksArray = new Drink*[(numDrinks+1)];

    //makes the new array and the old array equal and then deletes the old array
    for(int i = 0; i < numDrinks; i++) {
        newDrinksArray[i] = drinks[i];
    }
    newDrinksArray[numDrinks] = newDrink;

    //delete newDrink;
    delete[] drinks;

    drinks = newDrinksArray;

    numDrinks++;

}

//removes a drink from the drinks array given an index
void DrinkLibrary::remove(int index) {
    int position = 0;

    //checks if the index is valid
    if(index < 0 || index >= numDrinks) {
        cout << "Invalid index.\n";
        return;
    }

    //creates a drink array of drinks equal to the old array excluding the index being removed
    Drink** newDrinksArray = new Drink*[numDrinks-1];
    for(int i = 0; i < numDrinks; i++) {
        if(i != index) {
            newDrinksArray[position] = drinks[i];
            position++;
        } else
            delete drinks[i];
    }

    delete[] drinks;

    drinks = newDrinksArray;
    numDrinks--;

}

void DrinkLibrary::editDrinks() {
    int drinkIndex, choice, alcoholPercentage, numIngredients;
    string drinkName, pairing, glassware, instructions;
    string* newIngredients = nullptr;
    
    //displays all drink names and assigns them an index
    cout << "\n\tDisplaying All Drinks:\n\n";
    for(int i = 0; i < numDrinks; i++)
        cout << "\t(" << i+1 << ") Drink Name: " << drinks[i]->getName() << endl;
    
    //asks the user for the index of the drink they want to edit
    cout << "\n\tWhich Drink do you want to Edit: ";
    cin >> drinkIndex;
    drinkIndex--;
    cout << "\n\tEditing: " << drinks[drinkIndex]->getName() << endl;

    while(drinkIndex >= numDrinks || drinkIndex < 0) {
        cout << "Invalid Selection!\nWhich Drink do you want to Edit: ";
        cin >> drinkIndex;
        drinkIndex--;
    }

    cout << "\t\t1 - Edit Name\n"
         << "\t\t2 - Edit Alcohol Percentage\n"
         << "\t\t3 - Edit Pairing\n"
         << "\t\t4 - Edit Ingredients\n"
         << "\t\t5 - Edit Glassware\n"
         << "\t\t6 - Edit Instructions\n"
         << "\t\t7 - Remove Drink\n"
         << "\t\t8 - Back to Main\n"
         << "\nCHOICE: ";

    cin >> choice;
    cout << endl;


    switch(choice) {
        case 1:
            //edits the drinks name
            cin.ignore();
            cout << "New Drink Name: ";
            getline(cin, drinkName);
            drinks[drinkIndex]->setName(drinkName);
            break;

        case 2:
            //edits the alcohol percentage
            cout << "New Alcohol Percentage: ";
            cin >> alcoholPercentage;
            drinks[drinkIndex]->setAlc(alcoholPercentage);
            break;

        case 3:
            //edits the drinks pairing
            cin.ignore();
            cout << "New Drink Pairing: ";
            getline(cin, pairing);
            drinks[drinkIndex]->setPairing(pairing);
            break;

        case 4:
            //creates new ingredients for a drink
            cout << "\t\tNumber of Ingredients: ";
            cin >> numIngredients;
            
            cin.ignore();
            newIngredients = new string[numIngredients];
            for (int j = 0; j < numIngredients; j++) {
                cout << "\t\tIngredient #: " << (j + 1) << ": ";
                getline(cin, newIngredients[j]);
            }
            delete[] drinks[drinkIndex]->getRecipe()->getIngredients();

            drinks[drinkIndex]->getRecipe()->setIngredients(newIngredients);
            drinks[drinkIndex]->getRecipe()->setNumIngredients(numIngredients);

            break;
        case 5:
            //edits glassware
            cin.ignore();
            cout << "New Drink Glassware: ";
            getline(cin, glassware);
            drinks[drinkIndex]->getRecipe()->setGlassware(glassware);
            break;
        case 6:
            //edits drink instructions
            cin.ignore();
            cout << "New Drink Instructions (type full instructions before hitting enter): ";
            getline(cin, instructions);
            drinks[drinkIndex]->getRecipe()->setInstructions(instructions);
            break;
        case 7:
            //removes the selected drink
            remove(drinkIndex);
            cout << "Drink " << (drinkIndex+1) << " Removed\n";
            break;
        case 8:
            cout << "Returning to Main Menu.\n";
            break;
        default:
            cout << "Invalid choice Please try again.\n";
    }
    cout << endl;
}