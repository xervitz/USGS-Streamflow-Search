//
//  fileManager.cpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/24/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#include "fileManager.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "stringConvert.hpp"

class fileManager;
using namespace std;

fileManager::fileManager() {
    string file, input, input2;
    int count = 1, j = 0;
    char c;
    string::size_type spot;
    
    ifstream f("fl.cfs"); //reads in the file that stores all the save data
    
    cout << endl << "Available built files" << endl;
    
    file = stringConvert::fileToString(f);
    f.close();
    file.erase(file.size()); //erases the last char in the above file (it's a \n)
    file.insert(0, "1. ");
    do {                        //makes output a numbered list. Also inserts the list for easier searching later
        c = file[j];
        if(c == '\n') {
            count++;
            file.insert(j+1, stringConvert::intToString(count) + ". ");
        }
        j++;
    } while(c != '\0');
    
    cout << file;
    cout << "\n\nWhich file would you like to open? ";
    
    cin >> input;
    input = input + ". ";
    c = ' ';
    spot = file.find(input);
    spot += 3;
    
    cfs = "";
    
    c = file[spot];
    
    while(c != '\n' && c != '\0') { //finds where the user selected and pulls the .cfs file from that spot.
        cfs = cfs + c;
        spot++;
        c = file[spot];
    }
    
    cout << "\nWould you like to:\n1. Delete the file\n2. Edit the file (not implimented)\n3. Exit\n";
    
    cin >> input2;
    
    while (true) {
        if(stringConvert::stringToInt(input2) == 1) {
            deleteFile();
            break;
        }
        else if(stringConvert::stringToInt(input2) == 2) {
            //editFile();
            break;
        }
        else if(stringConvert::stringToInt(input2) == 3) {
            break;
        }
        else {
            cout << "Invalid input: ";
        }
    }
}

void fileManager::deleteFile() {
    string input;
    const char* file = cfs.c_str();
    
    cout << "Are you sure you want to delete " << cfs << "? This cannot be reversed (yes/no): ";
    cin >> input;
    if(!input.compare("yes")) {
        if(remove(file) != 0) { //if the file doesn't exist for some reason
            cout << "error deleting file" << endl;
        }
        else {
            ifstream f("fl.cfs");
            string input = stringConvert::fileToString(f); //pull file into a string
            f.close();
            
            string::size_type i = input.find(cfs); //find the file they want in fl.cfs
            
            if(i != 0) {
                input.erase(i - 1, cfs.size()); //if it exists anywhere but the first spot
            }                                   //we want to delete it and the \n before it
            else {
                input.erase(i, cfs.size()); //if it's the first one delete it and the \n after
            }
            
            ofstream o("fl.cfs");
            o << input; //write the new file
            o.close();
            
            cout << "File deleted";
        }
    }
}

fileManager::~fileManager() {
    
}