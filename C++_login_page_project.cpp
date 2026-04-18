#include<iostream>
#include<fstream>
using namespace std;

class temp
{
    string userName,Email,password;
    string searchName,searchPass,searchEmail;
    fstream file;
public:
    void login();
    void signUp();
    void forgot();
};


int main()
{
    temp obj;
    char choice;
    while(true)
    {
        cout<<"\n1- Login";
        cout<<"\n2- Sign-up";
        cout<<"\n3- Forget Password";
        cout<<"\n4- Exit";
        cout<<"\n\nEnter Your Choice :: ";
        cin>>choice;
        cin.ignore();

        switch(choice)
        {
        case '1':
            obj.login();
            break;
        case '2':
            obj.signUp();
            break;
        case '3':
            obj.forgot();
            break;
        case '4':
            return 0;
            break;
        default:
            cout<<"Invalid Selection...!";
        }
    }
}

void temp :: signUp()
{
    cout<<"\nEnter Your user Name :: ";
    getline(cin,userName);
    cout<<"Enter Your Email Address :: ";
    getline(cin,Email);
    cout<<"Enter Your Password :: ";
    getline(cin,password);

    file.open("loginData.txt",ios :: out | ios :: app);
    file<<userName<<"*"<<Email<<"*"<<password<<endl;
    file.close();
}

void temp :: login()
{
    cout<<"--------LOGIN--------"<<endl;
    cout<<"Enter Your User Name :: "<<endl;
    getline(cin,searchName);
    cout<<"Enter Your password:: "<<endl;
    getline(cin,searchPass);

    file.open("loginData.txt",ios :: in);
    bool found = false;
    while(getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password, '\n')) {
        if(userName == searchName && password == searchPass) {
            cout<<"\nAccount Login Successful...!";
            cout<<"\nUserName :: "<<userName;
            cout<<"\nEmail :: "<<Email<<endl;
            found = true;
            break;
        }
    }

    if(!found) {
        cout << "\nInvalid Username or Password!" << endl;
    }
    file.close();

}

void temp :: forgot()
{
    cout<<"Enter Your User Name :: "<<endl;
    getline(cin,searchName);
    cout<<"Enter Your Email:: "<<endl;
    getline(cin,searchEmail);

    file.open("loginData.txt",ios :: in);
   bool found = false;

    while(getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password, '\n')) {
        if(userName == searchName && Email == searchEmail) {
            cout<<"\nAccount Found Successfully...!";
            cout<<"\nYour Password :: "<<password<<endl;
            found = true;
            break;
        }
    }

    if(!found) {
        cout<<"\nAccount Not Found...!\n";
    }
    file.close();

}
