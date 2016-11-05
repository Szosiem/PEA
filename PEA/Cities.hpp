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

public:
    Cities(vector<int> x, vector<int> y);
    ~Cities();
    
    vector<city> getCities();
    
    int getSize();
    
};

#endif /* Cities_hpp */
