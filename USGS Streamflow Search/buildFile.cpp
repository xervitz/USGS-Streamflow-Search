//
//  buildFile.cpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#include "buildFile.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "stringConvert.hpp"

class stringConvert;

/*
 *This whole class is pretty simple. It's mostly input/output with a lot of checks for user
 *input. Anything that looks remotely strange is likely to do with me formating the
 *file correctly so that it is easy to read in later in the program.
 */
buildFile::~buildFile() {}

buildFile::buildFile() {
    string input = "";
    string check = "";
    string date1 = "", date2 = "";
    file = "";
    name = "";
    fileCount = 0;
    dateCount = 0;
    
    cout << "Welcome to the file builder"
        "You can enter as many .csv USGS data files as you like"
        "along with as many dates as you like."
        "The files created here can be loaded in the cfs date search"
        "for easier seraching of multiple csv and dates."
        "All files mentioned will be searched for each set of dates"
        "\n\n"
        "There is no need to specify file extnesions."
        "The program will assume .csv for data files "
        "and will use a custom file extension for saved files.\n\n"
        "enter \"exit\" at any time to leave and go back to the main menu\n\n";
    
    while(check.compare("no") != 0) {
        cout << "Enter input data file (csv file): ";
        cin >> input;
        cout << "File specified is " << input << ". Is this correct (yes/no): ";
        cin >> check;
        if((check.compare("yes"))) {
            check = "";
            continue;
        }
        fileCount++;
        file = file + input + ".csv\n";
        cout << "Would you like to add another data file (yes/no)? ";
        cin >> check;
    }
    
    file.erase(file.size() - 1);
    input = "";
    check = "";
    
    while (check.compare("yes")) {
        
        cout << "Enter start date: ";
        cin >> date1;
        cout << "Enter end date: ";
        cin >> date2;
        
        if(!dateCheck(date1)) {
            cout << "the first date is invalid. Please re-enter\n";
        }
        else if(!dateCheck(date2)) {
            cout << "the second date is invalid. Please re-enter\n";
        }
        else {
            date = date + date1 + "," + date2 + "\n";
            dateCount++;
            cout << "Are you finished entering dates (yes/no)? ";
            cin >> check;
        }
    }
    makeFile();
}

void buildFile::makeFile() {
    bool valid = 0;
    cout << file << endl;
    do{
        cout << "What would you like to call the file? ";
        cin >> name;
        name = name + ".cfs";
        ifstream f(name.c_str());
        if((f.good())) {
            cout << "That file already exists. Do you want to over write it (yes/no)? ";
            string y;
            cin >> y;
            
            if(y.compare("yes") != 0) {
                valid = 1;
            }
        }
        f.close();
    }while(valid);
    
    ofstream output;
    output.open(name);
    output << "#" << fileCount << endl << file << endl << "#" << dateCount << endl << date;
    output.close();
    
    saveFile();
}

bool buildFile::dateCheck(string s) {
    string::size_type pos = 0, pos2;
    string num = "";
    bool good = 0;
    if(s.find("/") != string::npos) {
        good = 1;
        pos = s.find("/",pos);

        for(string::size_type i = 0; i < pos; i++) {
            num = num + s[i];
        }
        if(stringConvert::stringToInt(num) > 12) good = 0;
        pos2 = pos + 1;
        pos = s.find("/",pos + 1);
        
        num = "";
        for(string::size_type i = pos2; i < pos; i++) {
            num = num + s[i];
        }
        if(stringConvert::stringToInt(num) > 31) good = 0;

        num = "";
        for(string::size_type i = pos + 1; i < s.length(); i++) {
            num = num + s[i];
        }

        if(stringConvert::stringToInt(num) > 9999 || stringConvert::stringToInt(num) < 1000) good = 0;
    }
    return good;
}

void buildFile::saveFile() {
    ifstream f("fl.cfs");
    
    if(!(stringConvert::fileToString(f)).compare("")) {
        f.close();
        ofstream o("fl.cfs");
        o << name;
        o.close();
    }
    else {
        f.close();
        ofstream o("fl.cfs", std::ios_base::app);
        o << endl << name;
        o.close();
    }
}