//
//  Cities.cpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-04.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#include "Cities.hpp"

Cities::Cities(vector<int> x, vector<int> y)
{
    city temporary;
    for (int i = 0; i < x.size(); i++) {
        temporary.x = x.at(i);
        temporary.y = y.at(i);
        
        this->cities.push_back(temporary);
    }
}

Cities::Cities(vector<vector<int>> import)
{
    this->citiesA.swap(import);
}

Cities::~Cities()
{
    
}

vector<city> Cities::getCities()
{
    return this->cities;
}

vector<vector<int>> Cities::getMatrix()
{
    return citiesA;
}

int Cities::getSize()
{
    return (int)this->cities.size();
}