#ifndef USER_CPP
#define USER_CPP
#include "User.h"
#include "Time.h"
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
using std::unordered_set;


//Precondition:
//1) info size is 3
//2) data is stored as following,
//userID, name, numOfUserBooks
//Stores the information about the user
//Information provided from file input
User::User(vector<string> info){
  userID = stoi(info[0]);
  name = info[1];
  numOfUserBooks = stoi(info[2]);
}
//If user is created from the commandline
//Information is simply name and id
User::User(string userName, int id){
  name = userName;
  userID = id;
  numOfUserBooks = 0;
}

//Provided with a Book, adds it to the Users "hand"

void User::addBook(Book* newBook){
  //Implies the book was NOT added from the file
  //Sets the duedate, renewCount, and changes the books availability
  if (newBook->getAvailability()==true){
    newBook->setDueDate(Time::getTime() + 15);
    newBook->setRenewCount(0);
    newBook->setAvailability(false);
    //If this is the User's NOT first time borrowing
    //Book with this genre, adds one to demonstrate
    //User likes this genre
    if (userGenre.find(newBook->getGenre()) != userGenre.end()){
      auto it = userGenre.find(newBook->getGenre());
      it->second +=1;
    }
    //Otherwise add the genre to the genre User likes
    else{
      userGenre[newBook->getGenre()] = 1;
    }
    //If this is the User's NOT first time borrowing
    //Book with this author, adds one to demonstrate
    //User likes this author
    if (userAuthor.find(newBook->getAuthor()) != userAuthor.end()){
      auto it = userAuthor.find(newBook->getAuthor());
      it->second +=1;
    }
    //Otherwise add the genre to the genre User likes
    else{
      userGenre[newBook->getGenre()] = 1;
    }
  }

  //If this is the first time the user is borrowing the book
  //Add one to its popularity score
  //Then add it to the books that the User has borrowed
  if (historyOfBooks.find(newBook->getID()) == historyOfBooks.end()){
    newBook->addToScore();
    historyOfBooks.insert(newBook->getID());
  }
  //Regardless of how book is added,
  //It's borrow id needs to be updated
  //And book needs to be added to users "hand"
  newBook->setBorrowID(userID);
  hand.push_back(newBook);
}


//Provided an ID, the Library will
//Print the Accounts information
//And information about User's books
//On several lines
void User::PrintUser() const{
  cout << "Name: " << getName() << endl;
  cout << "AccountID#: " << getID() << endl;
  if (hand.size()==0){
    cout << "No books checked out." << endl;
  }
  else{
    cout << hand.size() << " books checkout out:" << endl;
  }
  //IF ANY BOOKS OVERDUE PRINT NUM BOOKS OVERDUE
  for (unsigned int i = 0 ; i < hand.size(); i++){
    cout << "\t" << i+1 << ".\n";
    hand[i]->PrintBookFromUser();
  }
  cout << endl;
}


//Given an book ID it will search
//the book and then using Books "returnBook"
//function, resets its values and remove it from User hand
void User::returnBookUser(int id){
  for (unsigned int i = 0; i < hand.size(); ++i){
    if (hand[i]->getID() == id){
      hand[i]->returnBook();
      hand.erase(hand.begin()+i);
    }
  }
}

//Print user information and then prints all of its books
void User::PrintByUsersInfo() const{
    cout << name << " (AccountID# " << userID << "). ";
    if (hand.size()==0){
      cout << "No books checked out." << endl;
    }
    else{
      cout << hand.size() <<  " books checked out:" << endl;
    }
    for (unsigned int i = 0; i < hand.size(); ++i){
      cout << "\t"<< i+1 << ". \"" << hand[i]->getTitle()
      << " by " << hand[i]->getAuthor() << " (BookID# " << hand[i]->getID()
      << ") [" << hand[i]->getGenre() << "]." << endl;
    }
}

//Before removing a User, it first force returns all of it's Books
void User::returnAllBooks(){
  for (unsigned int i = 0 ; i < hand.size(); ++i){
    cout << "\"" << hand[i]->getTitle() << "\" by " << hand[i]->getAuthor()
    << "  (BookID# " << hand[i]->getID() << ") force returned." << endl;
    hand[i]->returnBook();
  }
}

//Search through all of User's books
//If any are late, OverDue is TRUE
//Otherwise false and they can continue activitiy
bool User::getBooksOverDueStatus() const{
  for (unsigned int i = 0 ; i < hand.size(); ++i){
    if (hand[i]->getDueDate() < Time::getTime()){
      return true; //TRUE IMPLIES OVERDUE!
    }
  }
  return false;
}

//If User has Books and no book is OverDue
//Then renews all books that are eligible for renewal
//Counts how many books were renewed, and then prints
//An update of those books
void User::renewAllBooks(){
  if (hand.size()==0){
    cout << "No books in this account.\n\n";
    return;
  }
  if (getBooksOverDueStatus()){
    cout << "Account has overdue books.\n\n";
    return;
  }
  int count = 0;
  unordered_set<int> renewedBooks;
  for (unsigned int i = 0; i < hand.size(); ++i){
    if (hand[i]->getRenewCount()<2){
      hand[i]->setRenewCount(hand[i]->getRenewCount()+1);
      hand[i]->setDueDate(hand[i]->getDueDate()+5);
      count++;
      renewedBooks.insert(hand[i]->getID());
    }
  }
  cout << count << " of " <<  hand.size() << " books successfully renewed." <<endl;
  for (unsigned int i = 0; i < hand.size(); ++i){
    cout << "\t" << i+1 << ".\n";
    hand[i]->PrintBookFromUser();
    if (renewedBooks.find(hand[i]->getID()) != renewedBooks.end()){
      cout << "\tBook successfully renewed." << endl;
    }
    else{
      cout << "\tBook already renewed twice." << endl;
    }
  }
  cout << endl;
}


// vector<string> User::genreAndAuthor(){
//   vector<string> recs;
//   int max = 0;
//   //RETURN VECTOR WITH HIGHEST REPEATED GENRE
//   //ADD TO IT MOST REPEATED AUTHOR
//   return recs;
// }



#endif
