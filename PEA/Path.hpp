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
    vector<int> apath;
    
    int distance;

    bool tsp;
    
public:
    Path(vector<city> import);
    Path(vector<city> import, int dist);
    
    Path(vector<int> import);
    Path(int dimension);
    Path(vector<int> newpath, int dist);
    
    int calculate();
    int calculateP(vector<int> pathB);
    int calculateA(vector<vector<int>> matrix);
    double distanceTo(city from, city to);
    void swap(int first, int second);
    void swapA(int first, int second);
    
    vector<city> getVector();
    vector<int> getPath();
    int getDistance();
    
};

#endif /* Path_hpp */
