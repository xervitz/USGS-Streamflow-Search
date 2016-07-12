//
//  stringConvert.hpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#ifndef stringConvert_hpp
#define stringConvert_hpp

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;
class stringConvert {
public:
    static string intToString(int i);
    static int stringToInt(string s);
    static string fileToString(istream& f);
    static bool fileCheck();
    static void stringToFile(string s, string name);
    static int charToInt(char c);
};

#endif /* stringConvert_hpp */
