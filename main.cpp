#include <iostream>
#include <string>
#include "Library.h"
#include "Interface.h"
using std::string;


int main(int argc, char* argv[]){
  string bookFile ="";
  string userFile = "";

  if (argc >= 3){
    bookFile = argv[1];
    userFile = argv[2];
  }
  else if (argc == 2){
    bookFile = argv[1];
  }

  Interface sim(bookFile, userFile);
  sim.inputRequest();
  // Interface sim;
  // sim.inputRequest();
  // lib.PrintLibraryBook();
  // lib.simulator();
  // lib.PrintLibraryUser();
}
