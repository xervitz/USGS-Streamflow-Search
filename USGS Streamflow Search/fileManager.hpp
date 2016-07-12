//
//  fileManager.hpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/24/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#ifndef fileManager_hpp
#define fileManager_hpp

#include <stdio.h>
#include <string>

using namespace std;

class fileManager {
public:
    fileManager();
    ~fileManager();
    
private:
    string cfs;
    void deleteFile();
    void menu();
    //void editFile();
};

#endif /* fileManager_hpp */
