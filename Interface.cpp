#ifndef INTERFACE_CPP
#define INTERFACE_CPP
#include "Interface.h"
using std::ifstream;
using std::istringstream;

using std::cout;
using std::cin;
using std::string;
using std::endl;

Interface::Interface(string bookFile, string userFile){
  //Neither file was provided
  if (bookFile == ""){
    cout << "No books provided." << endl;
    cout << "No accounts provided." << endl;
    return;
  }
  //Only Book file was provided
  if (userFile == ""){
    populateBooks(bookFile);
    cout << "No accounts provided." << endl;
  }
  //Both Book and User file provided
  else{
    populateBooks(bookFile);
    populateUsers(userFile);
  }
}
//Reads each line in the file and creates
//Then stores the string between bars "|"
//In a vector. The vector is sent
//To the Book constructor to create a Book
//And then it is added the Library
void Interface::populateBooks(string bookFile){
  ifstream inFile;
  inFile.open(bookFile);
  if (!inFile.is_open()){
    cout << "Could not find file \"" << bookFile << "\". Skipping." << endl;
    return;
  }
  cout << "Loading books from \"" << bookFile << "\"."<< endl;

  string my_string_to_split;
  istringstream ss {my_string_to_split};

  string bookCount;
  getline(inFile, bookCount);

  vector<string> bookInfo;
  //Read each section of string
  //Up until char |
  //If vector has 5 strings, create book
  //Clear vector for next book
  while (!inFile.eof()){
    string bookLine;
    getline(inFile, bookLine);
    istringstream ss(bookLine);
    //Learned this method of parsing through Maximillian Ioffee
    //Creates a string in the for loop, and stores the string between |
    //then pushes it into the vector and repeats
    //Once it has 5 pieces of information, it can create the Book and then repeat
    //The process for the next line
    for (string each_split; getline(ss, each_split, '|');){
      bookInfo.push_back(each_split);

      if (bookInfo.size()==5){
        Book *newBook = new Book(bookInfo);
        simLibrary.addBook(newBook);
        //Clears vector so next Book can be stored
        bookInfo.clear();
      }
    }
  }
}
//Reads each line in the file and
//Then stores the string between bars "|"
//In a vector. The vector is sent
//To the User constructor to create a User
//And then it is added the Library
void Interface::populateUsers(string userFile){
  ifstream inFile;
  inFile.open(userFile);
  if (!inFile.is_open()){
    cout << "Could not find file \"" << userFile << "\". Skipping." << endl;
    return;
  }
  cout << "Loading books from \"" << userFile << "\"."<< endl;
  //userInfo stores the
  //Information to create
  //A User and the Books
  //It already has
  vector<string> userInfo;
  string userCount;
  getline(inFile, userCount);
  while (!inFile.eof()){
    string userLine;
    getline(inFile, userLine);
    istringstream ss(userLine);
    //Same function explanation for reading Book file above..
    for (string each_split; getline(ss, each_split, '|');){
      userInfo.push_back(each_split);

      //if the userInfo vector is
      //3 + the number of books they have
      //*3 because each book has 3 pieces of information
      //create user
    if (userInfo.size()>=3){
      if (userInfo.size() == stoi(userInfo[2])*3 +3){

        User *newUser = new User(userInfo);
        simLibrary.addUser(newUser);
        //Check if vector has more information
        //Than just setting up user
        if (userInfo.size() > 3){
          simLibrary.checkout(userInfo);
        }
        userInfo.clear();
        }
      }
    }
  }
}

//Manages all of the types of input
//If Library does not have Books or Users
//Will Print accordingly
//Otherwise, allows for commandline to
//See or manipulate library info
//Runs until command "EXIT"
void Interface::inputRequest(){
  string input;
  do {
    int id;
    cout << "> ";
    cin >> input;

    //Book related commands but no Books results in Printing message and continuing...
    if ((input == "BOOK" || input == "BROWSE" || input == "REMOVEB" || input == "RETURN") && (simLibrary.isBooksEmpty())){
      cout << "No books in your library.\n\n";
    }
    //Account related commands but no Account results in Printing message and continuing...
    else if ((input== "ACCOUNT" || input == "ACCOUNTS" || input== "REMOVEA"|| input == "RENEW") && (simLibrary.isAccountsEmpty())){
      cout << "No accounts in your library.\n\n";
    }
    else if (input == "BROWSE"){
      cout << "Enter the criteria to sort by. (title/author/genre/bookid/popularity)\n> ";
      string browseBy;
      cin >> browseBy;
      determineSortBy(browseBy);
    }
    else if (input == "BOOK"){
      cout << "Enter the book id.\n> ";
      cin >> id;
      if (!id){ PrintError();}
      else{
        simLibrary.PrintLibraryBook(id);
        cout << endl;
      }
    }
    else if (input == "ACCOUNTS"){
      cout << "Enter the criteria to sort by. (name/accountid/checkout)\n> ";
      string searchBy;
      cin >> searchBy;
      if (searchBy == "NAME" || searchBy == "ACCOUNTID" || searchBy == "CHECKOUT"){
        determineSortBy(searchBy); //SHOULD THERE BY one FUNCTIONS IN SIMLIBRARY TO DEAL WITH THIS
      }
      else{
        cout << "Invalid value.\n\n";
      }
    }
    else if (input == "ACCOUNT"){
      cout << "Enter the account id.\n> ";
      cin >> id;
      if (!id){PrintError();}
      else{
        simLibrary.PrintLibraryUser(id);
      }

    }
    else if (input == "ADDB"){
      vector<string> addedBook = bookInput();
      if (addedBook.size() != 0){
        Book *newBook = new Book(addedBook);
        simLibrary.addBook(newBook);
        cout << "BookID# " << addedBook[3] << " successfully created.\n\n";
      }
    }
    else if (input == "ADDA"){
      string userName;
      cout << "Enter the user's name.\n> ";
      cin >> userName;
      User *newUser = new User(userName, simLibrary.getNewUserID());
      simLibrary.addUser(newUser);
      cout << "AccountID# " << newUser->getID() << " successfully created.\n\n";
    }
    else if (input == "RENEW"){
      cout << "Enter account id.\n> ";
      cin >> id;
      if (!id){PrintError();}
      else{
        simLibrary.renewUsersBook(id);
      }
    }
    else if (input == "REMOVEA"){
      cout << "Enter the account id.\n> ";
      cin >> id;
      if (!id){PrintError();}
      else{
        simLibrary.removeUser(id);
      }
    }
    else if (input == "REMOVEB"){
      cout << "Enter the book id.\n> ";
      cin >> id;
      if (!id){PrintError();}
      else{
        simLibrary.removeBook(id);
      }
    }
    else if (input == "CHECKOUT"){
      cout <<"Enter the account id.\n> ";
      int userID, bookID;
      cin >> userID;
      cout << "Enter the book id.\n> ";
      cin >> bookID;
      simLibrary.checkout(userID, bookID);
    }
    else if (input == "RETURN"){
        cout << "Enter the book id.\n> ";
        cin >> id;
        if (!id){PrintError();}
        else{
          simLibrary.returnBook(id);
        }
    }
    else if (input == "SYSTEM"){
      simLibrary.PrintSystem();
    }
    else if (input == "HELP"){
      PrintHelp();
    }
    else if (input == "TIME"){
      Time::setTime();
    }
    else if (input == "EXPORT"){
      string bookFile, accountFile;
      cout << "Enter the name of the books file. (This may overwrite a file)/n> ";
      cin >> bookFile;
      cout << "Enter the name of the accounts file. (This may overwrite a file)/n> ";
      cin >> accountFile;
      simLibrary.exportLib(bookFile, accountFile);
    }
    else if (input == "RECOMMEND"){
      cout << "Enter the account id.\n> ";
      cin >> id;
      if (!id){PrintError();}
      else{
        simLibrary.makeRecs(id);
      }
    }
    else if (input == "SEARCH"){
      string searchPhrase;
      cout << "Enter the criteria to search by. (title/author)\n> ";
      cin >> input;
      cout << "Enter the search phrase.\n> ";
      cin >> searchPhrase;
      if (input == "TITLE"){
        simLibrary.searchTitles(searchPhrase);
      }
      else if (input == "AUTHOR"){
        simLibrary.searchAuthors(searchPhrase);
      }
      else{
        cout << "Invalid value.\n\n";
      }
    }
    else{
      cout << "Invalid command." << endl;
    }
  } while (input != "EXIT");
  cout << "Thank you for using StackOverDue" << endl;
}
//Collects Book infortmation from command line
//Stores it in vector and sends vector to Book
//To create a new book and add it to the library
vector<string> Interface::bookInput(){
  vector<string> book;
  string title, author, genre;
  cout << "Enter the new book's title.\n> ";
  cin >> title;
  book.push_back(title);
  cout << "Enter the new book's author.\n> ";
  cin >> author;
  book.push_back(author);
  if (simLibrary.bookTitleAuthorExists(title, author) == true){
    cout << "Book with this title and author already exists.\n\n";
    book.clear();
    return book;
  }
  cout << "Enter the new book's genre.\n> ";
  cin >> genre;
  book.push_back(genre);
  book.push_back(std::to_string(simLibrary.getNewID()));
  return book;
}

//If input is not the correct type
void Interface::PrintError() {
  cout << "Invalid Input" << endl;
  cin.clear();
}

//Determines which method the command line prefers to sort
//And calls the functions accordingly
void Interface::determineSortBy(string input){
  if (input == "ACCOUNTID"){
    simLibrary.sortByAccountID();
  }
  else if (input == "BOOKID"){
    simLibrary.sortByBookID();
  }
  else {
      simLibrary.sortDataBy(input);
    }
  }

//Prints all options available on commandline
void Interface::PrintHelp() const{
  cout << "BROWSE: Provides the status of all the books.\n"
          "BOOK: Provides the status of a specific book.\n"
          "SEARCH: Searches for all books with a key-phrase in the title or author.\n"
          "ACCOUNTS: Provides account snapshots for all user accounts.\n"
          "ACCOUNT: Provides an account snapshot for a specific user account.\n"
          "CHECKOUT: Checks a book out to a user account.\n"
          "RENEW: Renews a checked out book. (Up to two times allowed)\n"
          "RETURN: Returns a checked out book.\n"
          //"RECOMMEND: Generates a list of recommended books for a given user.\n"
          "ADDB: Adds a new book to the library.\n"
          "REMOVEB: Removes a specific book from the library.\n"
          "ADDA: Creates a new user account in the library.\n"
          "REMOVEA: Removes a specific user account from the library.\n"
          "SYSTEM: Provides diagnostic information about the system.\n"
          "TIME: Fast forwards the system time by a specified number of days.\n"
          //"EXPORT: Exports the library’s books and accounts to files.\n"
          "HELP: Displays this help menu.\n"
          "EXIT: Exits the program.\n";
}

#endif
