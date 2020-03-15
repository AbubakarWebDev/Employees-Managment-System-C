//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
#include <iomanip>
using namespace std;

//***************************************************************
//            FUNCTION PROTOTYPING USED IN PROJECTS
//****************************************************************
bool validateInput();
int mainmenu();

//***************************************************************
//                   GLOBAL VARIABLES
//****************************************************************
const char *fileName = "file.dat";

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
class Employee
{
private:
     int id;
     char name[100];
     int age;
     int salary;

public:
     // constructor function
     Employee()
     {
          // Default Initialization Except Garbage Value
          id = 0;
          strcpy(name, "no name");
          age = 0;
          salary = 0;
     }

     // member function
     void getData();             // function use to get Employees Record From User.
     void writeFile();           // function use to Write Employees Records in a file that get From User.
     void readFile();            // function use to Read Employees Records from a file.
     void showData();            // function use to Show All Employees Records.
     void searchData(char *str); // function use to search Data from file.
     void updateData(char *str); // function use to Update Data from file.
     void deleteData(char *str); // function use to Delete Data from file.
};

//***************************************************************
//           DEFINATION OF MEMBER FUNCTIONS OF CLASS
//****************************************************************
void Employee::getData()
{
label:
     bool flag;

     cin.ignore();
     cout << "Enter Your Name : ";
     cin.getline(name, 100);

     flag = validateInput();
     if (flag)
          goto label;

     cout << "Enter Your ID : ";
     cin >> id;

     flag = validateInput();
     if (flag)
          goto label;

     cout << "Enter Your Age : ";
     cin >> age;

     flag = validateInput();
     if (flag)
          goto label;

     cout << "Enter Your Salary : ";
     cin >> salary;

     flag = validateInput();
     if (flag)
          goto label;
}

void Employee::writeFile()
{
     if (name == "no name" && id == 0)
     {
          cout << "Employee Record is not initalized" << endl;
     }
     else
     {
          fstream file;
          file.open(fileName, ios::out | ios::app | ios::binary);

          file.write((char *)this, sizeof(*this));

          file.close();
     }
}

void Employee::readFile()
{
     fstream file;
     file.open(fileName, ios::in | ios::binary);

     if (!file)
     {
          cout << "File can not Open";
     }
     else
     {
          if (file.peek() == ifstream::traits_type::eof())
          {
               cout << "\nYour File is Empty! No Record is Avialable to Show\n";
          }
          else
          {
               file.read((char *)this, sizeof(*this));

               while (!file.eof())
               {
                    showData();
                    file.read((char *)this, sizeof(*this));
               }

               file.close();
          }
     }
}

void Employee::showData()
{
     cout << "Enter Your Name : ";
     cout << name << endl;

     cout << "Enter Your ID : ";
     cout << id << endl;

     cout << "Enter Your Age : ";
     cout << age << endl;

     cout << "Enter Your Salary : ";
     cout << salary << endl;

     cout << endl
          << endl;
}

void Employee::searchData(char *str)
{
     bool flag = false;

     fstream file;
     file.open(fileName, ios::in | ios::binary);

     if (!file)
     {
          cout << "File Cannot be Open";
     }
     else
     {
          file.read((char *)this, sizeof(*this));
          while (!file.eof())
          {
               if (!strcmp(str, name))
               {
                    showData();
                    flag = true;
               }
               file.read((char *)this, sizeof(*this));
          }

          file.close();

          if (!flag)
          {
               cout << "Record For This Name Does Not Exist";
          }
     }
}

void Employee::updateData(char *str)
{
     bool flag = false;
     fstream file;
     file.open(fileName, ios::in | ios::out | ios::ate | ios::binary);

     if (!file)
     {
          cout << "File Cannot Open Successfully!";
     }
     else
     {
          file.seekg(0, ios::beg);
          file.read((char *)this, sizeof(*this));
          while (!file.eof())
          {
               if (!strcmp(str, name))
               {
                    showData();
                    getData();
                    int position = (-1) * static_cast<int>(sizeof(*this));
                    file.seekp(position, ios::cur);
                    file.write((char *)this, sizeof(*this));
                    flag = true;
               }
               file.read((char *)this, sizeof(*this));
          }

          if (!flag)
          {
               cout << "Record For This Name Does Not Exist";
          }
     }
}

void Employee::deleteData(char *str)
{
     int c1, c2;
     bool flag = true;
     ofstream fout;
     ifstream fin;
     fin.open(fileName, ios::in | ios::binary);

     if (!fin)
     {
          cout << "File Cannot Open Successfully!";
     }
     else
     {
          fin.read((char *)this, sizeof(*this));
          fout.open("tempfile.dat", ios::out | ios::binary);
          while (!fin.eof())
          {
               if (strcmp(str, name))
               {
                    fout.write((char *)this, sizeof(*this));
               }
               fin.read((char *)this, sizeof(*this));
          }
          fin.close();
          fout.close();

          fstream f1, f2;
          f1.open(fileName, ios::in | ios::binary);
          f2.open("tempfile.dat", ios::in | ios::binary);

          while (true)
          {
               c1 = f1.get();
               c2 = f2.get();
               if (c1 != c2)
               {
                    flag = false;
                    break;
               }
               if ((c1 == EOF) || (c2 == EOF))
                    break;
          }

          f1.close();
          f2.close();

          if (flag)
          {
               cout << "Record For This Name Does Not Exist";
          }
          else
          {
               int choice;
               cout << "Are Your Sure to Delete This Record\n";
               cout << "1 : Yes\n";
               cout << "2 : No\n";
               cout << "Enter Your Choice : ";
               cin >> choice;
               if (choice == 1)
               {
                    remove(fileName);
                    rename("tempfile.dat", fileName);
                    cout << "\n\nRecord is Deleted Successfully";
               }
          }
     }
}

//***************************************************************
//            FUNCTION DEFINATION USED IN PROJECTS
//****************************************************************
int mainmenu()
{
label:
     system("cls");
     int choice;
     bool flag;
     cout << "\n\n=============== Employee Managment System ==================\n\n";
     cout << "Please Select Your Choice :- \n";
     cout << "1 : Insert Employees Records\n";
     cout << "2 : View All Employees Records\n";
     cout << "3 : Search Employees Records\n";
     cout << "4 : Update Employee Records\n";
     cout << "5 : Delete Employee Records\n";
     cout << "6 : Exit Application\n";
     cout << "Enter Your Choice : ";
     cin >> choice;

     flag = validateInput();
     if (flag)
     {
          goto label;
     }
     else
     {
          return choice;
     }
}

bool validateInput()
{
     if (cin.fail())
     {
          // Restore input stream
          cin.clear();
          // Clear The Previous Input
          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          // Throwing Error and Again Input Value From User
          cout << "\nError : inValid Value Detected! Please Enter Valid Value Again\n\n";

          return true;
     }
     else
     {
          return false;
     }
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
     system("color f0");
     system("title Employeee Managment System by Abubakar");
     bool check = true;
     char search[100];
     int size;
     bool flag;
     Employee *ptr = NULL;
     Employee filedata;

     while (check)
     {
          system("cls");
          switch (mainmenu())
          {
          case 1:
          label1:
               cout << "How Many Employees Records that You Want to Store : ";
               cin >> size;

               flag = validateInput();

               if (flag)
               {
                    goto label1;
               }
               else
               {
                    ptr = new Employee[size];

                    for (int i = 0; i < size; i++)
                    {
                         cout << "\n\nEnter the Details For the Employee # " << i + 1 << endl;
                         ptr[i].getData();
                    }

                    for (int i = 0; i < size; i++)
                    {
                         ptr[i].writeFile();
                    }
                    break;
               }
          case 2:
               cout << "\n\n=============== Employee Details ==================\n\n";
               filedata.readFile();
               break;
          case 3:
               cout << "Please Enter Employee Name That you Want to Search its Record : ";
               cin.ignore();
               cin.getline(search, 100);
               filedata.searchData(search);
               break;
          case 4:
               cout << "Please Enter Employee Name That you Want to Update its Record : ";
               cin.ignore();
               cin.getline(search, 100);
               filedata.updateData(search);
               break;
          case 5:
               cout << "Please Enter Employee Name That you Want to Delete its Record : ";
               cin.ignore();
               cin.getline(search, 100);
               filedata.deleteData(search);
               break;
          case 6:
               cout << "\nThank You For Using This Application\n";
               check = false;
               break;
          default:
               cout << "Invalid Choice! Please Select Valid Choice.";
               break;
          }
          cout << endl;
          system("pause");
     }
}
