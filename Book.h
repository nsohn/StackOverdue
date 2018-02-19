#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <vector>
#include <stdlib.h>
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;

class Book{
public:
  //Create book with necessary
  //information in vector
  Book(vector<string> vect);

  //Different forms of printing
  //Book depending on the request
  //From the Interface
  void PrintBook() const;
  void PrintBookFromUser() const;
  void PrintBookFromBrowse() const;
  //Resets the Books User dependent information
  void returnBook();
  //Provided with the Users information,
  //Changes the books User dependent data
  void changeBookStatus(vector<int> bookInfo);
  void addToScore(){popScore++;}

  //When User borrows a book, it passes
  //Information to the Book to change
  //Its User dependent data
  void setBorrowID(const int id){borrowID= id;}
  void setAvailability(bool avail){available = avail;}
  void setDueDate(int date){dueDate = date;}
  void setRenewCount(int numTimes){numTimeRenewed = numTimes;}

  //Get Info from Book
  int getAccountID() const {return borrowID;}
  int getID() const {return id;}
  int getDueDate() const {return dueDate;}
  int getRenewCount() const {return numTimeRenewed;}
  string getTitle() const {return title;}
  string getAuthor() const {return author;}
  string getGenre() const {return genre;}
  int getScore() const {return popScore;}
  bool getAvailability() const {return available;}
private:
  //Basic book information
  string title;
  string author;
  int id;
  string genre;
  int popScore;
  bool available;

  //Upon borrowing, book keeps
  //Track of who borrowed it
  //It's duedate and renewal count
  int borrowID;
  int dueDate;
  int numTimeRenewed;
};
#endif
