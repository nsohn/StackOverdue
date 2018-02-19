#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "Book.h"
#include "User.h"


class Library{
public:
  //Two methods of checking out book
  //One is from file input, uses vector for data
  //Other is from command line, uses userID and bookID
  void checkout(vector<string> bookInfo);
  void checkout (int userID, int bookID);
  //Returns single book given bookID
  void returnBook(int id);
  //Given User or Book, adds it to Library
  void addUser(User *aUser);
  void addBook(Book *aBook);

  //Prints specific Book or User information
  void PrintLibraryBook(int id) const;
  void PrintLibraryUser(int id) const;

  //Prints an update about the Library status
  void PrintSystem() const;

  //Checks if Books or Accounts is empty
  bool isBooksEmpty(){return idLib.empty();}
  bool isAccountsEmpty(){return userLib.empty();}

  //Converts the file input data into int
  //So that it can be stored correctly
  std::vector<int> convertToInt(std::vector<std::string> input);

  //Creates new ID for Book or User
  int getNewID(){return usedBookIDs.size()+1;}
  int getNewUserID(){return usedUserIDs.size()+1;}

  //Provided ID's, deleted Book or User
  void removeBook(int id);
  void removeUser(int id);

  //Account and User ID
  //Can be printed in order
  void sortByAccountID();
  void sortByBookID();

  //Search Book for titles/authors with searchWord
  void searchTitles(string searchWord);
  void searchAuthors(string searchPhrase);
  //Renew all eligible Books in User
  void renewUsersBook(int id);
  //Determines which sort method to use
  void sortDataBy(string sortBy);
  //Determines if Book can be added or if Book already exists
  bool bookTitleAuthorExists(string title, string author);

  //Dont work yet..
  void exportLib(string bookFile, string accountFile);
  void makeRecs(int id);
private:
  void PrintSortedBook(vector<Book*>& sortedBooks) const;
  void PrintSortedUser(vector<User*>& sortedUsers) const;
  int numBooks;
  int numUsers;

  //Keeps track of all Books and Users
  //According to their unique ID
  std::map <int, Book*> idLib;
  std::map <int, User*> userLib;

  std::unordered_set<int> usedBookIDs; //keeps track of all book IDs
  std::unordered_set<int> usedUserIDs;//keeps track of all user IDs

  //Calculate number of overdue books/accounts
  int numOverDueBooks() const;
  int numOverDueAccounts() const;
};

#endif
