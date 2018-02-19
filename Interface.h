#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <string>
#include <locale>
#include "Time.h"
#include "Library.h"

class Interface{
public:
  //Constructor is called from main with two files
  //Uses them to fill library, strings are empty,
  //Library does not populate but functions continue to work
  Interface(string bookFile, string userFile);

  //Manages the input from command line
  //Calls the appropriate function from Library
  //Or private functions
  void inputRequest();

private:
  //Stores book info provided by file or commandline
  vector<string> bookInput();
  //Prints for any input error
  void PrintError();
  //Prints all possible commands
  //Available to user
  void PrintHelp() const;

  //Given a book file or/and user file
  //These functions store all of the books
  //In the library, followed by all of the Users
  //Users books are also added to User's "hand"
  void populateBooks(string bookFile);
  void populateUsers(string userFile);

  //Determines which way of sorting the user wants
  //And calls the appropriate function accordingly
  void determineSortBy(string input);

  //The library that stores the Users and Books info
  Library simLibrary;
};
#endif
