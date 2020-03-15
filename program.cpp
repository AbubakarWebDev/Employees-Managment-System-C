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
//        FUNCTIONs PROTOTYPING THAT USED IN PROJECTS
//****************************************************************
int mainmenu();               // function that print the Main Menu on Console Screen.
bool validateInput();         // fuction that Validate Input Prints Error.
bool isEmpty(ifstream &file); // function that checks file is empty or not.

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
     char name[100], post[100], department[100];
     double salary;

public:
     // constructor function
     Employee()
     {
          // Default Initialization Except Garbage Value
          id = 0;
          strcpy(name, "no name");
          strcpy(name, "no post");
          strcpy(name, "no department");
          salary = 0;
     }

     // member function
     void getData();             // function use to get Employees Record From User.
     void writeFile();           // function use to Write Employees Records in a file that get From User.
     void readFile();            // function use to Read Employees Records from a file.
     void showData();            // function use to Show All Employees Records.
     void searchData(int input); // function use to search Data from file.
     void updateData(int input); // function use to Update Data from file.
     void deleteData(int input); // function use to Delete Data from file.
     void sortData();            // function that Sorts Employees Data in Desending Order w.r.t Salary.
};

//***************************************************************
//           DEFINATION OF MEMBER FUNCTIONS OF CLASS
//****************************************************************
void Employee::getData()
{
label:
     bool flag;

     cin.ignore();
     cout << "Enter Employee Name : ";
     cin.getline(name, 100);

     flag = validateInput();
     if (flag)
          goto label;

     cout << "Enter Employee Unique ID : ";
     cin >> id;

     flag = validateInput();
     if (flag)
          goto label;

     cin.ignore();
     cout << "Enter Employee Post : ";
     cin.getline(post, 100);

     flag = validateInput();
     if (flag)
          goto label;

     cout << "Enter Employee Department : ";
     cin.getline(department, 100);

     flag = validateInput();
     if (flag)
          goto label;

     cout << "Enter Employee Salary : ";
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
     ifstream file;
     file.open(fileName, ios::in | ios::binary);

     if (!file)
     {
          cout << "File can not Open";
     }
     else
     {
          if (isEmpty(file))
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
     cout << "\nEmployee Name is : ";
     cout << name << endl;

     cout << "Employee ID is : ";
     cout << id << endl;

     cout << "Employee post is : ";
     cout << post << endl;

     cout << "Employee Department is : ";
     cout << department << endl;

     cout << "Employee Salary is : ";
     cout << salary << endl;
}

void Employee::searchData(int input)
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
               if (input == id)
               {
                    showData();
                    flag = true;
               }
               file.read((char *)this, sizeof(*this));
          }

          file.close();

          if (!flag)
          {
               cout << "Record For This ID Does Not Exist";
          }
     }
}

void Employee::updateData(int input)
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
               if (input == id)
               {
                    showData();
                    cout << "\nEnter Updated Record :- \n\n";
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
               cout << "Record For This ID Does Not Exist";
          }
          else
          {
               cout << "\nNew Records Has Been Updated Successfully\n";
          }
     }
}

void Employee::deleteData(int input)
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
               if (input != id)
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
               cout << "Record For This ID Does Not Exist";
          }
          else
          {
          label:
               fstream file;
               file.open(fileName, ios::in | ios::binary);
               int choice;
               while (file.read((char *)this, sizeof(*this)))
               {
                    if (input == id)
                    {
                         showData();
                    }
               }
               file.close();
               cout << "\nAre Your Sure to Delete The Above Record\n";
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
               else if (choice == 2)
               {
                    remove("tempfile.dat");
               }
               else
               {
                    cin.clear();
                    cin.ignore();
                    cout << "Error : Invalid Choice Detected! Please Enter Valid Choice";
                    goto label;
               }
          }
     }
}

void Employee::sortData()
{
     int size, fileSize, objSize, position;
     Employee *ptr = NULL;

     ifstream file;
     file.open("file.dat", ios::in | ios::binary);

     if (isEmpty(file))
     {
          cout << "\nYour File is Empty! No Record is Avialable to Show\n";
     }
     else
     {
          file.seekg(0, ios::end);

          fileSize = static_cast<int>(file.tellg());
          objSize = static_cast<int>(sizeof(*this));
          size = fileSize / objSize;

          ptr = new Employee[size];

          file.seekg(0, ios::beg);

          for (int i = 0; i < size; i++)
          {
               file.read((char *)&ptr[i], sizeof(*this));
          }
          file.close();

          for (int i = 0; i < size; i++)
          {
               for (int j = i + 1; j < size; j++)
               {
                    if (ptr[i].salary < ptr[j].salary)
                    {
                         swap(ptr[i], ptr[j]);
                    }
               }
          }

          cout << "\n\n======== Sorted Employee Details With Respect to Salary ========\n\n";

          for (int i = 0; i < size; i++)
          {
               ptr[i].showData();
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
     cout << "6 : Sort Employee Records with respect to Salary\n";
     cout << "7 : Exit Application\n";
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

bool isEmpty(ifstream &file)
{
     return (file.peek() == ifstream::traits_type::eof());
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
     system("color f0");
     system("title Employeees Managment System by Muhammad Abubakar");
     bool check = true;
     int search;
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
                    cout << "\nNew Records Has Been Added Successfully\n";
                    break;
               }
          case 2:
               cout << "\n\n=============== Employee Details ==================\n\n";
               filedata.readFile();
               break;
          case 3:
               cout << "Please Enter Employee Unique ID That you Want to Search its Record : ";
               cin >> search;
               filedata.searchData(search);
               break;
          case 4:
               cout << "Please Enter Employee Unique ID That you Want to Update its Record : ";
               cin >> search;
               filedata.updateData(search);
               break;
          case 5:
               cout << "Please Enter Employee Unique ID you Want to Delete its Record : ";
               cin >> search;
               filedata.deleteData(search);
               break;
          case 6:
               filedata.sortData();
               break;
          case 7:
               cout << "\nThank You For Using This Application\n";
               check = false;
               break;
          default:
               cout << "Invalid Choice! Please Select Valid Choice.";
               break;
          }
          cout << endl;
          cout << endl;
          system("pause");
     }
}