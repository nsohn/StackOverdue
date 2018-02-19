#ifndef TIME_CPP
#define TIME_CPP
#include "Time.h"
using std::cout;
using std::cin;
using std::endl;

//Initializes time at the start of the program
int Time::libTime = 1;

//Functions asks for the number of days to add to time
//And adds it to time
void Time::setTime(){
  int input;
  cout << "Enter the number of days to time travel.\n> ";
  cin >> input;
  if (input > 0){ //can we travel backwards?
    cout << "Travelled " << input << " days through time travel. ("
      << libTime << " --> " << libTime+input << ").\n\n";
    libTime += input;
  }
  else{
    cout << "Invalid value.\n\n";
  }
}



#endif
