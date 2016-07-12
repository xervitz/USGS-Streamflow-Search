//
//  mainMenu.hpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#ifndef mainMenu_hpp
#define mainMenu_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class mainMenu {
public:
    mainMenu();
private:
    void clearScreen();
    string input;
};
#endif /* mainMenu_hpp */
