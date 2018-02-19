#ifndef TIME_H
#define TIME_H
#include <iostream>

//Time is needs to be accessible
//By every class
//Therefore the functions and private members
//Need to be static functions/members
class Time{
public:
  static void setTime();
  static int getTime(){return libTime;}
private:
  static int libTime;
};

#endif
