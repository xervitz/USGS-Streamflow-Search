//
//  buildFile.hpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#ifndef buildFile_hpp
#define buildFile_hpp

#include <stdio.h>
#include <string>

using namespace std;

class buildFile {
public:
    buildFile();
    ~buildFile();
    void makeFile();
    
private:
    string file, name, date;
    int fileCount, dateCount;
    bool dateCheck(string s);
    void saveFile();
};

#endif /* buildFile_hpp */
