/*
    Title: DrinkLibrary.cpp
    Project 1 - CSC1310
    Authors: Levi, Brody, Ryan, Justin
    Date: 9/18/2024
 */
#include "DrinkLibrary.h"   // header file
#include <fstream>          // allow input from input text file
#include <iostream>
#include "DrinkFunctions.h"
#include "Recipe.h"

using namespace std;

void DrinkLibrary::readIn()
{
    ifstream input;                 // cin file

    // choose which file to read from
    int choice;
    string fileName;
    do{
        cout << "\n\nWhich file would you like to read from?\n";
        cout << "\t1. Working Library\n";
        cout << "\t2. Test Case\n";
        cout << "\t3. Back\n";
        cin >> choice;
        while(choice < 1 || choice > 3)
        {
            cout << "\nInvalid selection!";
            cin >> choice;
        }
        switch(choice)
        {
            case 1:
                fileName = "WORKING_LIBRARY.txt";
                break;

            case 2:
                fileName = "TEST_CASE.txt";
                break;
        }

    }while(choice != 3);

    input.open(fileName);

    if (input.fail())               // fail case
    {
        cout << "\n\t\tFailed to open input file. Check for input.txt." << endl;
        return;
    }
    
    drinks = new Drink*[numDrinks]; // dynamically allocate array of pointers to Drink

    for (int i = 0; i < numDrinks; i++)
    {
      string name, pairing, glassware, instructions;
      string* ingredients;
      int alchololPercentage, numIngredients;

      // obtain values for parameters from input file
      getline(input, name, '*');

      input >> alchololPercentage;
      input.ignore();               // ignore *

      getline(input, pairing, '*');

      input >> numIngredients;
      input.ignore();               // ingore *
      ingredients = new string[numIngredients];
      for(int j = 0; j < numIngredients; j++)
      {
        getline(input, ingredients[j], '*');
      }

      getline(input, glassware, '*');

      getline(input, instructions, '*');

      // create a Recipe object
      Recipe drinkRecipe(ingredients, glassware, instructions);

      // create a Drink object
      drinks[i] = new Drink(name, alchololPercentage, pairing, drinkRecipe);
    }

    input.close();
}

//prints main menu
int DrinkLibrary::DisplayMenuGetChoice() {
    int choice;

    cout << "WELCOME MESSAGE\n"
		 << "1 - Display\n"
		 << "2 - Add\n"
		 << "3 - Remove\n"
         << "4 - End the Program\n"
		 << "\nCHOICE: ";

    cin >> choice;
    
    return choice;
}

void DrinkLibrary::printDrinks() {
    cout << "Displaying All Drinks:\n";

    for(int i = 0; i < numDrinks; i++)
        drinks[i]->printDrink();
}

//adds a drink to the library - WIP
void DrinkLibrary::addDrink() {
    string drinkName, pairing;
    double alcoholPercentage;
    Recipe* drinkRecipe;
    
    cout << "Adding Drink:\n";

    cin.ignore();
    cout << "\nEnter Drink Name: ";
    getline(cin, drinkName);
    cout << "Enter the alcohol Percentage: ";
    cin >> alcoholPercentage;
    cin.ignore();
    cout << "Enter a Pairing: ";
    getline(cin, pairing);

    //drinkRecipe.createRecipe();

    Drink* newDrink = new Drink(drinkName, alcoholPercentage, pairing, drinkRecipe);

    Drink** newDrinksArray = new Drink*[numDrinks+1];
    for(int i =0; i < numDrinks; i++)
        newDrinksArray[i] = drinks[i];
    newDrinksArray[numDrinks] = newDrink;

    delete[] drinks;
    drinks = newDrinksArray;
    numDrinks++;

}