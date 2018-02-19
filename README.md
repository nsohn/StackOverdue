# StackOverdue is a library based program. I will use the word "simulator" to describe the person using the program.

# How to compile
Type "make". After all of the files are compiled, there will be an executable "StackOverdue" In the terminal, the simulator can provide either no files, a book file, or a book and an account file. The book file must come first and only after a book file can there be an account file.
#### For example: "./StackOverdue data/library.small/books.data data/library.small/accounts.data"

**A book file has the following syntax:**
BOOKID|TITLE|AUTHOR|GENRE|POPULARITYSCORE
##### For example:
1|The Things They Carried|Tim O'Brien|Metafiction|100

**An account file has the following syntax:**
ACCOUNTID|NAME|NUMBER_OF_BOOKS
**For each integer in _NUMBER_OF_BOOKS_ there will be a line with the following syntax:**
BOOKID|DUE_DATE|NUMBER_OF_TIMES_RENEWED

#### For example:

4|Noam Sohn|2
23|12|1
6|3|2

# **The main classes are as follows:**
## __Book__: maintains information about itself, title, author, genre, populartiy score, availability. Also maintains information about the User if someone borrows the book. Although the Book should not technically know about Users, given this programs purpose, I found that it was appropriate for the Book to keep track of the Users ID, the Books duedate and it's renewal count. Book also has the ability to Print different pieces of information about itself in different syntax in order to make information simpler for the simulator to read.

## **User:** keeps track of the books that it has checked out. I used a vector<Book*> to keep track of the User's Books. Perhaps it would have been a better design to use an unordered_set, however, I felt that since there is a maximum of 10 Books per User, a vector provides essentially the same speed.  It also has it's ID number, name, and a history of all the Books it has borrowed. The history of Books is stored an unordered_set of integers, where the ints are the BookID, which are guaranteed to be unique and even if the Book is deleted, it's ID will never be used again. 

## **Library:** stores all the Users and Books. Since each Book and User has a unique ID, I have an unordered_map of integers to Book* and integers to User*. The unordered map allows for O(1) insertion, retrieval, and removal of the Book*/User*. Furthermore, the pointers minimizes the amount of memory needed. The Library is the "middle-man" between the simulator and the User/Book classes. It passes information back and forth to allow for a smooth experience for the simulator.

## **Interface:** takes the simulators input and determines which functions within Library should be called, which call other functions in User or Book accordingly.

Interface is initialized with two files. If the file names are blank, it will continue without importing Books and Users. If not, it will create Books and Users and store it in it's Library. All input from command line must be capatilized. The program will run until the command "EXIT" has been entered.
Here is a list of the commands and what the simulator can expect from them:
* BROWSE: Provides the status of all the books.
* BOOK: Provides the status of a specific book.
* SEARCH: Searches for all books with a key-phrase in the title or author.
* ACCOUNTS: Provides account snapshots for all user accounts.
* ACCOUNT: Provides an account snapshot for a specific user account.
* CHECKOUT: Checks a book out to a user account.
* RENEW: Renews a checked out book. (Up to two times allowed)
* RETURN: Returns a checked out book.
* ADDB: Adds a new book to the library.
* REMOVEB: Removes a specific book from the library.
* ADDA: Creates a new user account in the library.
* REMOVEA: Removes a specific user account from the library.
* SYSTEM: Provides diagnostic information about the system.
* TIME: Fast forwards the system time by a specified number of days.
* HELP: Displays this help menu.
* EXIT: Exits the program.


Time is initialized to 1 upon running the program. Time only changes if the simulator types "TIME" and follows the steps to change time. Time can only go forward and can only increase in whole days (ints). A Books due date is Time + 15, and renewal gives the Book an additional 5 days. Books that are provided in the User file will have specified due dates.

