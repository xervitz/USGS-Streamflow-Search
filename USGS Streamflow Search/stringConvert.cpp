//
//  stringConvert.cpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#include "stringConvert.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class stringConvert;
/*
 *Simple set of functions to make other code easier to read.
 *These are all things I do often. Converting between strings, files, and ints
 *isn't fun in c++ so these just do all that.
 */
string stringConvert::intToString(int i) {
    string s;
    ostringstream c;
    c<<i;
    s = c.str();
    return s;
}

int stringConvert::stringToInt(string s) {
    int i;
    stringstream c(s);
    c>>i;
    return i;
}

void stringConvert::stringToFile(string s, string name) {
    ofstream f(name);
    f << s;
    f.close();
}

string stringConvert::fileToString(istream& f) {
    string n;
    for(char c; f.get(c); n += c);
    return n;
}

int stringConvert::charToInt(char c) {
    int i = c - 48;
    return i;
}