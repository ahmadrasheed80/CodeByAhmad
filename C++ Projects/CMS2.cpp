#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

// forward declaration

class Contacts;

class User
{

private:
    string firstName, lastName, email, password;
    int userId;
    friend class Contacts;
    // friend DatabaseManager;

public:
    string filepath = "Users/";
    void registerUser();
    string getEmail();
    string getPassword();
    bool loginUser();

}; // End user class

// Functions for user class

void User::registerUser()
{
    cout << "====================================" << endl;
    cout << "\t Register User " << endl;
    cout << "====================================" << endl;

    // Assuming filepath + to_string(userId) + "_info" + ".dat" is defined somewhere before this function is called
    cout << "Enter your ID: ";
    cin >> userId;

    // Check if the file already exists
    ifstream existingFile(filepath + to_string(userId) + "_info" + ".dat");
    if (existingFile.is_open())
    {
        cout << "A user with this ID already exists." << endl;
        existingFile.close();
        return;
    }

    // Get other user details
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your email address: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    cout << "====================================" << endl;

    // Save user in the file
    ofstream userFile(filepath + to_string(userId) + "_info" + ".dat");
    userFile << userId << " " << firstName << " " << lastName << " " << email << " " << password << endl;
    userFile.close();

    cout << "User registration successful." << endl;
}

bool User ::loginUser()
{

    string _email;
    int _id;
    string _password;
    cout << "====================================" << endl;
    cout << "\t\tLogin User " << endl;
    cout << "====================================" << endl;
    // open the file
    cout << "Enter your email : ";
    cin >> _email;
    cout << "Enter your ID : ";
    cin >> _id;
    cout << "Enter your password : ";
    cin >> _password;

    ifstream userFile2(filepath + to_string(_id) + "_info" + ".dat");

    if (!userFile2.is_open())
    {
        system("cls");

        cout << "Error: Could not open!" << endl;
        return 0;
    }

    while (userFile2 >> userId >> firstName >> lastName >> email >> password)
    {
        if (email == _email && password == _password)
        {
            system("cls");
            cout << "Logged in as " << firstName << " " << lastName << " successfully!" << endl;
            return 1;
        }
    }
    system("cls");

    cout << "Invalid username or password!" << endl;
    loginUser();
    userFile2.close();
    return 0;
}

// string User ::getEmail()
// {

//     return email;

// } // end getEmail function

// string User ::getPassword()
// {

//     return password;

// } // end getPassword function

//----------------------------------------------------------------
// 2nd class
class Contacts : virtual public User
{
private:
    string fname, lname, email, address;
    long long phoneNo;

public:
    void submitForm()
    {

        cout << "Enter the first name : ";
        cin >> fname;
        cout << "Enter the last name : ";
        cin >> lname;
        cout << "Enter the email :  ";
        cin >> email;
        cout << "Enter the address : ";
        cin >> address;
        cout << "Enter the phone number : ";
        cin >> phoneNo;
    }

    void createContact()
    {
        submitForm();
        // open file with the name of this user or ID
        ofstream writeContactsFile(filepath + to_string(userId) + "_info" + ".dat", ios::app);

        if (!writeContactsFile)
        {
            system("cls");

            cout << "Error  : File is not opening!" << endl;
        }

        writeContactsFile << fname << " " << lname << " " << email << " " << address << " " << phoneNo << endl;
        system("cls");

        cout << "Data stored successfully!" << endl;
        writeContactsFile.close();
    }

    void contactForm()
    {

        cout << "====================================" << endl;
        cout << "\t Details of " << fname << " " << lname << endl;
        cout << "====================================" << endl;

        cout << "Name : " << fname << " " << lname << endl;
        cout << "Email : " << email << endl;
        cout << "Address : " << address << endl;
        cout << "Phone Number : " << phoneNo << endl;
    }

    void showContact()
    {
        ifstream readData(filepath + to_string(userId) + "_info" + ".dat");

        if (!readData.is_open())
        {
            system("cls");

            cout << "Error: Couldn't open file." << endl;
            return;
        }

        string line;
        getline(readData, line);
        if (readData >> fname >> lname >> email >> address >> phoneNo)
        {
            do
            {
                contactForm();
            } while (readData >> fname >> lname >> email >> address >> phoneNo);
        }
        else
        {
            system("cls");

            cout << "No contact found" << endl;
        }

        // while (readData >> fname >> lname >> email >> address >> phoneNo)
        // {

        //     cout << "====================================" << endl;
        //     cout << "\t Details of " << fname << " " << lname << endl;
        //     cout << "====================================" << endl;

        //     cout << "Name : " << fname << " " << lname << endl;
        //     cout << "Email : " << email << endl;
        //     cout << "Address : " << address << endl;
        //     cout << "Phone Number : " << phoneNo << endl;
        // }
    }

    bool searchContact()
    {
        string _email;
        ifstream searchingFile(filepath + to_string(userId) + "_info" + ".dat");

        if (!searchingFile.is_open())
        {
            system("cls");

            cout << "Error: Could not open file!" << endl;
            return false;
        }

        cout << "Enter the email to find contact:" << endl;
        cin >> _email;

        string line;
        while (getline(searchingFile, line))
        {
            // for reading line by line in the file and extracting in "iss"
            istringstream iss(line);

            if (iss >> fname >> lname >> email >> address >> phoneNo)
            {
                if (email == _email)
                {
                    contactForm();
                    searchingFile.close();
                    return true;
                }
            }
        }
        system("cls");

        cout << "Contact with " << email << " not found " << endl;
        searchingFile.close();
        return false;
    }

    void deleteContact()
    {
        string _email;
        int flag = 0;

        cout << "Enter the email to delete contact: ";
        cin >> _email;

        ifstream existingFile(filepath + to_string(userId) + "_info" + ".dat");
        ofstream newFile("temp.dat");

        if (!existingFile.is_open() || !newFile.is_open())
        {
            cout << "Error: Couldn't open file." << endl;
            return; // exit the function on error
        }

        string line;
        // adding first line to the new file (user data in the first line)
        if (getline(existingFile, line))
        {
            newFile << line << endl;
        }

        while (getline(existingFile, line))
        {
            // it extract the data of the existing file in 'is'
            istringstream is(line);

            if (is >> fname >> lname >> email >> address >> phoneNo)
            {
                if (_email != email)
                {
                    newFile << fname << " " << lname << " " << email << " " << address << " " << phoneNo << endl;
                }
                else
                {
                    flag = 1;
                }
            }
        }

        existingFile.close();
        newFile.close();

        if (remove((filepath + to_string(userId) + "_info" + ".dat").c_str()) != 0)
        {
            system("cls");

            cout << "Error deleting original file." << endl;
            return; // exit the function on error
        }

        if (rename("temp.dat", (filepath + to_string(userId) + "_info" + ".dat").c_str()) != 0)
        {
            system("cls");

            cout << "Error renaming temporary file." << endl;
            return; // exit the function on error
        }

        if (flag == 1)
        {
            system("cls");

            cout << "Success! Contact Deleted!" << endl;
        }
        else
        {
            system("cls");

            cout << "Contact not found." << endl;
        }
    }

    void updateContact()
    {

        system("cls");
        int flag = 0;
        string _email;
        cout << "Enter the email to update the contact : " << endl;
        cin >> _email;

        ifstream existingFile(filepath + to_string(userId) + "_info" + ".dat");
        ofstream newFile("temp.dat");

        if (!existingFile.is_open() || !newFile.is_open())
        {
            cout << "Error: Couldn't open the file " << endl;
            return;
        }

        string line;

        if (getline(existingFile, line))
        {
            newFile << line << endl;
        }

        while (getline(existingFile, line))
        {
            istringstream is(line);
            if (is >> fname >> lname >> email >> address >> phoneNo)
            {
                if (_email != email)
                {
                    newFile << fname << " " << lname << " " << email << " " << address << " " << phoneNo << endl;
                }
                else
                {
                    flag = 1;
                    cout << "Enter details again for updating your contact " << endl;
                    submitForm();
                    newFile << fname << " " << lname << " " << email << " " << address << " " << phoneNo << endl;
                }
            }
        }

        existingFile.close();
        newFile.close();

        if (remove((filepath + to_string(userId) + "_info" + ".dat").c_str()) != 0)
        {
            system("cls");
            cout << "Error removing the previous contact." << endl;
            return;
        }

        if (rename("temp.dat", (filepath + to_string(userId) + "_info" + ".dat").c_str()) != 0)
        {
            system("cls");
            cout << "Error renaming the file." << endl;
            return;
        }

        if (flag == 0)
        {
            system("cls");
            cout << "Error : contact not found." << endl;
        }
        else
        {
            system("cls");

            cout << "Success! Contact updated successfully." << endl;
        }
    }
};

// managing contact with login or users
class DatabaseManager : virtual public User, public Contacts
{

public:
    void dashboard()
    {
        if (loginUser() == true)
        {
            while (1)
            {
                cout << "====================================" << endl;
                cout << "\tContact Management System " << endl;
                cout << "====================================" << endl;
                char choice;
                cout << "====================================" << endl;
                cout << "[0]-Logout\n[1]-Show Contacts\n[2]-Create Contact\n[3]-Delete Contact\n[4]-Update Contact\n[5]-Search Contact\nEnter the choice:\n " << endl;
                cin >> choice;

                switch (choice)
                {
                case '0':
                    system("cls");

                    cout << "You are logout successfully!" << endl
                         << endl;
                    return;
                case '1':
                    system("cls");

                    showContact();
                    break;
                case '2':
                    system("cls");
                    cout << "====================================" << endl;
                    cout << "\t Create Contact " << endl;
                    cout << "====================================" << endl;
                    createContact();
                    break;
                case '3':
                    system("cls");
                    cout << "====================================" << endl;
                    cout << "\t Delete Contact " << endl;
                    cout << "====================================" << endl;
                    deleteContact();
                    break;
                case '4':
                    system("cls");
                    cout << "====================================" << endl;
                    cout << "\t Update Contact " << endl;
                    cout << "====================================" << endl;
                    updateContact();
                    break;
                case '5':
                    system("cls");
                    cout << "====================================" << endl;
                    cout << "\t Search Contact " << endl;
                    cout << "====================================" << endl;
                    searchContact();
                    break;
                default:
                    system("cls");

                    cout << "Invalid choice, please try again:" << endl;
                    continue;
                }
            }
        }
    }
};

int main()
{
    system("cls");

    User object;
    DatabaseManager object1;
    char choice;
    while (1)
    {
        cout << "====================================" << endl;
        cout << "Welcome To Contact Management System " << endl;
        cout << "====================================" << endl;
        cout << "\n[0]-Exit\n[1]-Registration\n[2]-Login\nEnter your choice :  " << endl;
        cin >> choice;

        switch (choice)
        {
        case '0':
            system("cls");

            cout << "================================\n\tThanks For Using CMS\n================================"
                 << endl;
            exit(0);
        case '1':
            system("cls");

            object.registerUser();
            break;
        case '2':
            system("cls");

            object1.dashboard();
            break;
        default:
            continue;
        }
    }

    return 0;
}