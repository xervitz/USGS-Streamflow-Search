//
//  mainMenu.cpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#include "mainMenu.hpp"
#include <iostream>
#include <string>
#include "buildFile.hpp"
#include "arrayBuilder.hpp"
#include "fileManager.hpp"

using namespace std;

class mainMenu;
class arrayBuilder;
class buildFile;
class fileManager;

mainMenu::mainMenu() {
    clearScreen();
    while(true) {
        cout << "Main Menu" << endl;
        cout << "1: Build Storm List File" << endl;
        cout << "2: CFS Date Search" << endl;
        cout << "3: Manage Saved Data files" << endl;
        cout << "4. Exit" << endl;
        
        cin >> input;
        
        if(!input.compare("1")) {
            clearScreen();
            buildFile* l = new buildFile();
            clearScreen();
            delete l;
            cout << "File saved to local directory\n\n";
        }
        else if(!input.compare("2")) {
            clearScreen();
            arrayBuilder* l = new arrayBuilder();
            clearScreen();
            delete l;
        }
        else if(!input.compare("3")) {
            clearScreen();
            fileManager* l = new fileManager();
            clearScreen();
            delete l;
        }
        else if(!input.compare("4")) {
            exit(97);
        }
        else {
            cout << "Invalid Input.\n";
        }
        input = "";
    }
}

void mainMenu::clearScreen()
{
    cout << string(100, '\n');
}