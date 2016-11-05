//
//  main.cpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-04.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#include <iostream>
#include <ctime>

#include "Tools.hpp"
#include "Cities.hpp"
#include "Path.hpp"

using namespace std;

int showMenu()
{
    int choice = 0;
    cout << endl << "# Select an operation:" << endl;
    cout << "#" << endl;
    cout << "# 1. Show file details" << endl;
    cout << "# 2. Print cities" << endl;
    cout << "#" << endl;
    cout << "# 3. Simulated Annealing" << endl;
    cout << "#" << endl;
    cout << "# 0. Exit" << endl;
    cout << "\n\tYour choice : ";
    cin >> choice;
    
    return choice;
}

/*
void reportHelper()
{
    
}
*/

double decide(int energy, int newEnergy, double temperature)
{
    if (newEnergy < energy) {
        return 1.0;
    }
    return exp((energy - newEnergy)/temperature);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    srand((unsigned)time(NULL));
    
    string filename;
    bool reading = true;
    Tools *file = nullptr;
    while (reading)
    {
        cout << "\n\n\nEnter file name: ";
        cin >> filename;
        
        file = new Tools("/Users/krystian/Desktop/PEA/" + filename);
        
        if (file->readFile() != 0)
        {
            delete file;
            cout << "Error while opening file!" << endl;
        }
        else
        {
            reading = false;
        }
        
    }

    cout << "##########" << endl;
    cout << "File details:" << endl;
    cout << file->showDetails();
    cout << "##########" << endl;
    
    Cities *state = new Cities(file->getVectorX(),file->getVectorY());
    
    bool menu = true;
    
    while (menu) {
        switch (showMenu()) {
            case 0:
                menu = false;
                break;
                
            case 1:
            {
                cout << endl << file->showDetails();
            }
                break;
                
            case 2:
            {
                cout << endl << file->printCities();
            }
                break;
                
            case 3:
            {
                double temp = 10000;
                double coolRate = 0.000001;
                cout << endl << "Starting temperature is " << temp << endl;
                cout << "Cooling Rate is " << 1-coolRate << endl;
                int sizeOfState = state->getSize();
                
                Path *currentPath = new Path(state->getCities());
                
                cout << "Current distance is : \t" << to_string((int)currentPath->calculate()) << endl;
                
                Path *bestPath = new Path(currentPath->getVector());
                bestPath->calculate();
                
                while (temp > 1)
                {
                    Path *newPath = new Path(currentPath->getVector());
                    
                    int position1 = (int) (rand() % sizeOfState);
                    int position2 = (int) (rand() % sizeOfState);
                    
                    newPath->swap(position1, position2);
                    
                    int currentEnergy = currentPath->calculate();
                    int neighbourEnergy = newPath->calculate();
                    
                    if (decide(currentEnergy, neighbourEnergy, temp) > (double)((rand() % 101 )* 0.01)) {
                        delete currentPath;
                        currentPath = new Path(newPath->getVector(), newPath->getDistance());
                    }
                    
                    if (currentPath->getDistance() < bestPath->getDistance()) {
                        delete bestPath;
                        bestPath = new Path(currentPath->getVector(), currentPath->getDistance());
                    }
                    delete newPath;
                    temp *= 1 - coolRate;

                }
                cout << "Best distance is : \t\t" << bestPath->getDistance() << endl;
                delete bestPath;
                delete currentPath;
            }
                break;
            
            /* // report helper
            case 404:
            {
                reportHelper();
            }
                break;
            */
                
            default:
                cout << endl << "Wrong choice. Try again." << endl;
                break;
        }
    }
    
    delete file;
    delete state;
    return 0;
}
