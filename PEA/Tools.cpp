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
    
    if (source.good())
    {
        /*
        for (int i = 0; i < 4; i++)
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
         */
        
        do
        {
            getline(source, line);
            index = line.find(':')+2;
            
            string temp = line.substr(0, index-2);
            
            temp.erase(remove(temp.begin(), temp.end(),' '));
            
            if (temp == "NAME")
            {
                this->name = line.substr(index);
            }
            else if (temp == "TYPE")
            {
                if (line.substr(index) == "TSP")
                {
                    this->type = true;
                }
                else this->type = false;
            }
            else if (temp == "COMMENT")
            {
                this->comment = line.substr(index);
            }
            else if (temp == "DIMENSION")
            {
                this->dimension = stoi(line.substr(index));
            }
            else if (temp == "EDGE_WEIGHT_TYPE")
            {
                if (this->type)
                {
                    if (line.substr(index) != "EUC_2D")
                    {
                        return -2;
                    }
                }
            }
            
        }while (line.compare("EDGE_WEIGHT_SECTION") != 0 && line.compare("NODE_COORD_SECTION") != 0);
        
        
        
        if (this->type)
        {
            /*
            for (int i = 0; i < this->dimension; i++) {
                getline(source,line);
                index = line.find(' ')+1;
                line = line.substr(index);
                index = line.find(' ');
                this->x.push_back(stoi(line.substr(0,index-2)));
                this->y.push_back(stoi(line.substr(index + 1, line.length() - index - 3)));
            }
             */
            int jump = 0;
            do
            {
                float temp;
                if (jump % 3 == 0)
                {
                    source >> temp;
                }
                else if (jump % 3 == 1)
                {
                    source >> temp;
                    this->x.push_back((int)temp);
                }
                else if (jump % 3 == 2)
                {
                    source >> temp;
                    this->y.push_back((int)temp);
                }
                jump++;
            }while (jump < dimension*3);
        }
        else
        {
            
            matrix.resize(dimension);
            for ( int i = 0 ; i < dimension ; i++ )
                matrix[i].resize(dimension);
            
            for (int i = 0; i < dimension; i++)
            {
                for (int j = 0; j < dimension; j++)
                {
                    source >> matrix[i][j];
                }
            }
        }
    }
    
    else
    {
        return -1;
    }
    
    source.close();
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
            cities += to_string(i) + ".\t" + to_string(x.at(i)) + "\t\t" + to_string(y.at(i)) + "\n";
        }
    }
    else
    {
        cities += "_|\t";
        for (int i = 0; i < dimension; i++) {
            cities += to_string(i+1) + ".\t";
        }
        cities += "\n";
        for (int i = 0; i < dimension; i ++)
        {
            cities += to_string(i+1) + ".\t";
            for (int j = 0; j < dimension; j++)
            {
                cities += to_string(matrix[i][j]) + "\t";
            }
            cities += "\n";
        }
        
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

vector<vector<int>> Tools::getMatrix()
{
    return matrix;
}