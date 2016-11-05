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

Cities::Cities(int ** import)
{
    matrix = new int*[10];
    for (int i = 0; i < 10 ; i++) {
        matrix[i] = new int[10];
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = import[i][j];
        }
    }
}

Cities::~Cities()
{
    
}

vector<city> Cities::getCities()
{
    return this->cities;
}

int Cities::getSize()
{
    return (int)this->cities.size();
}