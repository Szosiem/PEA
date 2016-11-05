//
//  Path.hpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-05.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <vector>

#include "Cities.hpp"

class Path
{
private:
    vector<city> path;
    int distance;
    
public:
    Path(vector<city> import);
    Path(vector<city> import, int dist);
    
    int calculate();
    double distanceTo(city from, city to);
    void swap(int first, int second);
    
    vector<city> getVector();
    int getDistance();
    
};

#endif /* Path_hpp */
