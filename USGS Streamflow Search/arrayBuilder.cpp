//
//  arrayBuilder.cpp
//  USGS Streamflow Search
//
//  Created by Miles Necker on 6/15/16.
//  Copyright © 2016 Miles Necker. All rights reserved.
//

#include "arrayBuilder.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "stringConvert.hpp"
using namespace std;

class arrayBuilder;
class stringConvert;

arrayBuilder::arrayBuilder() {
    string input;
    cout << "1. Manual date entry\n";
    cout << "2. File date entry\n";
    cin >> input;
    if(!input.compare("1")) manualEntry();
    else if(!input.compare("2")) fileEntry();
    else {
        cout << "Invaild input. Returning to main menu.\n";
    }
}

void arrayBuilder::arrayMaker(istream& s) {
    string stream;
    int size = 0;
    char currC = ' ';
    int side = 0;
    int loop = 0;
    int pos = 0;
    string prevDate = "";
    string currDate = "";
    int errorsFound = 0;
    DATAPOINTS = 0;
    HOURPOINTS = 0;
    
    for(char c; s.get(c);stream += c) { //reads in the file character my character and turns it into a string (way easier to work with)
        size++; //keeps track of the total characters
        if (c == ',') {
            DATAPOINTS += 1; //keeps track of the number of datapoints
        }
    }
    
    while (pos < size) { //this first time is just a error checker
        currC = stream[pos]; //sets the current char to be one in the file
        
        if(currC == '\n') {
            side = 0; //keeps track of if we're reading a date or cfs
        }
        else if(currC == ','){
            if (currDate.compare(prevDate) == 0) { //a little check to remove potential doubled data points
                errorsFound++; //keeps track of errors for debugging
                DATAPOINTS--; //fixes the actual number of Datapoints for allocation later.
            }
            prevDate = currDate;
            currDate = "";
            side = 1;
        }
        else {
            if(side == 0) currDate += currC;
        }
        pos++;
    }
    side = 0;
    pos = 0;
    date = new string[DATAPOINTS]; //dynamically allocates the memory for the arrays
    flowRate = new string[DATAPOINTS];
    /* This bit works mostly like the one above. Loop keeps track of the position in the array
     * and I build the strings character by character pulling them out of the string I built
     * earlier. A while loop is used here as I only incriment the loop when I've hit a \n
     * character. There are a lot of ifs because some of the checks I do would seg fault
     * on the first run through, so I need to make sure they only run after the first data
     * point is recorded.
     */
    while (loop < DATAPOINTS) {
        currC = stream[pos];
        
        if(currC == '\n') {
            if(loop > 0) {
                if ((*(date + loop)).compare(*(date + loop - 1)) == 0) {
                    *(date + loop) = ""; //If I found one of the errors, don't record the point.
                    *(flowRate + loop) = "";
                }
                else {
                    loop++;
                }
            }
            else {
                loop++;
            }
            side = 0;
        }
        else if(currC == ',') {
            side = 1;
        }
        else {
            if(side == 0) {
                *(date + loop) += currC;
            }
            else {
                *(flowRate + loop) += currC;
            }
        }
        
        pos++;
    }
    makeHourly(); //I did this because I hate having huge functions.
}

arrayBuilder::~arrayBuilder() {
    delete [] hourlyFlow;
    delete [] hourlyDate;
    delete [] date;
    delete [] flowRate;
}

void arrayBuilder::manualEntry() {
    /*
     *This is a fairly simple function that just takes inputs and assigns them.
     *Fully manual entry. Will take one input before returning to main menu
     */
    string input;
    ifstream f;
    
    cout << endl << "Enter the file path to the USGS .csv file: ";
    cin >> input;
    f.open(input);
    
    cout << "Enter start date: ";
    cin >> sDate;
    
    cout << "Enter end date: ";
    cin >> eDate;
    
    arrayMaker(f);
    f.close();
    ofstream o("output.csv");
    o << outputString;
    o.close();
}

void arrayBuilder::fileEntry() {
    string input, file; //This function can get complicated as I reuse variables later in the function.
    int count = 1, j = 1;
    char c;
    std::string::size_type spot;
    string* csv;
    string* dateSet;
    
    ifstream f("fl.cfs"); //reads in the file that stores all the save data
    
    cout << endl << "Available built files" << endl;
    
    file = stringConvert::fileToString(f);
    f.close();
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
    
    input = "";
    
    c = file[spot];
    
    while(c != '\n' && c != '\0') { //finds where the user selected and pulls the .csv file from that spot.
        input = input + c;
        spot++;
        c = file[spot];
    }
    
    f.open(input);
    file = stringConvert::fileToString(f); //opens the .cfs file they specify and converts it to a string
    f.close();

    count = stringConvert::charToInt(file[1]); //grabs the number of csv files listed in the file
    csv = new string[count];
    int i = 3;
    j = 0;
    while(j < count) { //pulls each .csv name and stores it in a spot in a string array.
        while(file[i] != '\n') {
            *(csv + j) += file[i];
            i++;
        }
        i++;
        j++;
    }
    
    i++; //iterates i to get to the spot that stores number of dates
    
    count = stringConvert::charToInt(file[i]); //stores the number of dates
    
    i += 2; //iterates to the first character of the first date
    
    dateSet = new string[count];
    j = 0;
    
    while(j < count) {
        while(file[i] != '\n' && file[i] != '\0') {
            *(dateSet + j) += file[i]; //puts each date set in a spot in an array for easier access
            i++;
        }
        i++;
        j++;
    }
    
    for(int i = 0; i < stringConvert::charToInt(file[1]); i++) {
        buildFileOutput(*(csv + i), dateSet, count); //for each .csv file specified it runs all the dates
    }
    delete [] csv;
    delete [] dateSet;
}

void arrayBuilder::buildFileOutput(string csv, string* dateSet, int dateNum) {
    string output;
    ifstream f(csv);
    arrayMaker(f); //opens the .csv and pushes it to the array builder (maybe build another class for this)
    f.close();
    for(int i = 0; i < dateNum; i++) {
        sDate = (*(dateSet + i)).substr(0, (*(dateSet + i)).find(",")); //pulls out the first and second date spots (seperated by a comma in the file)
        eDate = (*(dateSet + i)).substr((*(dateSet + i)).find(",") + 1, 1000);
        findStorm(); //gets outputString set to what the output would be

        output = output + outputString + ",\n,\n,\n";
    }
    
    csv.insert(csv.find(".csv") - 1,"_output"); //builds name for the output file
    
    ofstream o(csv);
    o << output; //outputs file
    o.close();
}

void arrayBuilder::makeHourly() {
    /*The first for loop just builds the hourlyDate array by pulling all
     * the dates that end in ":00" (exactly on the hour) and putting them
     * all in an array.
     */
    int tmp = 0;
    int pos = 0;
    HOURPOINTS = (DATAPOINTS + 1)/4;
    hourlyDate = new string[HOURPOINTS];
    hourlyFlow = new int[HOURPOINTS];
    for(int i = 0; i < DATAPOINTS; i++) {
        if((*(date+i)).find(":00") != string::npos) {
            *(hourlyDate + pos) = *(date + i);
            pos++;
        }
        if(pos == HOURPOINTS) break; //if this isn't here, then the whole thing will crash
        //if the data doesn't end on a multiple of 4.
    }
    
    pos = 0;
    /*This is a pretty simple function. Uses a temp variable to convert the
     * previously 15 min intervals into hour intervals. Just a simple for loop
     * that runs through everything and pulls the cfs values then avergaes them
     * out and assigns them to the hourly arryas.
     */
    for(int i = 0; i < HOURPOINTS; i++) {
        for(int j = 0; j < 4; j++) {
            tmp += stringConvert::stringToInt(*(flowRate + pos));
            pos++;
            if(pos == DATAPOINTS) break;
        }
        *(hourlyFlow + i) = tmp/4;
        tmp = 0;
        if(pos == DATAPOINTS) break;
    }
}

void arrayBuilder::findStorm() {
    start = 0;
    end = 0;
    found = 0;
    /*This function finds the storm that has been specified by comparing the input
     *date to the dates in the data. If the date can't be found, it reports that.
     */
    while(start < HOURPOINTS) {
        if((*(hourlyDate+start)).find(sDate) != string::npos) {
            found = 1;
            
            break;
        }
        start++;
    }
    
    if(found == 1) {
        end = start;
        while(end < HOURPOINTS) {
            if((*(hourlyDate + end)).find(eDate) != string::npos) {
                found = 2;
                end--;
                break;
            }
            end++;
        }
    }
    buildString();
}

void arrayBuilder::buildString() {
    outputString = "";
    //simple string build loop. Loops through array, builds the string.
    for(int i = start; i <= end; i++) {
        string q = (*(hourlyDate + i)) + "," + stringConvert::intToString(*(hourlyFlow + i)) + "\n";
        outputString = outputString + q;
    }
}
