
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <iostream>
#include <regex>
#include <iterator>

using namespace std;

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
    Serial* SP = new Serial("COM3");    // adjust as needed, // COM3

    if (SP->IsConnected())
    	cout << "We're connected" << endl;

    char incomingData[256] = "";			
    //printf("%s\n",incomingData);
    int dataLength = 255;
    int readResult = 0;
    double avgSum = 0;
    int itr_x = 0;
    

    while(SP->IsConnected())
    {
	readResult = SP->ReadData(incomingData,dataLength);
	//printf("Bytes read: (0 means no data available) %i\n",readResult);
        incomingData[readResult] = 0;
       	
        regex serial_regex("(\\d){1,3}");
        string serial_vals = incomingData;
        avgSum = 0;
      
        auto words_begin = sregex_iterator(serial_vals.begin(), serial_vals.end(), serial_regex);
        auto words_end = sregex_iterator();

        cout << "Found " << distance(words_begin, words_end) << " serial numbers:\n";

        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            smatch match = *i;                                                 
            string match_str = match.str(); 
            avgSum += stoi(match_str);
            //cout << match_str << '\n';
        }  
        
        avgSum = avgSum / (distance(words_begin, words_end));
        cout << avgSum << endl;
        
        //printf("%s",incomingData);
	//cout << incomingData;
        
        Sleep(500);
        if((avgSum <=520) && (avgSum >= 480)){
            itr_x++;
            if(itr_x == 10){
                cout << "Medidation Achieved" << endl;
                // exit system // placeholder for external functionality
                delete SP;
                SP = 0;
                exit(EXIT_FAILURE);
            }
        }
        else{
            itr_x = 0;
        }
    }
    return 0; 
}