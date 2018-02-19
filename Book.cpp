#ifndef BOOK_CPP
#define BOOK_CPP
#include "Time.h"
#include "Book.h"

//Precondition: vector is at least 4
//If vector size is 4
//Book was added from the command line
//Otherwise book added from File
Book::Book(vector<string> vect){
  if (vect.size()==4){
    title = vect[0];
    author = vect[1];
    genre = vect[2];
    id = stoi(vect[3]);
    popScore = 0;
  }
  else{
    id = stoi(vect[0]);
    title = vect[1];
    author = vect[2];
    genre = vect[3];
    popScore = stoi(vect[4]);
  }
  //Upon creation all User dependent info
  //is initialized
  available = true;
  dueDate = -1;
  borrowID = -1;
}

//Prints single book with all of its information
//Prints on many lines
void Book::PrintBook() const{
  cout << "Title: \"" << getTitle() << "\"" << endl;
  cout << "Author: " << getAuthor() << endl;
  cout << "BookID#: " << getID() << endl;
  cout << "Genre: " << getGenre() << endl;
  cout << "Popularity Score: " << getScore() << endl;

  if (getAvailability()){
    cout << "Available" << endl;
  }
  else{
      cout << "Borrower AccountID#: " << getAccountID() << endl;
      cout << "Due Date: " << dueDate << endl;
      cout << "Times renewed: " << numTimeRenewed << endl;
      if (dueDate < Time::getTime()){
        cout << "OVERDUE" << endl;
      }
  }
}

//Prints the Books details indented and each
//detail gets its own line
void Book::PrintBookFromUser() const{
  cout << "\tTitle: \"" << getTitle() << "\"" << endl;
  cout << "\tAuthor: " << getAuthor() << endl;
  cout << "\tBookID#: " << getID() << endl;
  cout << "\tGenre: " << getGenre() << endl;
  cout << "\tPopularity Score: " << getScore() << endl;
  cout << "\tDue Date: " << getDueDate() << endl;
  cout << "\tTimes Renewed: " << getRenewCount() << endl;
}

//Prints one book per line
//Allowing for ALL books to be printed in
//a relatively short window
void Book::PrintBookFromBrowse() const{
  cout << "\"" << title << "\" by " << author << " (BookID# " << id << " [" << genre << "]. ";
  if (available == true){
    cout << "AVAILABLE.\n";
  }
  else{
    cout << "CHECKED OUT (AccountID# " << borrowID << ").\n";
  }
}
//Vector contains at least 4 pieces of information
//Order is guaranteed to be: borrowID, bookID, dueDate, numTimeRenewed
//Sets the different variables accordingly when a book is borrowed
void Book::changeBookStatus(vector<int> bookInfo){
  borrowID = bookInfo[0];
  dueDate = bookInfo[2];
  numTimeRenewed = bookInfo[3];
  available = false;
}

//Resets the status of the book
//Most important is AVAILABLE
//The rest are irrelevant while AVAILABLE
//and will be changed when a User checkouts the book
void Book::returnBook(){
  borrowID = -1;
  dueDate = -1;
  numTimeRenewed = 0;
  available = true;
}
#endif
