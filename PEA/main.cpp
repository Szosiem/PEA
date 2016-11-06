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

double temperature = 10000;
double coolingRate = 0.00001;

int showMenu()
{
    int choice = 0;
    cout << endl << "# Select an operation:" << endl;
    cout << "#" << endl;
    cout << "# 1. Show file details" << endl;
    cout << "# 2. Print cities" << endl;
    cout << "#" << endl;
    cout << "# 3. Simulated Annealing" << endl;
    cout << "# 4. Brute force" << endl;
    cout << "#" << endl;
    cout << "# 9. Settings" << endl;
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
    bool tsp;
    Tools *file = nullptr;
    while (reading)
    {
        cout << "\n\nType 'gen' to create new instance\nEnter file name: ";
        cin >> filename;
        
        if (filename == "gen")
        {
            string name, type;
            int dimension, maxvalue;
            cout << "Generating file started" << endl;
            cout << "Please type folowing values..." << endl;
            cout << "NAME: ";
            cin >> name;
            cout << "TSP or ATSP: ";
            cin >> type;
            cout << "DIMENSION: ";
            cin >> dimension;
            
            cout << "Type range of vaules : from 0 to ";
            cin >> maxvalue;
            
            ofstream generate;
            
            generate.open("/Users/krystian/Desktop/PEA/Generated/" + name  + "." + type);
            generate << "NAME: " << name << endl;
            generate << "TYPE: " << type << endl;
            if (type == "TSP")
            {
                generate << "COMMENT: generated file" << endl;
                generate << "DIMENSION: " << dimension << endl;
                generate << "EDGE_WEIGHT_TYPE: EUC_2D\nNODE_COORD_SECTION\n";
                for (int i = 0; i < dimension; i++)
                {
                    generate << i+1 << " " << rand() % maxvalue+1 << ".0 " << rand() % maxvalue+1 << ".0" << endl;
                }
            }
            else
            {
                
            }
            generate << "EOF";
            generate.close();

            filename = "Generated/" + name + "." + type;
        }
        
        file = new Tools("/Users/krystian/Desktop/PEA/" + filename);
        
        switch (file->readFile()) {
            case 0:
                reading = false;
                break;
            case -1:
            {
                delete file;
                cout << "Error while opening file!" << endl;
            }
                break;
            case -2:
            {
                delete file;
                cout << "Error while opening file! Unsupported file." << endl;
            }
                break;
                
            default:
                break;
        }
        
    }
    
    tsp = file->isTSP();
    
    cout << "##########" << endl;
    cout << "File details:" << endl;
    cout << file->showDetails();
    cout << "##########" << endl;
    
    Cities *state = nullptr;
    
    if (tsp)
    {
        state = new Cities(file->getVectorX(),file->getVectorY());
    }
    else
    {
        state = new Cities(file->getMatrix());
    }
    
    
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
                double temp = temperature;
                double coolRate = coolingRate;
                
                cout << endl << "Starting temperature is " << temp << endl;
                cout << "Cooling Rate is " << 1-coolRate << endl;
                
                if (tsp)
                {
                    int sizeOfState = state->getSize();
                    
                    Path *currentPath = new Path(state->getCities());
                    
                    cout << "Current distance is : \t" << to_string((int)currentPath->calculate()) << endl;
                    
                    Path *bestPath = new Path(currentPath->getVector());
                    bestPath->calculate();
                    
                    clock_t begin = clock();
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
                    float stop = float(clock() - begin) / CLOCKS_PER_SEC;
                    int sec = int(stop) % 60;
                    int min = stop / 60;
                    cout << "Time of execution: " << min << " [min] " << sec << " [s]" << endl;
                    //cout << "Time of execution: " << float( clock() - begin) / CLOCKS_PER_SEC << " [s]" << endl;
                    cout << "Best distance is : \t\t" << bestPath->getDistance() << endl;
                    delete bestPath;
                    delete currentPath;

                }
                else
                {
                    int sizeOfState = file->getDimension();
                    
                    Path *currentPath = new Path(sizeOfState);
                    
                    cout << "Current distance is : \t" << to_string((int)currentPath->calculateA(state->getMatrix())) << endl;
                    
                    Path *bestPath = new Path(currentPath->getPath());
                    bestPath->calculateA(state->getMatrix());
                    
                    clock_t begin = clock();
                    while (temp > 1)
                    {
                        Path *newPath = new Path(currentPath->getPath());
                        
                        int position1 = (int) (rand() % sizeOfState);
                        int position2 = (int) (rand() % sizeOfState);
                        
                        newPath->swapA(position1, position2);
                        
                        int currentEnergy = currentPath->calculateA(state->getMatrix());
                        int neighbourEnergy = newPath->calculateA(state->getMatrix());
                        
                        if (decide(currentEnergy, neighbourEnergy, temp) > (double)((rand() % 101 )* 0.01)) {
                            delete currentPath;
                            currentPath = new Path(newPath->getPath(), newPath->getDistance());
                        }
                        
                        if (currentPath->getDistance() < bestPath->getDistance()) {
                            delete bestPath;
                            bestPath = new Path(currentPath->getPath(), currentPath->getDistance());
                        }
                        delete newPath;
                        temp *= 1 - coolRate;
                        
                    }
                    float stop = float(clock() - begin) / CLOCKS_PER_SEC;
                    int sec = int(stop) % 60;
                    int min = stop / 60;
                    cout << "Time of execution: " << min << " [min] " << sec << " [s]" << endl;
                    cout << "Best distance is : \t\t" << bestPath->getDistance() << endl;
                    delete bestPath;
                    delete currentPath;
                }
            }
                break;
            
            case 4:
            {
                clock_t begin = clock();
                if (tsp)
                {
                    Path *currentPath = new Path(state->getCities());
                    int size = state->getSize();
                    // create permutation
                    int array[size];
                    
                    for (int i = 0; i < size; i++) {
                        array[i]=i;
                    }
                    /*
                    vector<vector<int>> paths;
                    
                    do
                    {
                        vector<int> temp;
                        for (int i = 0 ; i < state->getSize(); i++)
                        {
                            temp.push_back(array[i]);
                        }
                        paths.push_back(temp);

                    }
                    while (next_permutation(array,array + state->getSize()));
                    
                    for (int i = 0; i < paths.size(); i++)
                    {
                        currentPath->calculateP(paths.at(i));
                    }
                    */
                    
                    do
                    {
                        currentPath->calculateP(array, size);
                        
                    }while (next_permutation(array, array + size));
                    
                    float stop = float(clock() - begin) / CLOCKS_PER_SEC;
                    int sec = int(stop) % 60;
                    int min = stop / 60;
                    cout << "Time of execution: " << min << " [min] " << sec << " [s]" << endl;
                    cout << endl << "Best distance is : \t" << currentPath->getDistance() << endl;
                    delete currentPath;
                }
            }
                break;
            
            case 9:
            {
                cout << endl << "Current temperature: " << temperature;
                cout << endl << "Current cool rate: " << coolingRate;
                cout << endl << "New temperature: ";
                cin >> temperature;
                cout << "New cool rate: ";
                cin >> coolingRate;
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
