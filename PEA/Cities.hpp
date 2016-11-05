//
//  Cities.hpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-04.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#ifndef Cities_hpp
#define Cities_hpp

#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

struct city
{
    int x;
    int y;
};

class Cities
{
private:
    
    vector<city> cities;
    
    vector<vector<int>> citiesA;

public:
    Cities(vector<int> x, vector<int> y);
    Cities(vector<vector<int>> import);
    ~Cities();
    
    vector<city> getCities();
    vector<vector<int>> getMatrix();
    
    int getSize();
    
};

#endif /* Cities_hpp */
