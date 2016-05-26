#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include <stdlib.h>
#include<windows.h>//for dos operations
using namespace std;
string login();

///////password: umt

///////////////////////////////////////////////////////////
///////////////GOTO (X,Y)////////////////////////////////// BY AHR....
///////////////////////////////////////////////////////////
 COORD coord={0,0};
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
 ////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////


class CBook {

	private :
			int ID;
			string bookName;
			string Author;
			string ISBN;
			int price;
			int pages;
			int IssuedBy;
			string IssuedOn;
			string returnDate;
	public :
			CBook()
			{
				ID=0;
				bookName='\0';
				Author='\0';
				ISBN='\0';
				price=0;
				pages=0;
				IssuedBy=0;
				IssuedOn='\0';
				returnDate='\0';
			}
			CBook(int id,string bookname,string author,string isbn,int pricE,int pageS,int issuedby,string issuedon,string returndate)
			{
				ID=id;
				bookName=bookname;
				Author=author;
				ISBN=isbn;
				price=pricE;
				pages=pageS;
				IssuedBy=issuedby;
				IssuedOn=issuedon;
				returnDate=returndate;
			}

			void ReadFrmFile () //takes in a filename and book code then searches for the code in file
			{								//upon finding the ID displays the course info stored in the file
				int check=0;
				string filename;
				string code;
				string data;
				ifstream input;
				cout<<"Enter File name to read data from"<<endl;
				cin>>filename;
				cout<<"Enter The Book Code you want to search for "<<endl;
				cin>>code;

				input.open(filename.c_str());
				while(! input.eof())
				{
					getline (input,data,' ');
					if (data == code)
					{
						check = 1;
						cout<<endl;
						getline(input,data,',');
						cout<<data;
						cout<<endl;
					}
				}

				input.close();

				if ( check != 1)
				{
					cout<<"No course with this ID found"<<endl;
				}

			}

			void SetBook() // takes input from user to initallize all variables of the book
			{				// used in adding node to head in the linked list
						cout<<"Enter Book ID :";
						cin>>ID;
						cout<<"Enter Book Name :";
						cin>>bookName;
						cout<<"Enter Author Name :";
						cin>>Author;
						cout<<"Enter ISBN :";
						cin>>ISBN;
						cout<<"Enter Book's Price";
						cin>>price;
						cout<<"Enter Book's Total Pages";
						cin>>pages;
						cout<<"Enter ID of the Student who the the Book is Issued to(If not issued to Enter -1)";
						cin>>IssuedBy;
						cout<<"Enter Date Issued On ( If not issued Enter -1)";
						cin>>IssuedOn;
						cout<<"Enter Return Date ( If not issued Enter -1)";
						cin>>returnDate;
			}

			//get functutions for all private members
			int getID() { return ID;}
			string getBookName() {return bookName;}
			string getAuthor() {return Author;}
			string getISBN() {return ISBN;}
			int getPrice() {return price;}
			int getPages() {return pages;}
			int getIssuedby() {return IssuedBy;}
			string getIssuedOn() {return IssuedOn;}
			string getReturnDate() {return returnDate;}

			//set funcutions

			void setID(int id){ID=id;}
			void setBookName(string name){bookName = name;}
			void setAuthour(string authr) {Author = authr;}
			void setISBN(int isbn){ISBN=isbn;}
			void setPrice(int p){price=p;}
			void setPages(int p){pages=p;}
			void setIssuedBy(int iby){IssuedBy=iby;}
			void setIssuedOn(string ion){IssuedOn=ion;}
			void setReturnDate(string Rdate){returnDate=Rdate;}

			void printAll()
			{
				cout<<"ID : "<<ID<<endl;
				cout<<"Book Title : "<<bookName<<endl;
				cout<<"Author : "<<Author<<endl;
				cout<<"ISBN : "<<ISBN<<endl;
				cout<<"Price : "<<price<<endl;
				cout<<"Pages : "<<price<<endl;
				cout<<"Issued By : "<<IssuedBy<<endl;
				cout<<"Issued ON : "<<IssuedOn<<endl;
				cout<<"Return Date : "<<returnDate<<endl;

			}

			void writeToFile() // writes data to file
			{
				ofstream output;
				output.open("Books.txt",ios::app);
				output<<"ID : "<<ID<<endl;
				output<<"Book Title : "<<bookName<<endl;
				output<<"Author : "<<Author<<endl;
				output<<"ISBN : "<<ISBN<<endl;
				output<<"Price : "<<price<<endl;
				output<<"Pages : "<<price<<endl;
				output<<"Issued By : "<<IssuedBy<<endl;
				output<<"Issued ON : "<<IssuedOn<<endl;
				output<<"Return Date : "<<returnDate<<","<<endl<<endl;
			}


};

class CBookList {

	struct Node{
		CBook Book;
		Node *next;
	};
	Node *ListHeadPtr;

	public:
			CBookList()
			{
				ListHeadPtr = NULL;
			}

			~CBookList()
			{
				Node *ptrPrevious;
				while (ListHeadPtr != NULL)
				{
					ptrPrevious = ListHeadPtr;
					ListHeadPtr = ListHeadPtr->next;
					delete ptrPrevious;
				}
			}

			void AddBookToHead() // this funcution takes input from user to set up a new book
			{
				Node *ptrnew = new Node;
				ptrnew->Book.SetBook();
				ptrnew->next = ListHeadPtr;
				ListHeadPtr = ptrnew;
			}

			void AddBookToHead(CBook book) // overloaded function for adding a book at head
			{
				Node *ptrnew = new Node;
				ptrnew->Book = book;
				ptrnew->next = ListHeadPtr;
				ListHeadPtr = ptrnew;
			}

			void DisplayList() // displays the whole list
			{
				Node *ptrTemp = ListHeadPtr;
				cout<<endl;
				while(ptrTemp != NULL)
				{
					ptrTemp->Book.printAll();
					ptrTemp=ptrTemp->next;
				}
			}

			void DisplaySpecificBook(int key) // displays the info of a specific book
			{
				Node *ptrCurrent = ListHeadPtr;

				while(ptrCurrent != NULL && ptrCurrent->Book.getID() != key)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Book exists with Such ID"<<endl;
				else
				{
						cout<<"FOLLOWING RECORD FOUND AGAINST THE GIVEN ID"<<endl;
						ptrCurrent->Book.printAll();
				}
			}

			void DeleteBook(int key) //deletes a specific book
			{
				Node *ptrCurrent = ListHeadPtr;
				Node *ptrPrevious;

				while(ptrCurrent != NULL && ptrCurrent->Book.getID() != key)
				{
					ptrPrevious = ptrCurrent;
					ptrCurrent=ptrCurrent->next;
				}
				if (ptrCurrent == NULL)
					cout<<"No Book exists with Such ID"<<endl;

				if (ptrCurrent == ListHeadPtr)
						ListHeadPtr=ListHeadPtr->next;

				else
					ptrPrevious->next = ptrCurrent->next;

					delete ptrCurrent;
			}

			void SortListAscending() // sorts the list in ascending order
			{
				Node *TempHead = ListHeadPtr;
				int Counter=0;
				CBook TempBook;

				while ( TempHead!= NULL)
				{
					TempHead=TempHead->next;
					Counter++;
				}

				TempHead = ListHeadPtr;

				for (int i=0;i<Counter;i++)
				{
					 while(TempHead->next != NULL)
					 {
					 	if (TempHead->Book.getID() > TempHead->next->Book.getID())
					 	{
					 		TempBook = TempHead->Book;
					 		TempHead->Book = TempHead->next->Book;
					 		TempHead->next->Book = TempBook;

					 	}

					 	else
					 		TempHead = TempHead->next;
					 }
				}
				TempHead = ListHeadPtr;

			}

			void SortListDescending() // sort the list in descending order
			{
				Node *TempHead = ListHeadPtr;
				int Counter=0;
				CBook TempBook;

				while ( TempHead!= NULL)
				{
					TempHead=TempHead->next;
					Counter++;
				}

				TempHead = ListHeadPtr;

				for (int i=0;i<Counter;i++)
				{
					 while(TempHead->next != NULL)
					 {
					 	if (TempHead->Book.getID() < TempHead->next->Book.getID())
					 	{
					 		TempBook = TempHead->Book;
					 		TempHead->Book = TempHead->next->Book;
					 		TempHead->next->Book = TempBook;

					 	}

					 	else
					 		TempHead = TempHead->next;
					 }
				}
				TempHead = ListHeadPtr;

			}

			void writeToFile() // writes whle list to file
			{

				Node *ptrTemp = ListHeadPtr;
				while(ptrTemp!= NULL)
				{
				ptrTemp->Book.writeToFile();
				ptrTemp=ptrTemp->next;
				}
			}

			void WriteSpecificBook(int ID) //writes a specific  book to the file
			{
				Node *ptrCurrent = ListHeadPtr;

				while(ptrCurrent != NULL && ptrCurrent->Book.getID() != ID)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Book exists with Such ID"<<endl;
				else
				{

						ptrCurrent->Book.writeToFile();
				}
			}

			CBook returnBook(int ID) //  returns the instance of a specific book
			{
				Node *ptrCurrent = ListHeadPtr;

				while(ptrCurrent != NULL && ptrCurrent->Book.getID() != ID)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Book exists with Such ID"<<endl;
				else
				{

						return ptrCurrent->Book;
				}
			}
};
                                                                                                                                                                                                                                                                  string student_pass="umt";
class CStudent {

	private :
	  		 string ID;
	  		 string StdName;
	  		 string RollNo;
	  		 int BooksIssued;

	public :
			CStudent()
			{
				ID="";
				StdName='\0';
				RollNo= "";
				BooksIssued = 0;
			}

		//constructer
			CStudent ( string id,string name, string roll)
			{
				ID=id;
				StdName=name;
				RollNo=roll;
				BooksIssued = 0;
			}

			//get functuions

			string getId() {return ID;}
			string getName(){return StdName;}
			string getRollNo(){return RollNo;}
			int getBooksIssued(){return BooksIssued;}

			//set Funcutions

			void seId(string id){ID = id;}
			void setName(string name){StdName=name;}
			void setRollno(string Roll){RollNo = Roll;}
			void setBooksIssued(int bi){BooksIssued=bi;}

			void ReadFrmFile () //takes in a filename and student ID then searches for the code in file
			{								//upon finding the ID displays the Student info stored in the file
				int check=0;
				string filename;
				string code;
				string data;
				ifstream input;
				cout<<"Enter File name to read data from"<<endl;
				cin>>filename;
				cout<<"Enter The Student ID you want to search for "<<endl;
				cin>>code;

				input.open(filename.c_str());
				while(! input.eof())
				{
					getline (input,data,' ');
					if (data == code)
					{
						check = 1;
						cout<<endl;
						getline(input,data,',');
						cout<<data;
						cout<<endl;
					}
				}

				input.close();

				if ( check != 1)
				{
					cout<<"No Student with this ID found"<<endl;
				}

			}

			void SetStudent()
			{
				cout<<"Enter ID :";
				getline(cin ,ID);
				cin.ignore();
				cout<<"\nEnter Student Name :";
				getline(cin,StdName);
				cin.ignore();
				cout<<"\nEnter Roll Num ";
				getline(cin,RollNo);
				cin.ignore();
				cout<<"\nEnter ID of Books Issued ( Enter 0 if No book Issued)";
				cin>>BooksIssued;
				cin.ignore();
			}

			//print all functions
			void PrintAll()
			{
				cout<<"ID :  "<<ID;
				cout<<"\nName : "<<StdName;
				cout<<"\nRoll No : "<<RollNo;
				cout<<"\nBooks Issued : "<<BooksIssued;
			}

			void writeToFile()
			{
				ofstream output;
				output.open("Student.txt",ios::app);
				output<<"ID : "<<ID<<endl;
				output<<"Name : "<<StdName<<endl;
				output<<"Roll No : "<<RollNo<<endl;
				output<<"Books Issued : "<<BooksIssued<<","<<endl<<endl;

			}

};

class CStudentList {

		struct Node{
				CStudent Student;
				Node *next;
			};
		Node *ListHeadPtr;

	public:
			CStudentList()
			{
				ListHeadPtr = NULL;
			}
			~CStudentList()
			{
				Node *ptrPrevious;
				while (ListHeadPtr != NULL)
				{
					ptrPrevious = ListHeadPtr;
					ListHeadPtr = ListHeadPtr->next;
					delete ptrPrevious;
				}
			}

			void AddStudentToHead()
			{
				Node *ptrnew = new Node;
				ptrnew->Student.SetStudent();
				ptrnew->next = ListHeadPtr;
				ListHeadPtr = ptrnew;
			}

			void DisplayList()
			{
				Node *ptrTemp = ListHeadPtr;
				cout<<endl;
				if(ListHeadPtr==NULL)
                  {

                    cout<<"\n List is empty\n First enter elements in the list\n";
                  }
				else
				{


                        while(ptrTemp != NULL)
				{
					ptrTemp->Student.PrintAll();
					ptrTemp=ptrTemp->next;
				}
			}}

			void DisplaySpecificStudent(string key)
			{
				Node *ptrCurrent = ListHeadPtr;

				while(ptrCurrent != NULL && ptrCurrent->Student.getId()!= key)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Student exists with Such ID"<<endl;
				else
				{
						cout<<"FOLLOWING RECORD FOUND AGAINST THE GIVEN ID"<<endl;
						ptrCurrent->Student.PrintAll();
				}
			}

			void DeleteStudent(string key)
			{
				Node *ptrCurrent = ListHeadPtr;
				Node *ptrPrevious;

				while(ptrCurrent != NULL && ptrCurrent->Student.getId() != key)
				{
					ptrPrevious = ptrCurrent;
					ptrCurrent=ptrCurrent->next;
				}
				if (ptrCurrent == NULL)
					cout<<"No Student exists with Such ID"<<endl;

				if (ptrCurrent == ListHeadPtr)
						ListHeadPtr=ListHeadPtr->next;

				else
					ptrPrevious->next = ptrCurrent->next;

					delete ptrCurrent;
			}

			void SortList()
			{
				Node *TempHead = ListHeadPtr;
				int Counter=0;
				CStudent TempStudent;

				while ( TempHead!= NULL)
				{
					TempHead=TempHead->next;
					Counter++;
				}

				TempHead = ListHeadPtr;

				for (int i=0;i<Counter;i++)
				{
					 while(TempHead->next != NULL)
					 {
					 	if (TempHead->Student.getId() > TempHead->next->Student.getId())
					 	{
					 		TempStudent = TempHead->Student;
					 		TempHead->Student = TempHead->next->Student;
					 		TempHead->next->Student = TempStudent;

					 	}

					 	else
					 		TempHead = TempHead->next;
					 }
				}
				TempHead = ListHeadPtr;

			}

			void writeToFile()
			{

				Node *ptrTemp = ListHeadPtr;
				while(ptrTemp!= NULL)
				{
				 ptrTemp->Student.writeToFile();
				 ptrTemp=ptrTemp->next;
				}
			}

			void WriteSpecificStudent(string ID)
			{
				Node *ptrCurrent = ListHeadPtr;

				while(ptrCurrent != NULL && ptrCurrent->Student.getId() != ID)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Student exists with Such ID"<<endl;
				else
				{

				ptrCurrent->Student.writeToFile();
				}
			}

			void IssueBook(string ID, int bookID) // issues a book to a student
			{
				Node *ptrCurrent = ListHeadPtr;
				//bookID=-1;

				while(ptrCurrent != NULL && ptrCurrent->Student.getId() != ID)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Student exists with Such ID"<<endl;
				else if (ptrCurrent->Student.getBooksIssued() != 0)
						cout<<"Student Already has a Book"<<endl;
				else
				{
						ptrCurrent->Student.setBooksIssued(bookID);
				}
			}

			void ReturnBook(string ID , int bookID) // returns a book from a student
			{
				Node *ptrCurrent = ListHeadPtr;
				bookID=-1;

				while(ptrCurrent != NULL && ptrCurrent->Student.getId() != ID)
						ptrCurrent=ptrCurrent->next;

				if (ptrCurrent == NULL)
						cout<<"No Student exists with Such ID"<<endl;
				if (ptrCurrent->Student.getBooksIssued() != bookID)
						cout<<"This Student was not Issued this Book"<<endl;
				else
				{
						ptrCurrent->Student.setBooksIssued(0);
				}
			}
};

class CLibrary {

	private :
			CBookList AvailableBooks;
			CBookList BooksIssued;
			CStudentList Students;

	public :
			CLibrary()
			{
			}

			void AddBook()
			{
				AvailableBooks.AddBookToHead();
			}

			void DeleteBook()
			{
				int ID;
				cout<<"Enter Book ID"<<endl;
				cin>>ID;
				AvailableBooks.DeleteBook(ID);
			}

			void DisplayAvailableBooks()
			{
				AvailableBooks.DisplayList();
			}

			void DisplayIssuedBooks()
			{
				BooksIssued.DisplayList();
			}

			void DisplayBook()
			{
				int ID;
				cout<<"Enter Book ID"<<endl;
				cin>>ID;
				AvailableBooks.DisplaySpecificBook(ID);
			}

			void SortAvailableBooksAscending()
			{
				AvailableBooks.SortListAscending();
			}

			void SortAvailableBooksDescending()
			{
				AvailableBooks.SortListDescending();
			}

			void WriteAvailableBooksToFile()
			{
				AvailableBooks.writeToFile();
			}

			void WriteBookToFile()
			{
				int ID;
				cout<<"Enter Book ID"<<endl;
				cin>>ID;
				AvailableBooks.WriteSpecificBook(ID);
			}

			void AddStudent()
			{
				Students.AddStudentToHead();
			}

			void DeleteStudent()
			{
				string ID;
				cout<<"Enter Id of Student You Wish to Delete"<<endl;
				getline(cin,ID);
				Students.DeleteStudent(ID);
			}

			void DisplayStudents()
			{
				Students.DisplayList();
			}

			void DisplaySpecificStudent()
			{
				string ID;
				cout<<"Enter ID of Student"<<endl;
				getline(cin,ID);
				Students.DisplaySpecificStudent(ID);
			}

			void writeStudentsfile()
			{
				Students.writeToFile();
			}

			void writeStudentFile()
			{
				string ID;
				cout<<"Enter ID of Student "<<endl;
				getline(cin,ID);
				Students.WriteSpecificStudent(ID);
			}

			void ReadBookFromFile()
			{
				CBook B1;
				B1.ReadFrmFile();
			}

			void ReadStudentFromFile()
			{
				CStudent S1;
				S1.ReadFrmFile();
			}

			void IssueBook()
			{
				string ID;
				int BookID;
				cout<<"Enter ID of book you want to Issue"<<endl;
				cin>>BookID;
				cout<<"Enter ID of Student who wants the Book Issued"<<endl;
				getline(cin,ID);

				Students.IssueBook(ID,BookID);

				CBook Temp;
				Temp = AvailableBooks.returnBook(BookID);

				BooksIssued.AddBookToHead(Temp);

				AvailableBooks.DeleteBook(BookID);

			}

			void ReturnBook()
			{
				string ID;
				int BookID;
				cout<<"Enter ID of book Being Returned"<<endl;
				cin>>BookID;
				cout<<"Enter ID of Student who is Returning the Book Issued"<<endl;
				getline(cin,ID);
				Students.IssueBook(ID,BookID);

				CBook Temp;
				Temp = BooksIssued.returnBook(BookID);

				AvailableBooks.AddBookToHead(Temp);

				BooksIssued.DeleteBook(BookID);
			}



};

void ProjectX()
{
	CLibrary Library;


	//////////////////////////////////////////
	///////////////CLEAR SCREEN/////////////// BY AHR....
	//////////////////////////////////////////

	system("cls");

	int x,y,ID;
	bool loop=true;

	while (loop == true) {
            system("cls");

	cout << "\n\n=============================== MAIN MENU =================================\n";
    cout << "\n======== Options ===================================== Code ===============\n";
    cout << "\n======== Student's Menu ================================ 1 ================\n";
    cout << "\n======== Book's Menu =================================== 2 ================\n";
    cout << "\n======== Library's Menu ================================ 3 ================\n";
    cout << "\n======== EXIT ========================================== 4 ================\n";
	cout << "\n========================YOUR CHOICE=>                ======================\n";///////////////////
	cout << "\n=====================================                ======================\n";/////////////////// BY AHR.....
	gotoxy(40,14);
	cin>>x;
	gotoxy(40,16);
	cout<<"loading...";
	_sleep(1800);
    system("cls");

	switch(x){

			case 1 :

			    if(login()==student_pass)
			        {  gotoxy(39,8);
			          cout<<"loading...";
			            _sleep(5000);

                        gotoxy(39,9);
			            cout<<"Access granted!!!";
			            gotoxy(39,10);
			            cout<<" Please wait.";
                        _sleep(5000);
			           system("cls");

					  {
                      cout << " ****************************************************************************\n";
					  cout << " **************************  STUDENT MENU  **********************************\n";
					  cout << " ****************************************************************************\n";
     				  cout << "|                                                                            |\n";
     				  cout << "| Press 1 to Add New Student                                                 |\n";
 				      cout << "| Press 2 to Delete Existing Student                                         |\n";
   				      cout << "| Press 3 to Show particular student                                         |\n";
   				  	  cout << "| Press 4 to Show all Students                                               |\n";
   				  	  cout << "| Press 5 to Write Info of All Students on a file                            |\n";
   				  	  cout << "| Press 6 to Write info of specific Student on a file                        |\n";
   				  	  cout << "| Press 7 to Read Info of a Specific Student from file                       |\n";
					  cout << "| Press 8 to Exit                                                            |\n";
					  cout << "|****************************************************************************|\n";
                      cout << "\n ************************YOUR CHOICE=>                ***********************\n";///////////////////
	                  cout << "\n ************************                             ***********************\n";/////////////////// BY AHR.....
                      gotoxy(40,14);
					  cin>>y;
					  	gotoxy(35,16);
	                  cout<<"loading...";
	                   _sleep(1800);

	                   system("cls");

					  switch (y)
					  {
					  	case 1 : Library.AddStudent();
					  	cout<<"\nOPERATION SUCCESSFUL..";
					  	_sleep(1800);
					  			break;
					  	case 2 : Library.DeleteStudent();

                        cout<<"\nOPERATION SUCCESSFUL..";
					  	_sleep(1800);break;
					  	case 3 : Library.DisplaySpecificStudent();
                        cout<<"\nOPERATION SUCCESSFUL..";
					  	_sleep(1800);
					  			break;
					  	case 4 : Library.DisplayStudents();

                        cout<<"\nOPERATION SUCCESSFUL..";
					  	_sleep(1800);

					  			break;
					  	case 5 : Library.writeStudentsfile();

                        cout<<"\nOPERATION SUCCESSFUL..";
					  	_sleep(1800);
					  			break;
						case 6 : Library.writeStudentsfile();
						cout<<"\nOPERATION SUCCESSFUL..";
					  	_sleep(1800);
								break;
						case 7 : Library.ReadStudentFromFile();
					  	default : cout<<"Invalid Number Enterd"<<endl;
					  			break;

					    case 8 :
                            break;
					  }
						}}else
						{  gotoxy(39,8);
						    cout<<"Wrong password \nReturning to main menu";
						    _sleep(2000);
						}
					  break;

			case 2 :  {
					  cout << " ****************************************************************************\n";
     				  cout << "|                                                                            |\n";
     				  cout << "| Press 1 to Add New Book                                                    |\n";
 				      cout << "| Press 2 to Delete Existing Book                                            |\n";
   				      cout << "| Press 3 to Show particular Book                                            |\n";
   				  	  cout << "| Press 4 to Show all Books                                                  |\n";
   				  	  cout << "| Press 5 to Sort Books in Ascending order                                   |\n";
   				  	  cout << "| Press 6 to Sort Books in Descending order                                  |\n";
   				  	  cout << "| Press 7 to Write All Books on a File                                       |\n";
					  cout << "| Press 8 to Write Specific Book on File                                     |\n";
					  cout << "| Press 9 to Read Book from File                                             |\n";
					  cout << "|****************************************************************************|\n";

					  cin>>y;
					  switch(y)
					  {
					  	case 1 : Library.AddBook();
					  			break;
						case 2 : Library.DeleteBook();
								break;
					  	case 3 : Library.DisplayBook();
					  			break;
					  	case 4 : Library.DisplayAvailableBooks();
					  			break;
					  	case 5 : Library.SortAvailableBooksAscending();
					  			break;
					  	case 6 : Library.SortAvailableBooksDescending();
					  			break;
					  	case 7 : Library.WriteAvailableBooksToFile();
					  			break;
					  	case 8 : Library.WriteBookToFile();
					  			break;
					  	case 9 : Library.ReadBookFromFile();
					  			break;
					  	default : cout<<"Invalid Number Enterd"<<endl;
					  			break;
					  }
					 }
					  break;
			case 3 :
		   			{
		   			  cout << " ****************************************************************************\n";
     				  cout << "| Press 1 to Issue a book                                                    |\n";
 				      cout << "| Press 2 to Return a book                                                   |\n";
   				      cout << "| Press 3 to Print which books have been issued                              |\n";
					  cout << "| Press 4 to Print Available Books                                           |\n";
					  cout << " ****************************************************************************\n";
					cin>>y;
					switch(y)
					  {
					  	case 1 : Library.IssueBook();
					  			break;
						case 2 : Library.ReturnBook();
					  			break;
					  	case 3 : Library.DisplayIssuedBooks();
					  			break;
					  	case 4 : Library.DisplayAvailableBooks();
					  			 break;
					  	default : cout<<"Invalid Number Enterd"<<endl;
					  			break;
					  }
				   }
					  break;
			case 4 : {
					 loop =false;
					 break;
					}
					 break;
			default : {
						cout<<"invalid choice"<<endl;
					  }
	}
	}

}

int main()
	{
     system("Color 17");
	 ProjectX();

	getch();
	return 0;
}



///////////////////////////////////////////////////////
/////////////////////PASSWORD ******///////////////////
/////////////////////MECANISM////////////////////////// BY AHR
///////////////////////////////////////////////////////

string login(){
    system ("cls");
       string pass ="";
   char ch;
   gotoxy(39,5);
   cout << "////////////////////////////////////////\n";
   gotoxy(39,6);
   cout << "  Enter password : ";


   ch = getch();
   while(ch != 13){//character 13 is enter
      pass.push_back(ch);
      cout << '*';
      ch = getch();
   }
    gotoxy(39,7);
    cout << "////////////////////////////////////////\n";

     return pass;





}
