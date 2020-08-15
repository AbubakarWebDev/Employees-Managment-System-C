//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include <iostream>     // It is Used For Basic I/O Operations. 
#include <fstream>      // It is Used For File I/O Operations. 
#include <limits>       // It is Used For Get Numeric Limits. 
#include <cstring>      // It is Used For C String Handling. 
using namespace std;


//***************************************************************
//        FUNCTIONs PROTOTYPING THAT USED IN PROJECTS
//****************************************************************
int mainmenu();                     // function that print the Main Menu on Console Screen.
bool validateInput();               // fuction that Validate User Input & Prints Error.
bool isEmpty(ifstream &file);       // function that checks file is empty or not.


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
    void getData();             // function to get Employees Record From User.
    void writeFile();           // function to Write Employees Records in a file that get From User.
    void readFile();            // function to Read Employees Records from a file.
    void showData();            // function to Print All Employees Records that Read From a File.
    void searchData(int input); // function to search Data from file.
    void updateData(int input); // function to Update Data from file.
    void deleteData(int input); // function to Delete Data from file.
    void sortData();            // function to Sorts Employees Data in Desending Order w.r.t Salary.
};


//***************************************************************
//           DEFINATION OF MEMBER FUNCTIONS OF CLASS
//****************************************************************
void Employee::getData()
{
    bool flag = false;

label1:
    cout << "\tEnter Employee Name : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(name, 100);
    flag = validateInput();
    if (flag)
        goto label1;


label2:
    cout << "\tEnter Employee Unique ID : ";
    cin >> id;
    flag = validateInput();
    if (flag)
        goto label2;


label3:
    cout << "\tEnter Employee Post : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(post, 100);
    flag = validateInput();
    if (flag)
        goto label3;


label4:
    cout << "\tEnter Employee Department : ";
    cin.getline(department, 100);
    flag = validateInput();
    if (flag)
        goto label4;


label5:
    cout << "\tEnter Employee Salary : ";
    cin >> salary;
    flag = validateInput();
    if (flag)
        goto label5;
}

void Employee::writeFile()
{
    if (name == "no name" && id == 0)
    {
        cout << "\tEmployee Record is not initalized" << endl;
    }
    else
    {
        fstream file;
        file.open(fileName, ios::out | ios::app | ios::binary);

        file.write((char *)this, sizeof(*this));

        file.close();

        if (!file.good()) {  
            // For Check Any Error After Writing the file. For Example File Memory Full, File Format Errors. 
            cout << "\tError occurred at writing time!" << endl;
        }
    }
}

void Employee::readFile()
{
    ifstream file;
    file.open(fileName, ios::in | ios::binary);

    if (!file)
    {
        cout << "\tFile can not Open";
    }
    else
    {
        if (isEmpty(file))
        {
            cout << "\n\tYour File is Empty! No Record is Avialable to Show\n";
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
    cout << "\n\tEmployee Name is : ";
    cout << name << endl;

    cout << "\tEmployee ID is : ";
    cout << id << endl;

    cout << "\tEmployee post is : ";
    cout << post << endl;

    cout << "\tEmployee Department is : ";
    cout << department << endl;

    cout << "\tEmployee Salary is : ";
    cout << salary << endl;
}

void Employee::searchData(int input)
{
    bool flag = false;

    fstream file;
    file.open(fileName, ios::in | ios::binary);

    if (!file)
    {
        cout << "\tFile Cannot be Open";
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
            cout << "\tRecord For This ID Does Not Exist";
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
        cout << "\tFile Cannot Open Successfully!";
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
                cout << "\n\tEnter Updated Record :- \n\n";
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
            cout << "\tRecord For This ID Does Not Exist";
        }
        else
        {
            cout << "\n\tNew Records Has Been Updated Successfully\n";
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
        cout << "\tFile Cannot Open Successfully!";
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
            cout << "\tRecord For This ID Does Not Exist";
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
            cout << "\n\tAre Your Sure to Delete The Above Record\n";
            cout << "\t1 : Yes\n";
            cout << "\t2 : No\n";
            cout << "\tEnter Your Choice : ";
            cin >> choice;
            if (choice == 1)
            {
                remove(fileName);
                rename("tempfile.dat", fileName);
                cout << "\n\n\tRecord is Deleted Successfully";
            }
            else if (choice == 2)
            {
                remove("tempfile.dat");
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tError : Invalid Choice Detected! Please Enter Valid Choice";
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
        cout << "\n\tYour File is Empty! No Record is Avialable to Show\n";
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

        cout << "\n\n\t======== Sorted Employee Details With Respect to Salary ========\n\n";

        for (int i = 0; i < size; i++)
        {
            ptr[i].showData();
        }

        delete [] ptr;   // Explicitly Delete Memory Location From Heap.
    }
}


//***************************************************************
//            FUNCTION DEFINATION USED IN PROJECTS
//****************************************************************
int mainmenu()
{
    system("cls");
    int choice;
    bool flag;
    cout << "\n\n <================= Employee Managment System =================>\n\n";
    cout << "\tPlease Select Your Choice :- \n";
    cout << "\t1 : Insert Employees Records\n";
    cout << "\t2 : View All Employees Records\n";
    cout << "\t3 : Search Employees Records\n";
    cout << "\t4 : Update Employee Records\n";
    cout << "\t5 : Delete Employee Records\n";
    cout << "\t6 : Sort Employee Records w.r.t Salary\n";
    cout << "\t7 : Exit Application\n";
label:
    cout << "\tEnter Your Choice : ";
    cin >> choice;

    flag = validateInput();
    if (flag)
        goto label;
    else
        return choice;
}

bool validateInput()
{
    /* Why do we use:
         1) cin.ignore
         2) cin.clear

         1) To ignore (extract and discard) values that we don't want on the stream.
         2) To clear the internal state of stream. After using cin.clear internal state is set again back to goodbit, which means that there are no 'errors'.

         Long version:
         If something is put on 'stream' (cin) then it must be taken from there. By 'taken' we mean 'used', 'removed', 'extracted' from stream. Stream has a flow. The data is flowing on cin like water on stream. You simply cannot stop the flow of water.
    */

    if (cin.fail())
    {
        // Restore input stream
        cin.clear();
        // Clear The All Previous Input Before the '\n' Character 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Throwing Error and Again Input Value From User
        cout << "\n\tError : inValid Value Detected! Please Enter Valid Value Again\n\n";

        return true;
    }
    else
    {
        return false;
    }
}

bool isEmpty(ifstream &file)
{
    /*
    The peek() function looks into the input stream and tells us what the next character is without removing it from the input stream. Moreover, the peek() function can store the character in a designated memory locatio without actually removing it from the stream.
    */
   
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
            label:
            cout << "\tHow Many Employees Records that You Want to Store : ";
            cin >> size;

            flag = validateInput();

            if (flag)
            {
                goto label;
            }
            else
            {
                ptr = new Employee[size];

                for (int i = 0; i < size; i++)
                {
                    cout << "\n\n\tEnter the Details For the Employee # " << i + 1 << endl;
                    ptr[i].getData();
                }

                for (int i = 0; i < size; i++)
                {
                    ptr[i].writeFile();
                }

                delete [] ptr;  // Explicitly Delete Memory Location From Heap.
                
                cout << "\n\tNew Records Has Been Added Successfully\n";
                break;
            }
        case 2:
            cout << "\n\n\t=============== Employee Details ==================\n\n";
            filedata.readFile();
            break;
        case 3:
            cout << "\tPlease Enter Employee Unique ID That you Want to Search its Record : ";
            cin >> search;
            filedata.searchData(search);
            break;
        case 4:
            cout << "\tPlease Enter Employee Unique ID That you Want to Update its Record : ";
            cin >> search;
            filedata.updateData(search);
            break;
        case 5:
            cout << "\tPlease Enter Employee Unique ID you Want to Delete its Record : ";
            cin >> search;
            filedata.deleteData(search);
            break;
        case 6:
            filedata.sortData();
            break;
        case 7:
            cout << "\n\tThank You For Using This Application\n";
            check = false;
            break;
        default:
            cout << "\tInvalid Choice! Please Select Valid Choice.";
            break;
        }
        cout << "\n";
        cout << "\t" << system("pause");
    }
}
