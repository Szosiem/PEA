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
    this->distance = 0;
    this->path.swap(import);
}

Path::Path(vector<city> import, int dist)
{
    this->distance = dist;
    this->path.swap(import);
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

vector<city> Path::getVector()
{
    return this->path;
}

int Path::getDistance()
{
    return this->distance;
}