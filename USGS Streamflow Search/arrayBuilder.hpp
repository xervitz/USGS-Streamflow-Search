//
//  arrayBuilder.hpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#ifndef arrayBuilder_hpp
#define arrayBuilder_hpp

#include <stdio.h>
#include <string>
#include "stringConvert.hpp"

using namespace std;
class arrayBuilder {
public:
    arrayBuilder();
    ~arrayBuilder();
    
private:
    void arrayMaker(istream& s);
    void buildString();
    void manualEntry();
    void fileEntry();
    void makeHourly();
    void findStorm();
    void buildFileOutput(string csv, string* dateSet, int dateNum);
    
    int DATAPOINTS;
    int HOURPOINTS;
    int start, end, found;
    string sDate, eDate, outputString, stream;
    int* hourlyFlow;
    
    string* hourlyDate;
    string* date;
    string* flowRate;
    
};

#endif /* arrayBuilder_hpp */
