//
//  Path.cpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-05.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#include "Path.hpp"

Path::Path(vector<city> import)
{
    this->tsp = false;
    this->distance = 0;
    this->path.swap(import);
}

Path::Path(vector<city> import, int dist)
{
    this->tsp = false;
    this->distance = dist;
    this->path.swap(import);
}

Path::Path(int dimension)
{
    this->tsp = true;
    this->distance = 0;
    this->apath.resize(dimension);
    for (int i = 0; i < dimension; i++)
    {
        this->apath.at(i) = i;
    }
}

Path::Path(vector<int> import)
{
    this->tsp = true;
    this->distance = 0;
    this->apath.swap(import);
}

Path::Path(vector<int> newpath, int dist)
{
    this->tsp = true;
    this->distance = dist;
    this->apath.swap(newpath);
}

int Path::calculate()
{
    double dist = 0;
    
    for (int i = 0; i < path.size(); i++)
    {
        if (i+1 < path.size())
        {
            dist += distanceTo(this->path.at(i), this->path.at(i+1));
        }
        else
        {
            dist += distanceTo(this->path.at(i), this->path.at(0));
        }
    }
    this->distance = (int)dist;
    
    return this->distance;
}

int Path::calculateA(vector<vector<int>> matrix)
{
    double dist = 0;
    
    for (int i = 0; i < apath.size(); i++)
    {
        if (i+1 < apath.size())
        {
            
            dist += matrix[apath.at(i)][apath.at(i+1)];
        }
        else
        {
            dist += matrix[apath.at(apath.size()-1)][apath.at(0)];
        }
    }
    this->distance = (int)dist;
    return this->distance;
}

double Path::distanceTo(city from, city to)
{
    int xDistance = abs(from.x - to.x);
    int yDistance = abs(from.y - to.y);
    
    double distance = sqrt(pow((double)xDistance, 2.0) + pow((double)yDistance, 2.0));
    
    return distance;
}

void Path::swap(int first, int second)
{
    city temporary = this->path.at(first);
    
    this->path.at(first) = this->path.at(second);
    this->path.at(second) = temporary;
}

void Path::swapA(int first, int second)
{
    int temporary = this->apath.at(first);
    
    this->apath.at(first) = this->apath.at(second);
    this->apath.at(second) = temporary;
}

vector<city> Path::getVector()
{
    return this->path;
}

vector<int> Path::getPath()
{
    return apath;
}

int Path::getDistance()
{
    return this->distance;
}