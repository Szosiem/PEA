//
//  Tools.hpp
//  PEA
//
//  Created by Krystian Sliwinski on 2016-11-04.
//  Copyright © 2016 Krystian Sliwinski. All rights reserved.
//

#ifndef Tools_hpp
#define Tools_hpp

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Tools
{
private:
    string file;
    
    string name;
    string comment;
    bool type;
    int dimension;
    
    vector <int> x;
    vector <int> y;
    
    vector<vector<int>> matrix;
    
public:
    Tools(string filename);
    ~Tools();
    
    int readFile();
    string showDetails();
    string printCities();
    
    int getDimension();
    
    int getX(int index);
    int getY(int index);
    bool isTSP();
    string getName();
    
    vector<int> getVectorX();
    vector<int> getVectorY();
    vector<vector<int>> getMatrix();
};

#endif /* Tools_hpp */
