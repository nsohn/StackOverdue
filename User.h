#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <map>
#include "Book.h"

class User{
public:
  User(string userName, int id);
  User(std::vector<std::string> info);
  //Prints the User infomation
  void PrintUser() const;

  //Adds book to Users "hand"
  //And updates book information
  //accordingly
  void addBook(Book* newBook);

  //Returns book and removes it
  //From Users "hand"
  void returnBookUser(int id);

  //Before User is deleted
  //Force returns all books
  void returnAllBooks();
  //Searches through books
  //Renews all books that are eligible
  void renewAllBooks();

  //Prints users book information
  void PrintByUsersInfo() const;
  //Determines if any book is overdue
  bool getBooksOverDueStatus() const;

  int getNumBooksCheckedOut() const{return hand.size();}
  std::string getName() const{return name;}
  bool numBook() const {return hand.size()==10;}
  int getID() const {return userID;}

  //For recommmendations function..
  // vector<string> genreAndAuthor();
private:
  //Basic user information
  int userID;
  std::string name;

  //Stores number of books user has
  int numOfUserBooks;
  //Stores each book user currently has
  std::vector<Book*> hand;
  //Stores all of the books the user borrowed
  std::unordered_set<int> historyOfBooks;

  //Maps the genre/author to int
  //To keep track of the user preferences
  std::map<string, int> userGenre;
  std::map<string, int> userAuthor;
};
#endif
