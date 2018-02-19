#ifndef LIBRARY_CPP
#define LIBRARY_CPP
#include "Library.h"
#include "Time.h"


void Library::PrintLibraryBook(int id) const{
  if (idLib.find(id) != idLib.end()){
    auto it = idLib.find(id);
    it->second->PrintBook();
  }
  else{
    cout << "BookID# " << id << " not found." << endl;
  }
}
//Adds a Book to the map using the
//Books unique ID, also stores the Books
//ID so it cannot be reused
void Library::addBook(Book *aBook){
    idLib[aBook->getID()] = aBook;
    usedBookIDs.insert(aBook->getID());
    numBooks++;
}

//Adds a User to the map using the
//User unique ID, also stores the User
//ID so it cannot be reused
void Library::addUser(User *aUser){
  if ((userLib.find(aUser->getID())) == userLib.end()){
    userLib[aUser->getID()] = aUser;
    usedUserIDs.insert(aUser->getID());
    numUsers++;
  }
}
//Precondition vector will be greater than 3
//Converts the numeric data regarding a Book to int
//So it can be checkout while reading File
vector<int> Library::convertToInt(vector<string> input){
  vector<int> intVersion;
  for (unsigned int i = 3; i < input.size(); i++){
      intVersion.push_back(stoi(input[i]));
  }
  return intVersion;
}

//Precondition: vector<string> size is > 3
//Finds the Book, and then checks the Book out using Book
//Functions
//The bookInfo vector has ALL the Books the User has upon File input
//So collectBookInfo only stores the data for each Book. At each point that
//collectBookInfo is empty, it adds the User ID, because each Book needs
//To be updated with UserID
void Library::checkout(vector<string> stringInfo){
  vector<int> bookInfo = convertToInt(stringInfo);
  if (idLib.find(bookInfo[1]) == idLib.end()){//not sure if i need this..
    cout << "Could not find library book with ID# " << bookInfo[1] << "." << endl;
    return;
  }

  int userID = stoi(stringInfo[0]);
  vector<int> collectBookInfo;
  for (unsigned int i = 0; i < bookInfo.size(); i++){
    if (collectBookInfo.size()==0){
      collectBookInfo.push_back(userID);
    }
    collectBookInfo.push_back(bookInfo[i]);
    //Need 4 things to change book status
    //bookID, userID, dueDate, renewCount
    //bookID will always be collectBookInfo[1]
    if (collectBookInfo.size()==4){
        idLib[collectBookInfo[1]]->changeBookStatus(collectBookInfo);
        userLib[userID]->addBook(idLib[collectBookInfo[1]]);
        collectBookInfo.clear();
    }
  }
}

//Checkout Book from Command line.
//Finds Account and Book, then if the Account
//Does not have any overdue books, has fewer than 10 Books
//And the book is Available
//It is allowed to check it out
void Library::checkout(int userID, int bookID){
  if (userLib.find(userID)== userLib.end()){
    cout << "AccountID# " << userID << " not found." << endl;
    return;
  }
  if (idLib.find(bookID) == idLib.end()){
    cout << "BookID# " << bookID << " not found." << endl;
  }
  else{
    auto bookIT = idLib.find(bookID);
    auto userIT = userLib.find(userID);
    if (userIT->second->getBooksOverDueStatus()==true){
      cout << "Account has books overdue.\n\n";
    }
    else if (bookIT->second->getAvailability() == false){
      cout << "Book is already checked out.\n\n";
    }
    else if (userIT->second->numBook()){
      cout << "Account already has 10 books checked out.\n\n";
    }
    else{
        cout << "Book successfully checked out." << endl;
        userIT->second->addBook(bookIT->second);
        bookIT->second->PrintBook();
    }
  }
}

//Given a Book ID, it will remove it from the Library
//If the Book is checkedout, it will force return it
//Then it will delete it.
void Library::removeBook(int id){
  if (idLib.find(id) != idLib.end()){
    auto it = idLib.find(id);
    //Change Books status to True by returning it from the User
    //Then it can enter following IF statement to properly delete book
    if (it->second->getAvailability() == false){
      cout << "Force returing book from AccountID# " << it->second->getAccountID() << ".\n";
      userLib[it->second->getAccountID()]->returnBookUser(id);
    }
    if (it->second->getAvailability()){
      cout << "\"" << it->second->getTitle() << "\" by " << it->second->getAuthor() << " successfully removed.\n\n";
      Book* temp = it->second;
      idLib.erase(it);
      delete temp;
    }
  }
  else{
    cout << "BookID# " << id << " not found.";
  }
}
//Given a User ID, it will remove it from the Library
//If the User has checkedout Books, it will force return all of them
//Then it will delete the User.
void Library::removeUser(int id){
  if (userLib.find(id) != userLib.end()){
    auto it = userLib.find(id);
    it->second->returnAllBooks();
    cout << it->second->getName() << "'s account successfully removed.\n\n";
    User* temp = it->second;
    userLib.erase(it);
    delete temp;
  }
  else{
    cout << "UserID# " << id << " not found.\n\n";
  }
}

//Print information about the User
void Library::PrintLibraryUser(int id) const{
  if (userLib.find(id) != userLib.end()){
    auto it = userLib.find(id);
    it->second->PrintUser();
  }
  else{
    cout << "AccountID# " << id << " not found.\n\n";
  }
}
//The following 6 boolean functions are used with the
//"sort" function from <algorithm> each of them allows for Books
//Or Users to be sorted according to their specific data
bool sortByTitle(const Book* b1, const Book* b2){return b1->getTitle() < b2->getTitle();}
bool sortByAuthor(const Book* b1, const Book* b2){return b1->getAuthor() < b2->getAuthor();}
bool sortByGenre(const Book* b1, const Book* b2){return b1->getGenre() < b2->getGenre();}
bool sortByPop(const Book* b1, const Book* b2){return b1->getScore() < b2->getScore();}
bool sortByUserName(const User* u1, const User* u2){return u1->getName() < u2->getName();}
bool sortByCheckout(const User* u1, const User* u2){return u1->getNumBooksCheckedOut() > u2->getNumBooksCheckedOut();}

//Given the method to sort data by, it determine if a
//vector<Book*> or vector<User*> needs to be created.
//After creating the vector, it sorts it according to the method
//provided in the parameter
void Library::sortDataBy(string sortBy){
  //Book Related Sort
  //First creates vector of the necessary items (Books or Users)
  //Then using sort functions that I have created above, it will sort the
  //vector in the accoring way.
  if (sortBy == "TITLE" || sortBy == "AUTHOR" || sortBy == "GENRE" || sortBy == "POPULARITY"){
    vector<Book*> sortedBooks;
    for (auto it = idLib.begin(); it != idLib.end(); ++it){
      sortedBooks.push_back(it->second);
    }
    if (sortBy == "TITLE"){
      sort(sortedBooks.begin(), sortedBooks.end(), sortByTitle);
    }
    else if (sortBy == "AUTHOR"){
      sort(sortedBooks.begin(), sortedBooks.end(), sortByAuthor);
    }
    else if (sortBy == "GENRE"){
      sort(sortedBooks.begin(), sortedBooks.end(), sortByGenre);
    }
    else{//"POPULARITY"
      sort(sortedBooks.begin(), sortedBooks.end(), sortByPop);
    }
    PrintSortedBook(sortedBooks);
  }
  //ACCOUNT RELATED SORTING
  else{//"NAME"  "CHECKOUTS"
    vector<User*> sortedUsers;
    for (auto it = userLib.begin(); it != userLib.end(); ++it){
      sortedUsers.push_back(it->second);
    }
    if (sortBy == "NAME"){
      sort(sortedUsers.begin(), sortedUsers.end(), sortByUserName);
      // cout << "not yet";
    }
    else{ // Refers to CHECKOUTS
      sort(sortedUsers.begin(), sortedUsers.end(), sortByCheckout);
    }
    PrintSortedUser(sortedUsers);
  }
}

//Provided a sorted vector, it prints all the data accordingly
void Library::PrintSortedBook(vector<Book*>& sortedBooks) const {
  for (unsigned int i = 0; i < sortedBooks.size(); ++i){
    cout << i+1 << ". ";
    sortedBooks[i]->PrintBookFromBrowse();
  }
  cout << endl;
}
//Provided a sorted vector, it prints all the data accordingly
void Library::PrintSortedUser(vector<User*>& sortedUsers) const{
  for (unsigned int i = 0; i < sortedUsers.size(); ++i){
    cout << i+1 << ". ";
    sortedUsers[i]->PrintByUsersInfo();
  }
  cout << endl;
}

//Given a word or a substring, it will search through
//Titles of all the Books to determine if that substring
//Exists, if it does, it prints it to the screen
void Library::searchTitles(const string searchWord){
  int count = 1;
  for (auto it = idLib.begin(); it != idLib.end(); ++it){
    if (it->second->getTitle().find(searchWord) != std::string::npos){
        cout << count << ". ";
        count++;
        it->second->PrintBookFromBrowse();
    }
  }
  cout << endl;
}
//Given a word or a substring, it will search through
//Authors of all the Books to determine if that substring
//Exists, if it does, it prints it to the screen
void Library::searchAuthors(string searchWord){
  int count = 1;
  for (auto it = idLib.begin(); it != idLib.end(); ++it){
    if (it->second->getAuthor().find(searchWord) != std::string::npos){
        cout << count << ". ";
        count++;
        it->second->PrintBookFromBrowse();
    }
  }
  cout << endl;
}
//Account ID is unique, so it does not need to be
//Created into a vector. It is able to simply be printed
void Library::sortByAccountID(){
  int count = 1;
  for (auto it = userLib.begin(); it != userLib.end(); ++it){
    cout << count << ". ";
    count++;
    it->second->PrintByUsersInfo();
  }
  cout << endl;
}
//Books ID is unique, so it does not need to be
//Created into a vector. It is able to simply be printed
void Library::sortByBookID(){
  int count = 1;
  for (auto it = idLib.begin(); it != idLib.end(); ++it){
    cout << count << ". ";
    count++;
    it->second->PrintBookFromBrowse();
  }
  cout << endl;
}

//Prints an update of the system
void Library::PrintSystem() const{
  cout << "System time: " << Time::getTime() << endl;
  cout << "Number of books: " << idLib.size() << endl;
  cout << "Number of overdue books: " << numOverDueBooks() << endl;
  cout << "Number of accounts: " << userLib.size() << endl;
  cout << "Number of overdue accounts: " << numOverDueAccounts() << "\n\n";
}

//Calculates the number of overdue Books
int Library::numOverDueBooks() const {
  int count = 0;
  for (auto it = idLib.begin(); it != idLib.end(); ++it){
    //only increments count if book is checkout AND time > duedate
    if ((it->second->getDueDate() < Time::getTime()) && (!it->second->getAvailability())){
      count++;
    }
  }
  return count;
}

//Calculates the number of overdue accounts
int Library::numOverDueAccounts() const {
  int count = 0;
  for (auto it = userLib.begin(); it != userLib.end(); ++it){
    if (it->second->getBooksOverDueStatus() == true){
      count++;
    }
  }
  return count;
}

//Returns a Book using the Book and User functions
//Prints the completion of the return with a "receipt"
//Including number of days after due that it was returned
void Library::returnBook(int id){
  auto bookIT = idLib.find(id);
  if (idLib.find(id) == idLib.end()){
    cout << "BookID# " << id << " not found.\n\n";
  }
  else if (bookIT->second->getAvailability()==true){
    cout << "Book is currently not checked out.\n\n";
  }
  else{
    auto userIT = userLib.find(bookIT->second->getAccountID());
    cout << "Book successfully returned from AccountID# " << bookIT->second->getAccountID();
    if (bookIT->second->getDueDate() < Time::getTime()){
      cout << " (overdue by " << Time::getTime() - bookIT->second->getDueDate() << " days).\n\n";
    }
    else{
      cout << " (on time).\n\n";
    }
    userIT->second->returnBookUser(id);
  }
}
//Renews all eligible Books in User
void Library::renewUsersBook(int userID){
  if (userLib.find(userID)== userLib.end()){
    cout << "AccountID# " << userID << " not found." << endl;
    return;
  }
  auto it = userLib.find(userID);
  it->second->renewAllBooks();
}

void Library::exportLib(string bookFile, string accountFile){
  cout << "Couldnt get to function on time :( \n\n";
}
//Provided with a potential books title and author
//Determines if a book with that title and author
//Already exists, if yes, returns true and book will not be created
//Otherwise returns false and book can be created
bool Library::bookTitleAuthorExists(string title, string author){
  for (auto it = idLib.begin(); it != idLib.end(); ++it){
    if ((it->second->getTitle()==title) && (it->second->getAuthor()== author)){
      return true;
    }
  }
  return false;
}

void Library::makeRecs(int id){
  if (userLib.find(id) == userLib.end()){
    cout << "AccountID# " << id << " not found." << endl;
    return;
  }
  else{
    cout << "Couldnt get to function on time :( \n\n";
  }
}
#endif
