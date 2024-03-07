#include <iostream>
#include <cctype>
#include <fstream>
#include <time.h>
#include <cstring>
#include <string>
using namespace std;

typedef struct createAccount
{
    string userName;
    string password;
} createAccount;

void start();
bool empty();
bool checkName(string);;
void create_Account();
void details(string);
void Authentication();
bool user_u(string, ifstream& file);
void interface(string);
void initialize_Balance(string);
void balance(string);
void depMoney(string);
void withDraw(string);
void transactions(string);
void view_Details(string);

int main()
{
    start();

return 0;
}

void start()
{
    int a;
    do
    {
        cout << "\n\t\t\t\t\t0. Login\n\t\t\t\t\t1. Create account\t";
        cin >> a;
        if (a == 1)  // If 1 then create account
        {
            cin.ignore();
            create_Account();
        }
    } while (a);  // After creating ACC ask again for choice

    if (a == 0)  // If 0 check Authentication
    Authentication();
}

void create_Account()
{
    createAccount user;  // Struct user
 
    bool b1 = true, b2 = true;
    while (b1)  // Check for valid username, 8-20 characters
    {
        b1 = false;
        cout << "\nUsername?\t";
        getline(cin, user.userName);

        int length1 = (user.userName).length();
        
        if (length1 < 6)
        {
            cout << "\nUsername must contain at least 8 characters:";
            b1 = true;
        }
        else if (length1 > 20)
        {
            cout << "\nUsername should not be greater than 20 letters.";
            b1 = true;
        }
    }

    // Check for valid Password at least 2 lowercase and 2 uppercase aplhabets, 2 special characters
    while (b2)
    {
        b2 = false;
        cout << "\nPassword\t";
        getline(cin, user.password);
        
        int length2 = (user.password).length();
        int digit = 0;
        for (int i = 0; i < length2; i++)
        {
            if (isdigit(user.password[i]))
            {
                digit++;
            }
        }

        int alpha = 0, upper = 0, lower = 0, special = 0;
        for (int i = 0; i < length2; i++)
        {
            if (isalpha(user.password[i]))
            {
                alpha++;
                if (isupper(user.password[i]))
                {
                    upper++;
                }
                if (islower(user.password[i]))
                {
                    lower++;
                }
            }
            char c = user.password[i];
            if (c == '!' || c == '@' || c == '#' || c == '%')  // count special characters
            {
                special++;
            }
            
        }

        if (length2 < 8)
        {
        cout << "\nPassword must contain at least 8 characters:";
        b2 = true;
        }
        else if (length2 > 20)
        {
        cout << "\nPassword should not be greater than 20 letters.";
        b2 = true;
        }
        else if (digit < 2)
        {
        cout << "\nPassword must contain at least 2 digits.";
        b2 = true;
        }
        else if (alpha < 4)
        {
        cout << "\nPassword must contain at least 4 alphabets.";
        b2 = true;
        }
        else if (lower < 2)
        {
        cout << "\nPassword must contain at least 2 lower case alphabets.";
        b2 = true;
        }
        else if (upper < 2)
        {
        cout << "\nPassword must contain at least 2 upper case alphabets.";
        b2 = true;
        }
        else if (special < 2)
        {
        cout << "\nPassword must contain at least 2 special characters.";
        b2 = true;
        }
    }

    // Check that username should not collide with existing usernames
    // empty() will return true if file is empty
    bool bo = empty();
    
    if(bo == 0)  // If Username.txt is not empty
    {
        bool b = checkName(user.userName);  // checkName(user.userName) will return true if name collide
        if(b)
        {
            cout << "\n\nUsername already exist. Try again";
            create_Account();  // Again call create_Account() function
        }
    }

    // If username donot collide existing usernames
    ofstream file1("Username.txt", ios::app);  // Open file in appending mode to store usernames
    if (!(file1.is_open()))
    {
        return;
    }

    ofstream file2("Password.txt", ios::app);  // Open file in appending mode to store Passwords
    if (!(file2.is_open()))
    {
        cout << "Failed to open file.";
        return;
    }

    // Write username and password
    file1 << user.userName << endl;
    file1.close();
    file2 << user.password << endl;
    file2.close();

    details(user.userName);  // Take details of account holder

    initialize_Balance(user.userName);  // initialize balance of current account holder to 0;

    ifstream filein("Total_Accounts.bin");  // Open in reading mode
    int n = 0;
    filein >> n;
    filein.close();

    ofstream fileout("Total_Accounts.bin", ios::out);  // Writing mode
    fileout << ++n;  // Update Total Accounts
    fileout.close();
}

void details(string str)
{
    string fullName, adress, phone;
    cout << "\nFull Name: ";
    getline(cin, fullName);
    cout << "Adress: ";
    getline(cin, adress);

    do  // Check for valid Phone No.
    {
        cout << "Phone Number: ";
        cin >> phone;
        if (phone.length() != 11)
        cout << "INVALID phone number. Try again.";
    } while (phone.length() != 11);

    string filename = str + "_details.bin";  // File to store details of (every) current account holder in seperate file
    ofstream file(filename, ios::out);

    ifstream filein("Total_Accounts.bin");  // Open Total_Accounts.bin
    int n = 0;  // Read balance from file in n
    filein >> n;

    int x = 0012312000;  // A number for every ACC NO.
    file << "Name: " << fullName << endl;
    // read from Total_Account and increment by 1 for generating account no of current account holder
    file << "Account No.: " << x << ++n << endl;
    file << "Account Creation Date: " << __DATE__ << endl; 
    file << "Phone No.: " << phone << endl;
    file << "Adress: " << adress << endl;

    file.close();
    filein.close();
}

void Authentication()
{
    int a = 0, x = 0;
    string str;
    do{
        a = 0;
        cin.ignore();
        // Input username and Password with spaces
        string name;
        string password;
        cout << "\nUsername?\t";
        getline(cin, name);
        cout << "Password?\t";
        getline(cin, password);
        
        str = name;
        
        ifstream fileu("Username.txt");  // Open file for checking of input username
        if (!(fileu.is_open()))
        {
        cout << "Failed to open file!";
        return;
        }

        ifstream filep("Password.txt");  // Open file for checking of input password
        if (!(filep.is_open()))
        {
        cout << "Failed to open file!";
        return;
        }

        // user_u() will return true if name or password matches with any of stored username or password
        bool bo1 = user_u(name, fileu);
        bool bo2 = user_u(password, filep);

        if (bo1  == 1 && bo2 == 1)  // When both fun return true
        {
            cout << "Logged in successfully.";
            a = 1;  // make a = 1
        }
        
        if (a == 0)  // When not logged in
        {
            cout << "Failed to login. Press ENTER to try again.";
            fileu.close();
            filep.close();
            Authentication();  // Again call Authentication to enter password and username again
        }
        filep.close();
        fileu.close();
    } while(!(a));  // Donot iterate again if a == 1 or logged in

    if (a == 1)  // If logged in successfully
    {
        cout << "\n\n\t\t\t**********/n/nWELCOME**********";
        interface(str);
    }
    
}

void interface(string str)
{
    int n = 1;
    cout << "\n\n1: \t\tCheck balance.";    // Choices
    cout << "\n2: \t\tDeposit money.";
    cout << "\n3: \t\tWithdraw money.";
    cout << "\n4: \t\tView transactions history.";
    cout << "\n5: \t\tView details of account.\t";
    cout << "\n6: \t\tExit Account.\t";
    int ch;
    cin >> ch;

    switch (ch)
    {
        // Call Respective function
        // Passing str(username) because to open file of same user to read data
    case 1:
        balance(str);
        break;
    case 2:
        depMoney(str);
        break;
    case 3:
        withDraw(str);
        break;
    case 4:
        transactions(str);
        break;
    case 5:
        view_Details(str);
        break;
    case 6:
        start();
        break;
    
    default:
        cout << "\nINVALID INPUT!";
        break;
    }

}

void initialize_Balance(string str)
{
    string filename = str + "_balance.bin";  // Create file to store balance of current account holder
    ofstream file(filename, ios::out);
    file << 0;  // Initialize balance to 0
    file.close();
}

void balance(string str)
{
    string filename = str + "_balance.bin";  // Open file of that user
    ifstream file(filename);
    if (!(file.is_open()))
    {
        cout << "\nFailed to open file.";
        return;
    }

    int num;  // Read and display balance
    file >> num;
    cout << "\nBalance: " << num << endl;
    file.close();

    interface(str);  // Again call for choices
}

void depMoney(string str)
{
    int money;
    cout << "\nEnter amount to deposit: ";
    cin >> money;

    string filename = str + "_balance.bin";  // Open file of that user
    ifstream filein(filename);
    if (!(filein.is_open()))
    {
        cout << "\nFailed to open file.";
        return;
    }
    int balance;  // Read balance
    filein >> balance;
    balance += money;  // Add deposited money to existing balance
    filein.close();

    ofstream fileout(filename, ios::out);  // Now open same file in writing mode to write updated balance
    if (!(fileout.is_open()))
    {
        cout << "\nFailed to open file.";
        return;
    }
    
    fileout << balance;  // Write balance in file
    fileout.close();

    string file_trans = str + "_transactions.bin";  // Open file of that user in appending mode to store transaction history
    ofstream file(file_trans, ios::app);
    if (!(file.is_open()))
    {
        cout << "\nFailed to open file.";
        return;
    }
    file << "Date: " << __DATE__ << ", Amount Deposited: " << money << ", Total Balance: " << balance << endl;  // Append record
    file.close();
    interface(str);  // Again call for choices
}

void withDraw(string str)
{
    int money;
    string filename = str + "_balance.bin";  // Open file of that user
    ifstream filein(filename);
    int balance;
    filein >> balance;  // Read balance
    filein.close();
    int n = balance;
    do
    {
        cout << "\nEnter money to withdraw: ";
        cin >> money;
        
        if (balance < money)  // When user withdraw money more than balance
        {
            cout << "\nNot sufficient balance!";
        }
        else
        {
            balance -= money;  // Subtract withdraw money from balance
            filein.close();
        }
    } while (n < money);

    ofstream fileout(filename, ios::out);  // Now open same file in writing mode to write updated balance
    if (!(fileout.is_open()))
    {
        cout << "\nFailed to open file.";
        return;
    }
    fileout << balance;  // Write balance
    fileout.close();

    string file_trans = str + "_transactions.bin"; // File of that user in appending mode to store transaction history
    ofstream file(file_trans, ios::app);
    if (!(file.is_open()))
    {
        cout << "\nFailed to open file.";
        return;
    }
    file << "Date: " << __DATE__ << ", Amount Withdraw: " << money << ", Total Balance: " << balance << endl;  // Write record
    file.close();
    interface(str);  // Again call, for choices
}

void transactions(string str)
{
    string filename = str + "_transactions.bin";
    ifstream file(filename);  // Open transaction file of user in reading mode
    if (!(file.is_open()))
    {
        cout << "\nNo transactions.";
        return;
    }
    cout << endl;
    string s;
    while (getline(file, s)) // Read each line
    {
        cout << s << endl;  // Display each line
    }
    file.close();
    interface(str);  // Again call, for choices
}

void view_Details(string str)
{
    string filename = str + "_details.bin";  // Open file to read details of current user
    ifstream file(filename);
    string s;
    while (getline(file, s))  // Read each line
    {
        cout << s << endl;  // Display each line
    }
    file.close();


    string filename1 = str + "_transactions.bin";  // Open file to read transactions of current user
    ifstream file1(filename1);
    string s1;
    cout << "Transaction History:\n";
    while (getline(file1, s1))  // Read each line
    {
        cout << "\t\t\t" << s1 << endl;  // Display each line
    }
    file1.close();

    string filename2 = str + "_balance.bin"; // Open file to read balance of current user
    ifstream file2(filename2);
    int num;
    file2 >> num;  // Read balance
    cout << "\nCurrent Balance: " << num << endl;  // Display balance
    file2.close();
    interface(str);  // Call again, for choices
}

bool empty()
{
    bool b = false;
    ifstream file("Username.txt");  // Open file in reading mode
    if (!file.is_open())
    {
        return false;
    }
    file.seekg(0, ios::end);  // Check wheather file is empty or not
    if (file.tellg() == 0)  // If empty return true
    {
        return true;
    }
    file.close();

    return false;
}

bool checkName(string str)
{
    ifstream file("Username.txt");  // Open file in reading mode
    if (!file.is_open())
    {
        return false;
    }

    string s;
    while (getline(file, s))  // Checking that is any username in file matches with str or not, if matches return true
    {   
        if (str == s)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool user_u(string str, ifstream& file)
{
    string s;
    while (getline(file, s))  // Read from file and store each line(username or password) in s
    {
        if (s == str)  // If matches then return true
        {
            file.close();
            return true;
        }
    }
    return false;
}