//
//  Tools.cpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-04.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#include "Tools.hpp"

Tools::Tools(string filename)
{
    this->file = filename;
}

Tools::~Tools()
{
    
}

int Tools::readFile()
{
    string line;
    string::size_type index;
    ifstream source(this->file);
    
    if (source.is_open())
    {
        for (int i = 0; i < 6; i++)
        {
            getline(source,line);
            index = line.find(':')+2;
            switch (i)
            {
                case 0:
                    this->name = line.substr(index);
                    break;
                    
                case 1:
                {
                    if (line.substr(index) == "TSP") {
                        this->type = true;
                    }
                    else
                    {
                        this->type = false;
                    }
                }
                    break;
                    
                case 2:
                    this->comment = line.substr(index);
                    break;
                    
                case 3:
                    this->dimension = stoi(line.substr(index));
                    break;
                    
                default:
                    break;
            }
        }
        if (this->type) {
            for (int i = 0; i < this->dimension; i++) {
                getline(source,line);
                index = line.find(' ')+1;
                line = line.substr(index);
                index = line.find(' ');
                this->x.push_back(stoi(line.substr(0,index-2)));
                this->y.push_back(stoi(line.substr(index + 1, line.length() - index - 3)));
            }

        }
        else
        {
            
        }
    }
    else
    {
        return -1;
    }
    
    return 0;
}

string Tools::showDetails()
{
    string informations;

    string type = this->type ? "TSP" : "ATSP";
    informations = "Name: " + this->name + "\nType of problem: " + type + "\nDimension: " + to_string(this->dimension) + "\nComment: " + this->comment + "\n";
    
    return informations;
}

string Tools::printCities()
{
    string cities;
    
    if (this->type) {
        for (int i = 0; i < this->dimension; i++) {
            cities += to_string(i) + ".\t" + to_string(x.at(i)) + "\t" + to_string(y.at(i)) + "\n";
        }
    }
    else
    {
        
    }
    
    return cities;
}

int Tools::getX(int index)
{
    return x.at(index);
}

int Tools::getY(int index)
{
    return y.at(index);
}


int Tools::getDimension()
{
    return dimension;
}

bool Tools::isTSP()
{
    return this->type;
}

vector<int> Tools::getVectorX()
{
    return x;
}

vector<int> Tools::getVectorY()
{
    return y;
}